#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qmlredisinterface.h"
#include <qthread.h>


/*创建一个线程类*/
class MyThread : public QThread   //这里创建一个线程的类，
{                                 // 该类继承于QThread,其中只有一个函数run
    public:
    QMLRedisInterface qmlredis  ;
    virtual void run();    //run函数式该线程的执行函数，也就是说，
                            //只要这个线程被启动，那么该函数就会被调用
};

/*一个线程的主函数，循环打印一句话*/
void MyThread::run()
{
    while(1)
    {
        qmlredis.init();
        QVariant tempdata;
       tempdata = qmlredis.get("lihaoran");
       qmlredis.setValue(tempdata.toString());
     //  qmlredis.setServerUrl(tempdata);
       qDebug() << "thread id :" << QThread::currentThreadId();
      sleep(1);

    }
}


int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

     qmlRegisterType<QMLRedisInterface>("Redis", 1, 0, "RedisInterface");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

 //   MyThread thread;
   // thread.start();

    return app.exec();
}
