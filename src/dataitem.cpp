#include "dataitem.h"

void dataitem::setDate(QString user, QString pass, QString note)
{
    this->user=user;
    this->pass=pass;
    this->note=note;
}

QString dataitem::getUser()
{
    return user;
}

QString dataitem::getPass()
{
    return pass;
}

QString dataitem::getNote()
{
    return note;
}

QDataStream &operator <<(QDataStream &stream, const dataitem &dt)
{
    stream<<dt.user;
    stream<<dt.pass;
    stream<<dt.note;
    return stream;
}
QDataStream &operator >>(QDataStream &stream, dataitem &dt)
{
    stream>>dt.user;
    stream>>dt.pass;
    stream>>dt.note;
    return stream;
}
