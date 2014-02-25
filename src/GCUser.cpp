#include "GCUser.h"

GCUser::GCUser(QObject *parent) : QObject(parent)
{
    userName = QString("stigbd");
    password = QString("secret");

    getResponse();
}

void GCUser::getResponse()
{
    return;
}
