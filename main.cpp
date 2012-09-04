#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "cpwatcher.h"
#include <QDebug>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative>
#include "missionitem.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    CPWatcher *cp = new CPWatcher(0);
    qDebug() << "cp";

    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("cp", cp);
    qmlRegisterType<MissionItem>("missions", 1, 0, "MissionItem");
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/warri/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
