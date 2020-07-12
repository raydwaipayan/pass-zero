#ifndef PASSZERO_H
#define PASSZERO_H

#include <QMainWindow>
#include "dataitem.h"
#include <QListWidgetItem>

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
    void changeActive(const QString &, const QString &, const QString &, const QString &);
    void clearContext();

    void on_textPassword_textChanged(const QString &arg1);

    void on_btnNewEntry_released();

    void on_btnDelete_released();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::passzero *ui;
    QVector<dataitem> data;
    QString currentfile;
    QString label, user, pass, note;
};
#endif // PASSZERO_H
