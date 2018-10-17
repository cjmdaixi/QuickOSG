#include "appglobal.h"
#include "appworker.h"

AppGlobal::AppGlobal(QObject *parent) : QObject(parent)
{
    m_workerThread = new QThread(this);
    m_worker = new AppWorker(this);
    m_worker->moveToThread(m_workerThread);
    connect(m_workerThread, &QThread::finished, m_worker, &QObject::deleteLater);

    m_workerThread->start();
}

AppGlobal::~AppGlobal()
{
    m_workerThread->quit();
    m_workerThread->wait();
}

void AppGlobal::loadPointCloud(const QString &filePath)
{
    QMetaObject::invokeMethod(m_worker, "loadPointCloud", Qt::QueuedConnection, Q_ARG(QString, filePath));
}

void AppGlobal::loadObj(const QString &filePath)
{
    QMetaObject::invokeMethod(m_worker, "loadObj", Qt::QueuedConnection, Q_ARG(QString, filePath));
}

