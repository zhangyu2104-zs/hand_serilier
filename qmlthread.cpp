#include "qmlthread.h"
#include <QObject>

dataModel::dataModel(QObject* parent)
{
}

void dataModel::devicework()
{
  mydevice= new Devicedriver();
  QString strVar;
  strVar="hello world";
 // int infrare =  myDevice->get_infrared_range_left();
 // strVar::number(infrare,10)
  QJsonObject tempdata;
  tempdata.insert("name",strVar);
  
  emit dataReady(tempdata);
}

void dataModel::deviceclose()
{
 
    delete mydevice;
}



QmlThread::QmlThread(QObject* parent)
{
    m_mode.moveToThread(&m_thread); //加入到子线程

    connect(&m_thread,&QThread::started,&m_mode,&dataModel::devicework); //一旦线程开始，就调用接收Tcp的函数
    connect(&m_mode,&dataModel::dataReady,this,&QmlThread::dataChangedSlot);
    connect(&m_thread,&QThread::finished,&m_mode,&dataModel::deviceclose); //线程结束时关闭socket，删除申请内存
    m_thread.start(); //开启子线程
}

QmlThread::~QmlThread()
{
    m_thread.exit();
    m_thread.wait();
}

void QmlThread::dataChangedSlot(QJsonObject msg)
{
    m_data=msg;
    emit dataChanged();
}
