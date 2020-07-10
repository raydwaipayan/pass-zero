#include "passzero.h"
#include "ui_passzero.h"
#include <QMessageBox>
#include <QFileDialog>

passzero::passzero(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::passzero)
{
    ui->setupUi(this);
    connect(ui->actionAbout, &QAction::triggered, this, &passzero::about);
    connect(ui->actionExit, &QAction::triggered, this, &passzero::exit);
    connect(ui->actionSave, &QAction::triggered, this, &passzero::save);
    connect(ui->actionSave_As, &QAction::triggered, this, &passzero::saveAs);
    connect(ui->actionOpen, &QAction::triggered, this, &passzero::open);
    connect(ui->actionNew, &QAction::triggered, this, &passzero::newFile);

    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->label_4->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->textUsername->setVisible(false);
    ui->textPassword->setVisible(false);
    ui->textLabel->setVisible(false);
    ui->listWidget->setVisible(false);
    ui->btnAdd->setVisible(false);
    ui->btnDelete->setVisible(false);
}


passzero::~passzero()
{
    delete ui;
}

void passzero::reset(){
    ui->label->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->textEdit->setVisible(true);
    ui->textUsername->setVisible(true);
    ui->textPassword->setVisible(true);
    ui->textLabel->setVisible(true);
    ui->listWidget->setVisible(true);
    ui->btnAdd->setVisible(true);
    ui->btnDelete->setVisible(true);
    ui->nullLabel->setVisible(false);
}

void passzero::newFile()
{
    if(!currentfile.isEmpty())
    {
        //handle close ops
    }
    QString filename=QFileDialog::getSaveFileName(this,
                                                  tr("Create new Pass Zero file"),"",
                                                  tr("Pass Zero (*.pzk);;All Files (*)"));
    if(filename.isEmpty())
    {
        return;
    }
    currentfile=filename;
    reset();
}
void passzero::save()
{
    if(currentfile.isEmpty())
    {
        saveAs();
        return;
    }
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
void passzero::open()
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
    reset();
    currentfile=filename;

    QDataStream in(&file);
    in>>data;

    file.close();
}

void passzero::saveAs()
{
    QString filename=QFileDialog::getSaveFileName(this,
                                                  tr("Save Pass Zero file"),"",
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
    QDataStream out(&file);
    out<<data;

    file.close();
}
void passzero::exit()
{
    QMessageBox msgbox;
    msgbox.setText("Are you sure you want to Quit?");
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


void passzero::on_btnAdd_clicked()
{

}
