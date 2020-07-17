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
    ~dataitem(){}
    dataitem(const dataitem&);
    dataitem& operator=(const dataitem &);
    dataitem(QString l, QString u, QString p, QString n): label(l), user(u), pass(p),note(n){}
    void setData(const QString &label,const QString &user, const QString &pass, const QString &note);
    void setUser(const QString &);
    void setPass(const QString &);
    void setNote(const QString &);
    void setLabel(const QString &);
    QString getUser();
    QString getPass();
    QString getNote();
    QString getLabel();

    friend QDataStream &operator <<(QDataStream &stream, const dataitem &dt);
    friend QDataStream &operator >>(QDataStream &stream, dataitem &dt);
};

#endif // DATAITEM_H
