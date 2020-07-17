#include "passzero.h"
#include "ui_passzero.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QtDebug>
#include <QListWidgetItem>
#include <QInputDialog>

passzero::passzero(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::passzero), curidx(-1), delproc(false)
{
    ui->setupUi(this);
    connect(ui->actionAbout, &QAction::triggered, this, &passzero::about);
    connect(ui->actionExit, &QAction::triggered, this, &passzero::exit);
    connect(ui->actionSave, &QAction::triggered, this, &passzero::save);
    connect(ui->actionSave_As, &QAction::triggered, this, &passzero::saveAs);
    connect(ui->actionOpen, &QAction::triggered, this, &passzero::open);
    connect(ui->actionNew, &QAction::triggered, this, &passzero::newFile);

    setView(false);
}

passzero::~passzero()
{
    delete ui;
}

void passzero::clearData()
{
    ui->listWidget->clear();
    data.clear();
}
void passzero::setView(const bool &b)
{
    ui->label->setVisible(b);
    ui->label_2->setVisible(b);
    ui->label_3->setVisible(b);
    ui->label_4->setVisible(b);
    ui->textNote->setVisible(b);
    ui->textUsername->setVisible(b);
    ui->textPassword->setVisible(b);
    ui->textLabel->setVisible(b);
    ui->listWidget->setVisible(b);
    ui->btnDelete->setVisible(b);
    ui->btnNewEntry->setVisible(b);
    ui->nullLabel->setVisible(!b);
}

void passzero::clearDataView()
{
    ui->textLabel->clear();
    ui->textUsername->clear();
    ui->textPassword->clear();
    ui->textNote->clear();
}

void passzero::reset(){
    setView(true);
    curidx=-1;
    updateDataView();
    clearData();
}

void passzero::updateDataView()
{
    if(curidx==-1){
        clearDataView();
        return;
    }
    dataitem &cur=data[curidx];
    ui->textLabel->setText(cur.getLabel());
    ui->textUsername->setText(cur.getUser());
    ui->textPassword->setText(cur.getPass());
    ui->textNote->setText(cur.getNote());
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

    if(!filename.endsWith(".pzk"))
    {
        filename+=".pzk";
    }
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

    for(qint64 i=0;i<data.size();i++)
    {
        QListWidgetItem *item=new QListWidgetItem();
        item->setText(data[i].getLabel());
        ui->listWidget->addItem(item);
    }
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

void passzero::on_btnNewEntry_released()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                             tr("Entry label:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
    if (!ok) return;

    dataitem newitem(text, QString(), QString(), QString());
    data.append(newitem);

    QListWidgetItem *item = new QListWidgetItem();
    item->setText(newitem.getLabel());
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
}

void passzero::on_btnDelete_released()
{
    if(curidx==-1)
        return;
    delproc=true;
    delete ui->listWidget->takeItem(ui->listWidget->currentRow());
    delproc=false;
    data.remove(curidx);
    curidx=ui->listWidget->currentRow();
    updateDataView();
}

void passzero::on_textLabel_textChanged(const QString &arg1)
{
    if(curidx==-1) return;
    data[curidx].setLabel(arg1);
}
void passzero::on_textPassword_textChanged(const QString &arg1)
{
    if(curidx==-1) return;
    data[curidx].setPass(arg1);
}
void passzero::on_textUsername_textChanged(const QString &arg1)
{
    if(curidx==-1) return;
    data[curidx].setUser(arg1);
}

void passzero::on_textNote_textChanged()
{
    if(curidx==-1) return;
    data[curidx].setNote(ui->textNote->toPlainText());
}

void passzero::on_listWidget_currentRowChanged(int currentRow)
{
    if(delproc)
        return;
    curidx=currentRow;
    updateDataView();
}

