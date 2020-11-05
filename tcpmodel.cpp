#include "tcpmodel.h"
#include <QObject>

TcpModel::TcpModel(QObject* parent)
{
}

void TcpModel::tcpWork()
{
    m_socket=new QTcpSocket();
    m_socket->connectToHost("192.168.3.10",8000);
    if(m_socket->waitForConnected(-1))
    {
        while(1)
        {
            if(m_socket->waitForReadyRead())
            {
                QByteArray res=m_socket->readAll();
                msg=QString::fromLocal8Bit(res.data());
                emit dataRecved(msg); //接收完成信号
            }
        }
    }
}

void TcpModel::tcpClose()
{
    m_socket->close();
    delete m_socket;
}



TcpMoveToThread::TcpMoveToThread(QObject* parent)
{
    m_tcp.moveToThread(&m_thread); //加入到子线程

    connect(&m_thread,&QThread::started,&m_tcp,&TcpModel::tcpWork); //一旦线程开始，就调用接收Tcp的函数
    connect(&m_tcp,&TcpModel::dataRecved,this,&TcpMoveToThread::dataChangedSlot);
    connect(&m_thread,&QThread::finished,&m_tcp,&TcpModel::tcpClose); //线程结束时关闭socket，删除申请内存
    m_thread.start(); //开启子线程
}

TcpMoveToThread::~TcpMoveToThread()
{
    m_thread.exit();
    m_thread.wait();
}

void TcpMoveToThread::dataChangedSlot(QString msg)
{
    m_data=msg;
    emit dataChanged();
}
