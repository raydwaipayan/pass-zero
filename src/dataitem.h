#ifndef DATAITEM_H
#define DATAITEM_H

#include <string>
#include <QDataStream>
class dataitem{

private:
    QString user;
    QString pass;
    QString note;
public:
    dataitem(){}
    dataitem(QString u, QString p, QString n): user(u), pass(p),note(n){}
    void setDate(QString user, QString pass, QString note);
    QString getUser();
    QString getPass();
    QString getNote();

    friend QDataStream &operator <<(QDataStream &stream, const dataitem &dt);
    friend QDataStream &operator >>(QDataStream &stream, dataitem &dt);
};

#endif // DATAITEM_H
