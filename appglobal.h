#ifndef APPGLOBAL_H
#define APPGLOBAL_H

#include <QObject>
#include <QVariantMap>
#include <osg/Node>
#include <osg/Group>
#include <osgDB/ReaderWriter>
#include <osgDB/ReadFile>
#include <QFileInfo>
#include <QThread>

class QuickOSGViewer;
class AppWorker;

class AppGlobal : public QObject
{
    Q_OBJECT
    QString m_language = "en";
    QString m_langToken;
    QVariantMap m_busy = QVariantMap{{"status", false},{"reason", ""}};
    QVariantMap m_progressInfo = QVariantMap{{"visible", false}, {"title", ""},{"from", 0}, {"to", 100}};
    float m_progressValue = 0;
    QThread* m_workerThread = nullptr;
    AppWorker* m_worker = nullptr;

    QuickOSGViewer* m_viewer = nullptr;

public:
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
    Q_PROPERTY(QString langToken READ langToken NOTIFY langTokenChanged)
    Q_PROPERTY(QVariantMap busy READ busy WRITE setBusy NOTIFY busyChanged)
    Q_PROPERTY(QVariantMap progressInfo READ progressInfo WRITE setProgressInfo NOTIFY progressInfoChanged)
    Q_PROPERTY(float progressValue READ progressValue WRITE setProgressValue NOTIFY progressValueChanged)
    Q_PROPERTY(QuickOSGViewer* viewer READ viewer WRITE setViewer NOTIFY viewerChanged)

    explicit AppGlobal(QObject *parent = nullptr);
    ~AppGlobal();

    QString language() const
    {
        return m_language;
    }

    QString langToken() const
    {
        return m_langToken;
    }

    QVariantMap busy() const
    {
        return m_busy;
    }

    QVariantMap progressInfo() const
    {
        return m_progressInfo;
    }

    float progressValue() const
    {
        return m_progressValue;
    }

    QuickOSGViewer* viewer() const
    {
        return m_viewer;
    }

signals:

    void languageChanged(QString language);

    void langTokenChanged(QString langToken);

    void busyChanged(QVariantMap busy);

    void progressInfoChanged(QVariantMap progressInfo);

    void progressValueChanged(float progressValue);
    void modelLoaded(osg::Node* node);
    void errorHappened(QString msg);

    void viewerChanged(QuickOSGViewer* viewer);

public slots:
    void setLanguage(QString language)
    {
        if (m_language == language)
            return;

        m_language = language;
        emit languageChanged(m_language);
    }
    void setBusy(QVariantMap busy)
    {
        if (m_busy == busy)
            return;

        m_busy = busy;
        emit busyChanged(m_busy);
    }
    void setProgressInfo(QVariantMap progressInfo)
    {
        if (m_progressInfo == progressInfo)
            return;

        m_progressInfo = progressInfo;
        emit progressInfoChanged(m_progressInfo);
    }
    void setProgressValue(float progressValue)
    {
        if (qFuzzyCompare(m_progressValue, progressValue))
            return;

        m_progressValue = progressValue;
        emit progressValueChanged(m_progressValue);
    }
    osg::Node* loadModelFile(const QString &filePath){
        auto node = osgDB::readNodeFile(filePath.toStdString());
        return node;
    }
    QString fileSuffix(const QString &filePath) {
        QFileInfo info(filePath);
        return info.suffix();
    }

    void loadRaw(const QString& filePath);
    void loadPointCloud(const QString& filePath);
    void loadObj(const QString& filePath);
    void setViewer(QuickOSGViewer* viewer)
    {
        if (m_viewer == viewer)
            return;

        m_viewer = viewer;
        emit viewerChanged(m_viewer);
    }
};

#endif // APPGLOBAL_H
