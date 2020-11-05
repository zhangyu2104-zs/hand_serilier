#include "qmlredisinterface.h"
#include <iostream>
#include <stdio.h>
#include <QTimer>

using namespace std;
QMLRedisInterface::QMLRedisInterface()
{
   redis = new qRedis("127.0.0.1",6379);
   //connect(redis, SIGNAL(returnData(qRedis::Reply)), this, SLOT(calldata()));
   qDebug()<<"[QMLRedsInterface] create redis.object--"<<redis<<"qmlredis object--"<<this;
}
QMLRedisInterface::~QMLRedisInterface()
{
    qDebug()<<"[QMLRedsInterface] delete redis.object---"<<redis<<"qmlredis object---"<<this;
    delete this->redis;
    delete this;
}

bool QMLRedisInterface::openCon( )
{
     if (!redis->openConnection())
     {
         qDebug() << "Could not connect to server...";
         exit(0);
         return false;
     }

     qDebug() << "Connected to server...";
     return true;
}

 void QMLRedisInterface::calldata(void)
{
     //QString qv = this->redis->get("lihaoran");
    // connect(this, SIGNAL(returnData(qRedis::Reply)), this, SLOT(calldata()));
   //  QString tempdata=qv.toString();
    //qDebug() << "tempdata--";
     emit begin("100");
}

  Q_INVOKABLE QVariant QMLRedisInterface::get(const QString& key) const
{
    if(this->isComponentComplete())

     qDebug() << "GET:" << redis->get(key);
        return redis->get(key);
}
Q_INVOKABLE bool QMLRedisInterface::insertKey(QString key ,QString value)
{
  if(this->isComponentComplete())
   //   qDebug() << "SET:" << redis->set(key,value);
    return true;

}

void QMLRedisInterface::Control(QString key,QString value)
{
     if(key=="uvc_out"){
         qDebug()<< "[dosomething]=="<<key<<"----"<<value;    //chushihuashuju yuliu
         insertKey(key,value);
    }
}





