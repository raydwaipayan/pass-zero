#include "passzero.h"
#include "ui_passzero.h"
#include <QMessageBox>
#include <QFileDialog>

passzero::passzero(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::passzero)
{
    ui->setupUi(this);
    ui->textEdit->setTextInteractionFlags(Qt::NoTextInteraction);

    connect(ui->actionAbout, &QAction::triggered, this, &passzero::about);
    connect(ui->actionExit, &QAction::triggered, this, &passzero::exit);
    connect(ui->actionSave, &QAction::triggered, this, &passzero::save);
}

passzero::~passzero()
{
    delete ui;
}
void passzero::save()
{
    QFile file(currentfile);
    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(this,tr("Unable to open file for saving"),file.errorString());
        return;
    }
    QDataStream out(&file);
    out<<data;

    QMessageBox::information(this,tr("Data saved successfully!"),tr("Your details are stored in an encrypted file"));

    file.close();
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
    QString filename=QFileDialog::getSaveFileName(this,
                                                  tr("Open Pass Zero file"),"",
                                                  tr("Pass Zero (*.pzk);;All Files (*)"));
    if(filename.isEmpty())
    {
        return;
    }
    currentfile=filename;
}

void passzero::on_buttonOpen_released()
{
    QString filename=QFileDialog::getOpenFileName(this,
                                                  tr("Open Pass Zero file"),"",
                                                  tr("Pass Zero (*.pzk);;All Files (*)"));
    if(filename.isEmpty())
    {
        return;
    }

    QFile file(filename);
    if(!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::information(this,tr("Unable to open file"),file.errorString());
        return;
    }
    currentfile=filename;
    QDataStream in(&file);
    in>>data;

    file.close();
}
