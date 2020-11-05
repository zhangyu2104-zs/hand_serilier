#ifndef QMLTHREAD_H
#define QMLTHREAD_H

#include <QObject>

class QmlThread : public QObject
{
    Q_OBJECT
public:
    explicit QmlThread(QObject *parent = nullptr);

signals:

};

#endif // QMLTHREAD_H
