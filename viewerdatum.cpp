#include "viewerdatum.h"
#include "quickosgrenderer.h"
#include "quickosgviewer.h"
#include <QtDebug>
#include <QQuickWindow>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/LineWidth>
#include <osgViewer/GraphicsWindow>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgGA/NodeTrackerManipulator>
#include <QtMath>
#include<osgShadow/SoftShadowMap>
#include <osg/LineWidth>
#include <osgText/Text>
#include <osg/AutoTransform>
#include <osg/TextureRectangle>

const osg::Node::NodeMask ViewerDatum::m_datumMask = 0xfffffffe;

ViewerDatum::ViewerDatum(float size, osg::Camera *mainCamera)
    : m_size(size), m_mainCamera(mainCamera)
{
    setNodeMask(m_datumMask);
    m_axis = createViewerDatum(m_size);
}

osg::Geode * ViewerDatum::createAxisAlignedArrow(QString axis, float arrowLength, float arrowConeRadius, float arrowConeHeight, osg::Vec3 &coneCenter)
{
    osg::Geode* geode = new osg::Geode;
    osg::ref_ptr<osg::Geometry> lineGeometry = new osg::Geometry;
    osg::ref_ptr<osg::ShapeDrawable> coneGeometry = new osg::ShapeDrawable;

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;

    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
    osg::Vec4 coneColor = osg::Vec4(0.313, 0.313, 0.313, 1.0);
    osg::ref_ptr<osg::Cone> cone = nullptr;
    osg::Quat coneRotQuat;

    std::string timesFont("fonts/arial.ttf");
    auto labelOffsetRatio = 2.0;

    if (axis == "X"){
        coneCenter = osg::Vec3(arrowLength*labelOffsetRatio, 0.0f, 0.0f);
        coneColor = osg::Vec4(0.8157f, 0.008f, 0.0745f, 1.0f);
        vertices->push_back(coneCenter);
        colors->push_back(coneColor);
        cone = new osg::Cone(coneCenter, arrowConeRadius, arrowConeHeight);
        coneRotQuat.makeRotate(M_PI / 2, osg::Vec3(0.0f, 1.0f, 0.0f));
        cone->setRotation(coneRotQuat);
        coneGeometry->setShape(cone);
        coneGeometry->setColor(coneColor);
        geode->setName("X");
    }
    else if (axis == "Y"){
        coneCenter = osg::Vec3(0.0f, arrowLength*labelOffsetRatio, 0.0f);
        coneColor = osg::Vec4(0.494f, 0.827f, 0.129f, 1.0f);
        vertices->push_back(coneCenter);
        colors->push_back(coneColor);
        cone = new osg::Cone(coneCenter, arrowConeRadius, arrowConeHeight);
        coneRotQuat.makeRotate(-M_PI / 2, osg::Vec3(1.0f, 0.0f, 0.0f));
        cone->setRotation(coneRotQuat);
        coneGeometry->setShape(cone);
        coneGeometry->setColor(coneColor);
        geode->setName("Y");
    }
    else{
        coneCenter = osg::Vec3(0.0f, 0.0f, arrowLength*labelOffsetRatio);
        coneColor = osg::Vec4(0.0f, 0.5216f, 1.0f, 1.0f);
        vertices->push_back(coneCenter);
        colors->push_back(coneColor);
        cone = new osg::Cone(coneCenter, arrowConeRadius, arrowConeHeight);
        coneGeometry->setShape(cone);
        coneGeometry->setColor(coneColor);
        geode->setName("Z");
    }

    osg::LineWidth * lw = new osg::LineWidth(1.8);
    lineGeometry->getOrCreateStateSet()->setAttributeAndModes(lw);
    lineGeometry->setVertexArray(vertices);
    lineGeometry->setColorArray(colors, osg::Array::BIND_OVERALL);
    lineGeometry->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, vertices->size()));
    geode->addDrawable(lineGeometry);
    geode->addDrawable(coneGeometry);

    osg::ref_ptr<osg::Uniform> hoveredUniform = new osg::Uniform("Hovered", false);
    geode->getOrCreateStateSet()->addUniform(hoveredUniform);
    geode->setUserData(hoveredUniform);

    coneCenter *= 1.5;
    return geode;
}

osg::AutoTransform * ViewerDatum::createLabel(QString txt, osg::Vec3 pos)
{
    std::string timesFont("fonts/msyhbd.ttc");

    osgText::Text* text = new osgText::Text;
    text->setCharacterSize(17);
    text->setText(txt.toLatin1().data());
    text->setFont(timesFont);
    text->setAlignment(osgText::Text::CENTER_CENTER);
    if (txt == "X"){
        text->setColor(osg::Vec4(0.8157f, 0.008f, 0.0745f, 1.0f));
    }
    else if (txt == "Y"){
        text->setColor(osg::Vec4(0.494f, 0.827f, 0.129f, 1.0f));
    }
    else{
        text->setColor(osg::Vec4(0.0f, 0.5216f, 1.0f, 1.0f));
    }
    //text->setAlignment(osgText::Text);

    osg::Geode* textGeode = new osg::Geode;
    textGeode->addDrawable(text);
    textGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    osg::AutoTransform* at = new osg::AutoTransform;
    at->addChild(textGeode);

    at->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
    at->setAutoScaleToScreen(true);
    at->setPosition(pos);
    return at;
}

osg::MatrixTransform * ViewerDatum::createViewerDatum(float size)
{
    float arrowLength = size;
    float arrowConeHeight = size / 2;
    float arrowConeRadius = size / 8;

    osg::MatrixTransform * datum = new osg::MatrixTransform;
    osg::Group *arrowsGroup = new osg::Group;
    osg::Group *labelGroup = new osg::Group;

    osg::Vec3 labelPos;
    arrowsGroup->addChild(createAxisAlignedArrow(QStringLiteral("X"), arrowLength, arrowConeRadius, arrowConeHeight, labelPos));
    auto labelX = createLabel(QStringLiteral("X"), labelPos);
    osg::Uniform *textColor = new osg::Uniform("MaterialColor", osg::Vec4(0.313, 0.313, 0.313, 1.0));
    osg::Uniform *textTexture = new osg::Uniform("GlyphTexture", 0);
    auto stateSet = labelX->getOrCreateStateSet();
    stateSet->addUniform(textColor);
    stateSet->addUniform(textTexture);
    //stateSet->setAttribute(textProgram, osg::StateAttribute::ON);
    labelGroup->addChild(labelX);

    arrowsGroup->addChild(createAxisAlignedArrow(QStringLiteral("Y"), arrowLength, arrowConeRadius, arrowConeHeight, labelPos));
    auto labelY = createLabel(QStringLiteral("Y"), labelPos);
    //textColor = new osg::Uniform("MaterialColor", osg::Vec4(0.313, 0.313, 0.313, 1.0));
    textTexture = new osg::Uniform("GlyphTexture", 0);
    stateSet = labelY->getOrCreateStateSet();
    stateSet->addUniform(textColor);
    stateSet->addUniform(textTexture);
    //stateSet->setAttribute(textProgram, osg::StateAttribute::ON);
    labelGroup->addChild(labelY);

    arrowsGroup->addChild(createAxisAlignedArrow(QStringLiteral("Z"), arrowLength, arrowConeRadius, arrowConeHeight, labelPos));
    auto labelZ = createLabel(QStringLiteral("Z"), labelPos);
    //textColor = new osg::Uniform("MaterialColor", osg::Vec4(0.313, 0.313, 0.313, 1.0));
    textTexture = new osg::Uniform("GlyphTexture", 0);
    stateSet = labelZ->getOrCreateStateSet();
    stateSet->addUniform(textColor);
    stateSet->addUniform(textTexture);
    //stateSet->setAttribute(textProgram, osg::StateAttribute::ON);
    labelGroup->addChild(labelZ);


    osg::ref_ptr<osg::LineWidth> lineWidth = new osg::LineWidth;
    lineWidth->setWidth(3.0f);
    stateSet = arrowsGroup->getOrCreateStateSet();
    stateSet->setAttributeAndModes(lineWidth);
    //stateSet->setAttribute(arrowProgram, osg::StateAttribute::ON);



    datum->addChild(arrowsGroup);
    datum->addChild(labelGroup);
    //datum->setDataVariance(osg::Object::DYNAMIC);
    return datum;
}


void ViewerDatum::traverse(osg::NodeVisitor& nv)
{
    if (m_mainCamera.valid() &&	nv.getVisitorType() == osg::NodeVisitor::CULL_VISITOR){
        osg::Matrix matrix = m_mainCamera->getViewMatrix();
        matrix.setTrans( osg::Vec3() );
        //matrix.setScale();
        m_axis->setMatrix(matrix);
    }
    m_axis->accept(nv);
    osg::Camera::traverse( nv );
}
