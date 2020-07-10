#ifndef DATAITEM_H
#define DATAITEM_H

#include <string>
#include <QDataStream>
class dataitem{

private:
    QString label;
    QString user;
    QString pass;
    QString note;
public:
    dataitem(){}
    dataitem(QString l, QString u, QString p, QString n): label(l), user(u), pass(p),note(n){}
    void setData(QString label, QString user, QString pass, QString note);
    QString getUser();
    QString getPass();
    QString getNote();
    QString getLabel();

    friend QDataStream &operator <<(QDataStream &stream, const dataitem &dt);
    friend QDataStream &operator >>(QDataStream &stream, dataitem &dt);
};

#endif // DATAITEM_H
