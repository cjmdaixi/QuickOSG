#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSurfaceFormat>
#include "appglobal.h"
#include "quickosgviewer.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QGuiApplication app(argc, argv);

    // 注册QML模块
    qmlRegisterType<AppGlobal>("CppBackend", 1, 0, "AppGlobal");
    qmlRegisterType<QuickOSGViewer>("QuickOSG", 1, 0, "QuickOSGViewer");

    auto engine = new QQmlApplicationEngine();
    engine->addImportPath(QLatin1Literal("qrc:/"));

    // 构造app全局变量，将engine传入该全局变量构造函数
    auto appGlobal = new AppGlobal(engine);

    engine->rootContext()->setContextProperty("$app", appGlobal);
    engine->rootContext()->setContextProperty("$applicationPath", app.applicationDirPath());

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));

    auto result = app.exec();

    delete engine;
    return result;
}
