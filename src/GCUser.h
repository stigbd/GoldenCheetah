#ifndef GCUSER_H
#define GCUSER_H

#include "GoldenCheetah.h"
#include <QObject>

class GCUser : public QObject
{
    Q_OBJECT
    G_OBJECT

    public:
        explicit GCUser(QObject *parent = 0);

signals:
    void completed();

public slots:
    //void getResponse();

private:
    QString userName;
    QString password;
    void getResponse();
};

#endif // GCUSER_H

