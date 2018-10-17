#ifndef _QUICK_OSG_VIEWER_DATUM_H_
#define _QUICK_OSG_VIEWER_DATUM_H_

#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>  
#include <osgUtil/Optimizer>  
#include <osg/CoordinateSystemNode>  

#include <osg/Switch>  
#include <osgText/Text>  

#include <osgViewer/Viewer>  
#include <osgViewer/ViewerEventHandlers>  


class QuickOSGViewer;
class QuickOSGRenderer;

class ViewerData : public osg::Referenced
{
public:
    QuickOSGRenderer* renderer;
};


class ViewerDatum: public osg::Camera
{
public:
    const static osg::Node::NodeMask m_datumMask;
    ViewerDatum(float size, osg::Camera *mainCamera);
    virtual void traverse( osg::NodeVisitor& nv );
private:
    osg::Geode * createAxisAlignedArrow(QString axis, float arrowLength,
        float arrowConeRadius, float arrowConeHeight,
        osg::Vec3 &coneCenter);
    osg::MatrixTransform * createViewerDatum(float size);
    osg::AutoTransform * createLabel(QString txt, osg::Vec3 pos);
private:
    float m_size;
    osg::ref_ptr<osg::Camera> m_mainCamera;
    osg::ref_ptr<osg::MatrixTransform> m_axis;
};

#endif // _QUICK_OSG_VIEWER_DATUM_H_
