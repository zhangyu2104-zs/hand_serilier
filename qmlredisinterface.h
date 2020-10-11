#ifndef QMLREDISINTERFACE_H
#define QMLREDISINTERFACE_H

#include <QQuickItem>
#include <QDebug>



class QMLRedisInterface : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString  serverUrl            READ serverUrl            WRITE setServerUrl            NOTIFY serverUrlChanged )
public:
    QMLRedisInterface();

    QString serverUrl() const;

    //通过Q_INVOKABLE宏标记的public函数可以在QML中访问
     Q_INVOKABLE void init(); //初始化 redis接口
     Q_INVOKABLE QVariant get(const QString key) const;

signals:
     void serverUrlChanged(const QString& value);

public slots:
      void setServerUrl(const QString& value);

private:
       QString _serverUrl;

       // RedisInterface* _redisInterface;
//       RedisTool* _redisTool;

};

QML_DECLARE_TYPE(QMLRedisInterface)


#endif // QMLREDISINTERFACE_H
