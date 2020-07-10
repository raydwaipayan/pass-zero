#include "dataitem.h"

void dataitem::setData(QString label, QString user, QString pass, QString note)
{
    this->label=label;
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
QString dataitem::getLabel()
{
    return label;
}

QDataStream &operator <<(QDataStream &stream, const dataitem &dt)
{
    stream<<dt.label;
    stream<<dt.user;
    stream<<dt.pass;
    stream<<dt.note;
    return stream;
}
QDataStream &operator >>(QDataStream &stream, dataitem &dt)
{
    stream>>dt.label;
    stream>>dt.user;
    stream>>dt.pass;
    stream>>dt.note;
    return stream;
}
