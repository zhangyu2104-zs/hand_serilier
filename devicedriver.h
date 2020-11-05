#ifndef DEVICEDRIVER_H
#define DEVICEDRIVER_H

#include <QObject>

class devicedriver : public QObject
{
    Q_OBJECT
public:
    explicit devicedriver(QObject *parent = nullptr);

signals:

};

#endif // DEVICEDRIVER_H
