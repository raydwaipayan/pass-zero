#include "dataitem.h"

void dataitem::setData(const QString &label, const QString &user, const QString &pass, const QString &note)
{
    this->label=label;
    this->user=user;
    this->pass=pass;
    this->note=note;
}
dataitem::dataitem(const dataitem &rhs)
{
    this->label=rhs.label;
    this->user=rhs.user;
    this->pass=rhs.pass;
    this->note=rhs.note;
}
dataitem& dataitem::operator=(const dataitem &rhs)
{
    if(this==(&rhs))
        return (*this);

    this->label=rhs.label;
    this->user=rhs.user;
    this->pass=rhs.pass;
    this->note=rhs.note;
    return (*this);
}
void dataitem::setUser(const QString &user)
{
    this->user=user;
}
void dataitem::setPass(const QString &pass)
{
    this->pass=pass;
}
void dataitem::setNote(const QString &note)
{
    this->note=note;
}
void dataitem::setLabel(const QString &label)
{
    this->label=label;
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
