#include "qmlredisinterface.h"

QMLRedisInterface::QMLRedisInterface()
{

}

void QMLRedisInterface::init()
{
    //_redisInterface = new RedisInterface(serverUrl(), this);
   //  _redisTool = new RedisTool();
     qDebug() << "[QMLRedisInterface] init() is ok";
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

QVariant QMLRedisInterface::get(const QString key) const
{
    if(this->isComponentComplete())
       // return _redisInterface->get(key);
//       string sss = key.toStdWString();

//        string rely= _redisTool->getString(sss);
//         QString qstr2 = QString::fromStdString(rely);
//         return qstr2;

    return QVariant();

}
