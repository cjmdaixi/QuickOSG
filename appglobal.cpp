#include "appglobal.h"
#include <QCoreApplication>
#include <QQmlEngine>
#include <QtDebug>
#include <QFontDatabase>
#include <QImage>
#include <QFileInfo>
#include <QQmlContext>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

AppGlobal::AppGlobal(QObject *parent)
    : QObject(parent)
{
    setupActions();
    setupAwesomeFont();
}

AppGlobal::~AppGlobal()
{
    QFontDatabase::removeApplicationFont(m_faId);
}

void AppGlobal::setupActions()
{

}

void AppGlobal::setupAwesomeFont()
{
    m_faId = QFontDatabase::addApplicationFont(":/fonts/FontAwesome.otf");
    if (m_faId == -1)
    {
        qInfo() << "Cannot load fontawesome font!";
    }

    m_faMapping =
    {
        { QLatin1Literal("search"), QString::fromWCharArray(L"\uf002") },
        { QLatin1Literal("game"), QString::fromWCharArray(L"\uf11b") },
        { QLatin1Literal("heart"), QString::fromWCharArray(L"\uf004") },
        { QLatin1Literal("cog"), QString::fromWCharArray(L"\uf013") },
        { QLatin1Literal("file"), QString::fromWCharArray(L"\uf15b") },
        { QLatin1Literal("check"), QString::fromWCharArray(L"\uf00c") },
        { QLatin1Literal("circle"), QString::fromWCharArray(L"\uf111") },
        { QLatin1Literal("minimize"), QString::fromWCharArray(L"\uf2d1") },
        { QLatin1Literal("maximize"), QString::fromWCharArray(L"\uf2d0") },
        { QLatin1Literal("open"), QString::fromWCharArray(L"\uf115") },
        { QLatin1Literal("close"), QString::fromWCharArray(L"\uf2d4") },
        { QLatin1Literal("save"), QString::fromWCharArray(L"\uf0c7") },
        { QLatin1Literal("cancel"), QString::fromWCharArray(L"\uf00d") },
        { QLatin1Literal("restore"), QString::fromWCharArray(L"\uf0e2") },
        { QLatin1Literal("new"), QString::fromWCharArray(L"\uf0f6") },
        { QLatin1Literal("start"), QString::fromWCharArray(L"\uf1d8") },
        { QLatin1Literal("delete"), QString::fromWCharArray(L"\uf014") },
        { QLatin1Literal("batch"), QString::fromWCharArray(L"\uf1d9") },
        { QLatin1Literal("add"), QString::fromWCharArray(L"\uf067") },
        { QLatin1Literal("left"), QString::fromWCharArray(L"\uf100") },
        { QLatin1Literal("right"), QString::fromWCharArray(L"\uf101") },
        { QLatin1Literal("home"), QString::fromWCharArray(L"\uf015") },
        { QLatin1Literal("minus"), QString::fromWCharArray(L"\uf068") },
        { QLatin1Literal("plus"), QString::fromWCharArray(L"\uf067") },

        { QLatin1Literal("clock"), QString::fromWCharArray(L"\uf017") },
        { QLatin1Literal("location"), QString::fromWCharArray(L"\uf124") },
        { QLatin1Literal("leaf"), QString::fromWCharArray(L"\uf06c") },
        { QLatin1Literal("taskName"), QString::fromWCharArray(L"\uf0ae") },
        { QLatin1Literal("layerCount"), QString::fromWCharArray(L"\uf0c9") },
        { QLatin1Literal("layerIndex"), QString::fromWCharArray(L"\uf2a1") },
        { QLatin1Literal("thermo"), QString::fromWCharArray(L"\uf2c8") },
        { QLatin1Literal("circleon"), QString::fromWCharArray(L"\uf111") },
        { QLatin1Literal("circleoff"), QString::fromWCharArray(L"\uf10c") },
        { QLatin1Literal("model"), QString::fromWCharArray(L"\uf085") },
        { QLatin1Literal("disconnect"), QString::fromWCharArray(L"\uf127") },
        { QLatin1Literal("pause"), QString::fromWCharArray(L"\uf04c") },
        { QLatin1Literal("stop"), QString::fromWCharArray(L"\uf04d") },
		{ QLatin1Literal("file white"), QString::fromWCharArray(L"\uf016") },
    };
}

QString AppGlobal::fontAwesome() const
{
    QString faFamily;
    if (m_faId == -1)
    {
        qInfo() << "fontawesome font not loaded! Use YaHei instead...";
        faFamily = QLatin1Literal("Microsoft YaHei UI");
    }
    else
    {
        faFamily = QFontDatabase::applicationFontFamilies(m_faId).front();
    }
    return faFamily;
}

QString AppGlobal::iconText(QString iconName) const
{
    return m_faMapping.value(iconName, QString::fromWCharArray(L"\uf111"));
}


osg::Node * AppGlobal::loadModelFile(const QString & filePath)
{
	auto node = osgDB::readNodeFile(filePath.toStdString());
	return node;
}