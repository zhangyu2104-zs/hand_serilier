#ifndef QMLTHREAD_H
#define QMLTHREAD_H

#include <QThread>
#include "devicedriver.h"
#include "device_pi.h"
#include <QVariant>
#include <QJsonObject>

class dataModel:public QObject  //实现功能的类
{
    Q_OBJECT
public:
    dataModel(QObject* parent=nullptr);

signals:
    void dataReady(QJsonObject data);  //通知MoveToThread类,数据接收

public slots:
    void  devicework();
    void  deviceclose();

private:
    device_pi* myDevice;
    QString msg;
};

//将TcpModel在QML初始化时移入到子线程
class QmlThread: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QJsonObject m_data MEMBER m_data)
public:
    QmlThread(QObject* parent=nullptr);
    ~QmlThread();

signals:
    void dataChanged();   //用于通知QML应用，数据接收到


public slots:
    void dataChangedSlot(QJsonObject msg);

private:
    QThread m_thread;  //定义的线程
    dataModel m_mode;  //定义的TCP类，这样就能在TcpMoveToThread构造函数中将其移入新的线程
    QJsonObject m_data;  //保存接收数据
};


#endif // QMLTHREAD_H
