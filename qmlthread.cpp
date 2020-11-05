#include "qmlthread.h"
#include <QObject>
#include <wiringPi.h>

#define constrain(value,low,high)((value)<(low)?(low):((value)>(high)?(high):(value)))

dataModel::dataModel(QObject* parent)
{
}

void dataModel::devicework()
{
  myDevice= new device_pi();

 // int infrare =  myDevice->get_infrared_range_left();
 // strVar::number(infrare,10)
/*
    myDB.temp = myDevice.get_temperature_sensor_left();
    myDB.infrared[0] =   myDevice.get_infrared_range_left();
    myDB.infrared[1] =   myDevice.get_infrared_range_right();
    myDB.key_start   =   myDevice.get_keyValue_start();
    myDB.fan[0]      =   myDevice.get_fan_left_status();
    myDB.ad_power[0] =   myDevice.get_supply_power_48V();
    myDB.ad_power[1] =   myDevice.get_supply_power_5V();
    myDB.key_start   =   myDevice.get_keyValue_start();
    myDB.fan[0]      =   myDevice.get_fan_left_status();
    myDB.uvc_value   =   myDevice.get_UVC_status();
*/
  while(1)
  {
    QJsonObject tempdata;
    tempdata.insert("temp",myDevice->get_temperature_sensor_left());
    tempdata.insert("infrared_left",constrain(myDevice->get_infrared_range_left(),-55.0,125.0));
 
    emit dataReady(tempdata);
  
    delay(3000);
 }
}

void dataModel::deviceclose()
{
 
    delete myDevice;
}



QmlThread::QmlThread(QObject* parent)
{
    m_mode.moveToThread(&m_thread); //加入到子线程
    connect(&m_thread,&QThread::started,&m_mode,&dataModel::devicework); //一旦线程开始，就调用接收的函数
    connect(&m_mode,&dataModel::dataReady,this,&QmlThread::dataChangedSlot);
    connect(&m_thread,&QThread::finished,&m_mode,&dataModel::deviceclose); //线程结束时关闭，删除申请内存
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
