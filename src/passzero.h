#ifndef PASSZERO_H
#define PASSZERO_H

#include <QMainWindow>
#include "dataitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class passzero; }
QT_END_NAMESPACE

class passzero : public QMainWindow
{
    Q_OBJECT

public:
    passzero(QWidget *parent = nullptr);
    ~passzero();
private slots:
    void exit();
    void about();
    void save();

    void on_buttonCreate_released();
    void on_buttonOpen_released();

private:
    Ui::passzero *ui;
    QVector<dataitem> data;
    QString currentfile;
};
#endif // PASSZERO_H
