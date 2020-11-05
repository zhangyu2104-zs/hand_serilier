#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qmlredisinterface.h"
#include <qthread.h>
#include "devicedriver.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>
#include "qmlthread.h"
#include "qthread.h"
#include <QQmlContext>
#include <QtQml>
#include "tcpmodel.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

     qmlRegisterType<QMLRedisInterface>("Redis", 1, 0, "RedisInterface");
     qmlRegisterType<QmlThread>("QmlThread", 1, 0, "QmlThread");

    qmlRegisterType<TcpMoveToThread>("TcpMoveToThread",1,0,"TcpMoveToThread");  //注册QML类

    QQmlApplicationEngine engine;
    QMLRedisInterface qmlredisinterface;
    engine.rootContext()->setContextProperty("qmlredisinterface",&qmlredisinterface);
    
    QQmlComponent component(&engine,QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *object = component.create();
    
   QObject::connect(object,SIGNAL(qmlSignal(QString,QString)),&qmlredisinterface,SLOT(Control(QString,QString)));
   // QMetaObject::invokeMethod(object,"getMessage");
  //  QObject::connect(&qmlrediscontrol,&QQmlApplicationEngine::begin,&qmlrediscontrol,&QQmlApplicationEngine::doSomething);
    
    
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);
    
//    QObject *pRoot = engine.rootObjects().first();
//    QMLRedisInterface *qmlrediss= pRoot->findChild<QMLRedisInterface*>("redisInterface");
//    qmlrediss->doSomething();

/*
   MyThread *thread = new MyThread();
    QObject::connect(thread,&MyThread::finished,thread,&QObject::deleteLater);
  //  QObject::connect(thread,&MyThread::finished,this,&QObject::threadFinished);
   if(thread->isRunning())
   {
       qDebug()<<"thread is processing";
       //return;
       }
    QObject::connect(thread, SIGNAL(MyThread::baseData_return()), thread,SLOT(MyThread::dataChangedSlot()));
    
    thread->start();
*/
    return app.exec();
}


