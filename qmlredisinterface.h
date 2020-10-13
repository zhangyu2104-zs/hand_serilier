#ifndef QMLREDISINTERFACE_H
#define QMLREDISINTERFACE_H

#include <QQuickItem>
#include <QDebug>
#include "qRedis.h"

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

class QMLRedisInterface : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString  serverUrl            READ serverUrl            WRITE setServerUrl            NOTIFY serverUrlChanged )
    Q_PROPERTY(QString  value                READ value                WRITE setValue                  NOTIFY valueChanged)
public:
    QMLRedisInterface();

    QString serverUrl() const;
    QString  value()  const;

    //通过Q_INVOKABLE宏标记的public函数可以在QML中访问
     Q_INVOKABLE void init(); //初始化 redis接口
     Q_INVOKABLE QVariant get(const QString& key) const;

     Q_INVOKABLE int getCurrentValue();

signals:
     void serverUrlChanged(const QString& value);
      void valueChanged();

public slots:
      void setServerUrl(const QString& value);
      void setValue(const QString &value);
      void addValueTimeout();
private:
       QString _serverUrl;
       QString _value;
       qRedis *redis;

       QTimer *m_timer;
        int m_startValue;
        int m_endValue;
};

QML_DECLARE_TYPE(QMLRedisInterface)


#endif // QMLREDISINTERFACE_H
