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

public:
    QMLRedisInterface();
    ~QMLRedisInterface();

     typedef struct Reply {
        QString type;
        QString message;
        QString pattern;
        QString channel;
        QVariant value;
    } Reply;

    //通过Q_INVOKABLE宏标记的public函数可以在QML中访问
     Q_INVOKABLE QVariant get(const QString& key) const;
    Q_INVOKABLE bool insertKey(QString key ,QString value);
     Q_INVOKABLE void calldata(void);


signals:
     void begin(const QString &strDemo);



public slots:
     bool openCon();
     void Control(QString key,QString value);
     
private:
       qRedis *redis;
};

QML_DECLARE_TYPE(QMLRedisInterface)


#endif // QMLREDISINTERFACE_H
