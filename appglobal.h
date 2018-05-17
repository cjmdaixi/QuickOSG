#ifndef _APP_GLOBAL_H
#define _APP_GLOBAL_H

#include <QObject>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QColor>
#include <QThread>
#include <QVariantMap>
#include <QQuickItem>
#include <QTimer>
#include <QSysInfo>
#include <QVersionNumber>
#include <osg/Node>
#include <osg/Group>
#include <osgDB/ReaderWriter>

class AppGlobal : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString fontAwesome READ fontAwesome CONSTANT)
    Q_PROPERTY(QString fontFamily MEMBER m_fontFamily NOTIFY fontFamilyChanged)

	Q_PROPERTY(int majorVersion READ majorVersion CONSTANT)
	Q_PROPERTY(int minorVersion READ minorVersion CONSTANT)
	Q_PROPERTY(int patchVersion READ patchVersion CONSTANT)
	Q_PROPERTY(QString version READ version CONSTANT)

	Q_PROPERTY(osg::Node* sceneNode READ sceneNode NOTIFY sceneNodeChanged)

    explicit AppGlobal(QObject *parent = 0);
    ~AppGlobal();

    QString fontAwesome() const;
    Q_INVOKABLE QString iconText(QString iconName) const;

	int majorVersion() const { return m_version.majorVersion(); }
	int minorVersion() const { return m_version.minorVersion(); }
	int patchVersion() const { return m_version.microVersion(); }
	QString version() const { return m_version.toString(); }

	osg::Node* sceneNode() const { return m_sceneNode.get(); }
public slots:
	osg::Node* loadModelFile(const QString &filePath);
signals:
    void fontFamilyChanged();

    void minimize();
    void maximize();
	void tryQuit();
    void quit();

	void sceneNodeChanged();
private slots:

private:
	void setupAwesomeFont();
	void setupActions();
private:
    int m_faId = -1;
    QMap<QString, QString> m_faMapping;
    QString m_fontFamily = "Microsoft YaHei UI";

	QVersionNumber m_version = QVersionNumber(MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION);
	osg::ref_ptr<osg::Group> m_sceneNode;
};

#endif // _APP_GLOBAL_H
