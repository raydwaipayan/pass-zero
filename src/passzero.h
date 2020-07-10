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
    void open();
    void saveAs();
    void newFile();
    void reset();

    void on_btnAdd_clicked();

private:
    Ui::passzero *ui;
    QVector<dataitem> data;
    QString currentfile;
};
#endif // PASSZERO_H
