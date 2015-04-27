#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
#ifdef Q_OS_ANDROID
	engine.addImportPath("/imports/");
	engine.addPluginPath(QDir::homePath()+"../lib"
#else
	engine.addImportPath(QDir::currentPath()+"/imports/");
	engine.addPluginPath(QDir::currentPath()+"/lib");
#endif
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
