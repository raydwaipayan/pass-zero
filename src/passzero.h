#ifndef PASSZERO_H
#define PASSZERO_H

#include <QMainWindow>

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

    void on_buttonCreate_released();
    void on_buttonOpen_released();

private:
    Ui::passzero *ui;
};
#endif // PASSZERO_H
