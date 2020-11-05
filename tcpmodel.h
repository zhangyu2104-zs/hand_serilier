#ifndef TCPMODEL_H
#define TCPMODEL_H
#include <QTcpSocket>
#include <QThread>

class TcpModel:public QObject  //实现TCP功能的类
{
    Q_OBJECT
public:
    TcpModel(QObject* parent=nullptr);


signals:
    void dataRecved(QString data);  //通知TcpMoveToThread类,数据接收

public slots:
    void tcpWork();
    void tcpClose();

private:
    QTcpSocket* m_socket;
    QString msg;
};

//将TcpModel在QML初始化时移入到子线程
class TcpMoveToThread: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_data MEMBER m_data)
public:
    TcpMoveToThread(QObject* parent=nullptr);
    ~TcpMoveToThread();

signals:
    void dataChanged();   //用于通知QML应用，数据接收到


public slots:
    void dataChangedSlot(QString msg);

private:
    QThread m_thread;  //定义的线程
    TcpModel m_tcp;  //定义的TCP类，这样就能在TcpMoveToThread构造函数中将其移入新的线程
    QString m_data;  //保存接收数据
};

#endif // TCPMODEL_H
