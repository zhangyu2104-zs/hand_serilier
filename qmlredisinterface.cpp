#include "qmlredisinterface.h"
#include <iostream>
#include <stdio.h>
using namespace std;
QMLRedisInterface::QMLRedisInterface()
{

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
       // return _redisInterface->get(key);
    //    return redis->get("key");
  //  return QVariant();
     qDebug() << "GET:" << redis->get(key);

    // cout<<redis->get(key)<<endl;
        return redis->get(key);;

}
