#include "passzero.h"
#include "ui_passzero.h"

#include <QMessageBox>

passzero::passzero(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::passzero)
{
    ui->setupUi(this);
    ui->textEdit->setTextInteractionFlags(Qt::NoTextInteraction);

    connect(ui->actionAbout, &QAction::triggered, this, &passzero::about);
    connect(ui->actionExit, &QAction::triggered, this, &passzero::exit);
}

passzero::~passzero()
{
    delete ui;
}
void passzero::exit()
{
    QMessageBox msgbox;
    msgbox.setText("Are you sure youw ant to Quit?");
    msgbox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
    int ret=msgbox.exec();
    if(ret==QMessageBox::Yes)
        QApplication::exit();
}
void passzero::about()
{
    QMessageBox msgbox;
    msgbox.setText("Ultra Secure lightweight password manager");
    msgbox.setInformativeText("Written by Dwaipayan Ray");
    msgbox.exec();
}

void passzero::on_buttonCreate_released()
{

}
void passzero::on_buttonOpen_released()
{

}
