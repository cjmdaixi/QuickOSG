#ifndef APPWORKER_H
#define APPWORKER_H

#include <QObject>
#include <QFile>
#include <QtDebug>
#include <osg/Node>
#include <osg/Camera>
#include <osg/PrimitiveSet>
#include <osg/Texture2D>
#include <osg/TextureRectangle>
#include <osg/BufferObject>
#include <osg/BufferIndexBinding>
#include <osg/BindImageTexture>
#include <QVector>

class AppWorker : public QObject
{
    Q_OBJECT
public:
    explicit AppWorker(QObject *appGlobal);

signals:
public slots:
    void loadPointCloud(const QString& filePath);
    void loadObj(const QString& filePath);
private:
    void warning(const QString& msg);
    QByteArray readShaderFile(const QString& filePath);
    osg::Geode* loadPointCloudFile(QFile & file);
    osg::Geode* loadObjFile(QFile & file);
    osg::Camera* createHUDCamera(bool rtt);
    osg::Geode* createRectGeode();
private:
    QObject* m_appGlobal = nullptr;
};

#endif // APPWORKER_H
