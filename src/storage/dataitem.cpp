#include "dataitem.h"

void zero::dataitem::setData(const QString& label,
                             const QString& user,
                             const QString& pass,
                             const QString& note)
{
    this->label = label;
    this->user  = user;
    this->pass  = pass;
    this->note  = note;
}

zero::dataitem::dataitem(const dataitem& rhs)
{
    this->label = rhs.label;
    this->user  = rhs.user;
    this->pass  = rhs.pass;
    this->note  = rhs.note;
}

zero::dataitem& zero::dataitem::operator=(const dataitem& rhs)
{
    if (this == (&rhs)) return *this;

    this->label = rhs.label;
    this->user  = rhs.user;
    this->pass  = rhs.pass;
    this->note  = rhs.note;
    return *this;
}

void zero::dataitem::setUser(const QString& user)
{
    this->user = user;
}

void zero::dataitem::setPass(const QString& pass)
{
    this->pass = pass;
}

void zero::dataitem::setNote(const QString& note)
{
    this->note = note;
}

void zero::dataitem::setLabel(const QString& label)
{
    this->label = label;
}

QString zero::dataitem::getUser()
{
    return user;
}

QString zero::dataitem::getPass()
{
    return pass;
}

QString zero::dataitem::getNote()
{
    return note;
}

QString zero::dataitem::getLabel()
{
    return label;
}

QDataStream& zero::operator<<(QDataStream& stream, const zero::dataitem& dt)
{
    stream << dt.label;
    stream << dt.user;
    stream << dt.pass;
    stream << dt.note;
    return stream;
}

QDataStream& zero::operator>>(QDataStream& stream, zero::dataitem& dt)
{
    stream >> dt.label;
    stream >> dt.user;
    stream >> dt.pass;
    stream >> dt.note;
    return stream;
}
