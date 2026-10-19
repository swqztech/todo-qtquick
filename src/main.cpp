#include "todocontroller.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

int main(int argc, char* argv[]) {
  QGuiApplication app(argc, argv);
  QQuickStyle::setStyle(QStringLiteral("Basic"));
  app.setApplicationName(QStringLiteral("墨迹清单"));
  app.setOrganizationName(QStringLiteral("swqztech"));

  TodoController controller;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty(QStringLiteral("Todo"), &controller);
  QObject::connect(
      &controller, &TodoController::message, &engine,
      [](const QString& msg) { qInfo("%s", qUtf8Printable(msg)); });
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule(QStringLiteral("TodoApp"), QStringLiteral("Main"));

  return app.exec();
}
