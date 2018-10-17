#include "appworker.h"
#include <QFile>
#include <QtDebug>
#include <osg/Geode>
#include <osg/Geometry>
#include <QVariantMap>
#include <QTextStream>
#include <osg/BufferObject>
#include <osg/BufferIndexBinding>
#include <osg/Texture2D>
#include <osg/TextureRectangle>
#include <osgDB/ReaderWriter>
#include <osgDB/ReadFile>
#include <osg/AutoTransform>
#include "quickosgviewer.h"



AppWorker::AppWorker(QObject *appGlobal)
    : m_appGlobal(appGlobal)
{

}

void AppWorker::loadPointCloud(const QString &filePath)
{
    if(QFile::exists(filePath) == false){
        warning(QString("File %1 does not exist!").arg(filePath));
        return;
    }
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)){
        warning(QString("File %1 cannot open!").arg(filePath));
        return;
    }
    osg::ref_ptr<osg::Geode> geode = loadPointCloudFile(file);
    file.close();

    QMetaObject::invokeMethod(m_appGlobal, "modelLoaded", Qt::QueuedConnection, Q_ARG(osg::Node*, geode.release()));
}

void AppWorker::loadObj(const QString &filePath)
{
    if(QFile::exists(filePath) == false){
        warning(QString("File %1 does not exist!").arg(filePath));
        return;
    }
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)){
        warning(QString("File %1 cannot open!").arg(filePath));
        return;
    }
    osg::ref_ptr<osg::Geode> geode = loadObjFile(file);
    file.close();

    QMetaObject::invokeMethod(m_appGlobal, "modelLoaded", Qt::QueuedConnection, Q_ARG(osg::Node*, geode.release()));
}

void AppWorker::warning(const QString &msg)
{
    qWarning()<<msg;
    QMetaObject::invokeMethod(m_appGlobal, "errorHappened", Qt::QueuedConnection, Q_ARG(QString, msg));
}

QByteArray AppWorker::readShaderFile(const QString &filePath)
{
    QFile shaderFile(filePath);
    if(!shaderFile.open(QIODevice::ReadOnly)){
        qCritical()<<"Cannot open"<<filePath;
        return "";
    }
    auto shaderSource = shaderFile.readAll();
    shaderFile.close();
    return shaderSource;
}

osg::Geode *AppWorker::loadPointCloudFile(QFile &file)
{
    auto progressInfo = QVariantMap{{"visible", true}, {"title", "Loading"},{"from", 0}, {"to", file.size()}};
    QMetaObject::invokeMethod(m_appGlobal, "setProgressInfo", Qt::QueuedConnection, Q_ARG(QVariantMap, progressInfo));

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    osg::ref_ptr<osg::Vec3Array> colors = new osg::Vec3Array;
    colors->setBinding(osg::Array::BIND_PER_VERTEX);
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->setBinding(osg::Array::BIND_PER_VERTEX);

    const int EMIT_RATE = file.size() / 100; // emit progress info per emitRate
    int emitCount = 0;
    char lineBuf[1024];
    float posbuf[3], norbuf[3], colbuf[3];
    qint64 vcount = 0;
    while (!file.atEnd()) {
        auto lineLength = file.readLine(lineBuf, sizeof(lineBuf));
        //if(vcount++ % 5 != 1) continue;
        if(lineLength != -1){
            sscanf(lineBuf, "%f %f %f %f %f %f %f %f %f", posbuf, posbuf + 1, posbuf + 2,
                   colbuf, colbuf + 1, colbuf + 2,
                   norbuf, norbuf + 1, norbuf + 2);

//            sscanf(lineBuf, "%f %f %f %f %f %f", posbuf, posbuf + 1, posbuf + 2,
//                   norbuf, norbuf + 1, norbuf + 2);

            if(norbuf[0] == 0.0f && norbuf[1] == 0.0f && norbuf[2] == 0.0f)
                continue;
            vertices->push_back(osg::Vec3(posbuf[0], posbuf[1], posbuf[2]));
            //colors->push_back(osg::Vec3(colbuf[0], colbuf[1], colbuf[2]));
            colors->push_back(osg::Vec3(colbuf[0] / 255.0f, colbuf[1] / 255.0f, colbuf[2] / 255.0f));
            normals->push_back(osg::Vec3(norbuf[0], norbuf[1], norbuf[2]));

            auto readPos = file.pos();
            if(readPos / EMIT_RATE > emitCount){
                emitCount = readPos / EMIT_RATE;
                QMetaObject::invokeMethod(m_appGlobal, "setProgressValue", Qt::QueuedConnection, Q_ARG(float, float(readPos)));
            }
        }
    }

    QMetaObject::invokeMethod(m_appGlobal, "setProgressValue", Qt::QueuedConnection, Q_ARG(float, float(file.size())));

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
    geometry->setVertexArray(vertices.get());
    //colors->push_back(osg::Vec3(0.5, 0.5, 0.5));
    geometry->setVertexAttribArray(1, colors.get(), osg::Array::BIND_PER_VERTEX);
    geometry->setVertexAttribArray(2, normals.get(), osg::Array::BIND_PER_VERTEX);
    geometry->addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, vertices->size()));

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geometry.get());

    osg::ref_ptr<osg::Program> firstPassProgram = new osg::Program;
    auto firstPassVSSource = readShaderFile(":/shaders/disc_render.vert");
    auto firstPassFSSource = readShaderFile(":/shaders/disc_render.frag");
    firstPassProgram->addShader(new osg::Shader(osg::Shader::VERTEX, firstPassVSSource.data()));
    firstPassProgram->addShader(new osg::Shader(osg::Shader::FRAGMENT, firstPassFSSource.data()));

    auto ss = geode->getOrCreateStateSet();

    //ss->setAttributeAndModes(ssbb.get(), osg::StateAttribute::ON);
    ss->setAttributeAndModes(firstPassProgram.get(), osg::StateAttribute::ON);
    ss->setMode(GL_VERTEX_PROGRAM_POINT_SIZE, osg::StateAttribute::ON);
    //ss->addUniform(nearUni.get()); ss->addUniform(farUni.get());

    progressInfo["visible"] = false;
    QMetaObject::invokeMethod(m_appGlobal, "setProgressInfo", Qt::QueuedConnection, Q_ARG(QVariantMap, progressInfo));

    return  geode.release();
}

osg::Geode *AppWorker::loadObjFile(QFile &file)
{
    auto progressInfo = QVariantMap{{"visible", true}, {"title", "Loading"},{"from", 0}, {"to", file.size()}};
    QMetaObject::invokeMethod(m_appGlobal, "setProgressInfo", Qt::QueuedConnection, Q_ARG(QVariantMap, progressInfo));

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    osg::ref_ptr<osg::Vec3Array> colors = new osg::Vec3Array;
    colors->setBinding(osg::Array::BIND_PER_VERTEX);
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->setBinding(osg::Array::BIND_PER_VERTEX);

    const int EMIT_RATE = file.size() / 100; // emit progress info per emitRate
    int emitCount = 0;
    char lineBuf[1024];
    float posbuf[3];
    int faceIdx[3];
    qint64 vcount = 0;
    while (!file.atEnd()) {
        auto lineLength = file.readLine(lineBuf, sizeof(lineBuf));
        if(lineLength == -1) continue;

        if(lineLength > 2 && lineBuf[0] == 'v' && lineBuf[1] == ' '){
            sscanf(lineBuf, "v %f %f %f", posbuf, posbuf + 1, posbuf + 2);

            vertices->push_back(osg::Vec3(posbuf[0], posbuf[1], posbuf[2]));

            auto readPos = file.pos();
            if(readPos / EMIT_RATE > emitCount){
                emitCount = readPos / EMIT_RATE;
                QMetaObject::invokeMethod(m_appGlobal, "setProgressValue", Qt::QueuedConnection, Q_ARG(float, float(readPos)));
            }
        }
        else if(lineLength > 2 && lineBuf[0] == 'f' && lineBuf[1] == ' '){
            sscanf(lineBuf, "f %d %d %d", faceIdx, faceIdx + 1, faceIdx + 2);
        }
    }

    QMetaObject::invokeMethod(m_appGlobal, "setProgressValue", Qt::QueuedConnection, Q_ARG(float, float(file.size())));

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
    geometry->setVertexArray(vertices.get());
    //colors->push_back(osg::Vec3(0.5, 0.5, 0.5));
    geometry->setVertexAttribArray(1, colors.get(), osg::Array::BIND_PER_VERTEX);
    geometry->setVertexAttribArray(2, normals.get(), osg::Array::BIND_PER_VERTEX);
    geometry->addPrimitiveSet(new osg::DrawArrays(GL_POINTS, 0, vertices->size()));

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geometry.get());

    osg::ref_ptr<osg::Program> firstPassProgram = new osg::Program;
    auto firstPassVSSource = readShaderFile(":/shaders/disc_render.vert");
    auto firstPassFSSource = readShaderFile(":/shaders/disc_render.frag");
    firstPassProgram->addShader(new osg::Shader(osg::Shader::VERTEX, firstPassVSSource.data()));
    firstPassProgram->addShader(new osg::Shader(osg::Shader::FRAGMENT, firstPassFSSource.data()));

    auto ss = geode->getOrCreateStateSet();

    //ss->setAttributeAndModes(ssbb.get(), osg::StateAttribute::ON);
    ss->setAttributeAndModes(firstPassProgram.get(), osg::StateAttribute::ON);
    ss->setMode(GL_VERTEX_PROGRAM_POINT_SIZE, osg::StateAttribute::ON);
    //ss->addUniform(nearUni.get()); ss->addUniform(farUni.get());

    progressInfo["visible"] = false;
    QMetaObject::invokeMethod(m_appGlobal, "setProgressInfo", Qt::QueuedConnection, Q_ARG(QVariantMap, progressInfo));

    return  geode.release();
}

osg::Camera *AppWorker::createHUDCamera(bool rtt)
{
    auto viewer = m_appGlobal->property("viewer").value<QuickOSGViewer*>();
    Q_ASSERT(viewer);

    osg::ref_ptr<osg::Camera> hudCamera;
    if(rtt){
        hudCamera = viewer->createRTTCamera();
    }else{
        hudCamera = new osg::Camera;
    }
    hudCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    hudCamera->setProjectionMatrixAsPerspective(45, 1.0, 0.001, 100000);
    hudCamera->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
    hudCamera->setCullingMode(osg::CullSettings::NO_CULLING);
    hudCamera->setViewMatrixAsLookAt(osg::Vec3(0, 10, 0), osg::Vec3(0, 0, 0), osg::Vec3(0, 0, 1));

    return hudCamera.release();
}

osg::Geode *AppWorker::createRectGeode()
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back(osg::Vec3(-1.0f, 0.0f, -1.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, -1.0f));
    vertices->push_back(osg::Vec3(-1.0f, 0.0f, 1.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
    geometry->setVertexArray(vertices.get());
    geometry->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLE_STRIP, 0, vertices->size()));
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geometry.get());

    return geode.release();
}

