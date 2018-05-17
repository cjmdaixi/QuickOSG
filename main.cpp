#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "appglobal.h" 
#include "quickosgviewer.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	qmlRegisterType<AppGlobal>("CppBackend", 1, 0, "AppGlobal");
	qmlRegisterType<QuickOSGViewer>("QuickOSG", 1, 0, "QuickOSGViewer");

	auto engine = new QQmlApplicationEngine();

	engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
	auto result = app.exec();

	delete engine;
	return result;
}
