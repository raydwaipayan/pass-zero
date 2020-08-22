#ifndef PASSZERO_H
#define PASSZERO_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class passzero; }
QT_END_NAMESPACE

class passzero : public QMainWindow {
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
    void clearDataView();
    void updateDataView();
    void clearData();
    void setView(const bool&);
    void changeMasterKey();
    void rotateDbKey();
    void on_textPassword_textChanged(const QString&);
    void on_btnNewEntry_released();
    void on_btnDelete_released();
    void on_textLabel_textChanged(const QString& arg1);
    void on_textUsername_textChanged(const QString& arg1);
    void on_textNote_textChanged();
    void on_listWidget_currentRowChanged(int currentRow);

private:

    Ui::passzero *ui;
    database *db;
    QString currentfile;
    int curidx;
    bool delproc;
};
#endif // PASSZERO_H
