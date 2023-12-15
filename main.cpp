#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "backendmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    BackendModel backendModel(&app);
    engine.rootContext()->setContextProperty("cBackendModel", &backendModel);
    const QUrl url(u"qrc:/untitled/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
