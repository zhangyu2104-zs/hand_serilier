#include "qmlredisinterface.h"
#include <iostream>
#include <stdio.h>
#include <QTimer>

using namespace std;
QMLRedisInterface::QMLRedisInterface()
{
    m_startValue = 0;
    m_endValue = 1000;

    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(addValueTimeout()));

    m_timer->start(5);

}

void QMLRedisInterface::init()
{

    redis = new qRedis("127.0.0.1",6379);
     qDebug() << "[QMLRedisInterface] init() is ok";
     qRedis::Reply reply;

     if (!redis->openConnection())
     {
         qDebug() << "Could not connect to server...";
         exit(0);
     }

     qDebug() << "Connected to server...";

}

QString QMLRedisInterface::serverUrl() const
{
    return _serverUrl;
}

void QMLRedisInterface::setServerUrl(const QString& value)
{
    if(_serverUrl != value)
    {
        _serverUrl = value;
        emit serverUrlChanged(value);
    }
}

  Q_INVOKABLE QVariant QMLRedisInterface::get(const QString& key) const
{
    if(this->isComponentComplete())

     qDebug() << "GET:" << redis->get(key);

        return redis->get(key);;

}

 QString QMLRedisInterface::value() const
{
     qDebug() << "value--:" << _value;
    return _value;
}

void QMLRedisInterface::setValue(const QString &value)
{
    if(this->_value != value) {
        this->_value = value;
        emit valueChanged();
    }

}

int QMLRedisInterface::getCurrentValue()
{
    return ((double)m_startValue / (double)m_endValue) * 10;
}

void QMLRedisInterface::addValueTimeout()
{
   m_startValue++;
//    if(m_startValue >= m_endValue){

//        m_timer->stop();
//    }
}
