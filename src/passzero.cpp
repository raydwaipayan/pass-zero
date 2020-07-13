#include "passzero.h"
#include "ui_passzero.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QtDebug>
#include <QListWidgetItem>
#include <QInputDialog>

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
    ui->textNote->setVisible(false);
    ui->textUsername->setVisible(false);
    ui->textPassword->setVisible(false);
    ui->textLabel->setVisible(false);
    ui->listWidget->setVisible(false);
    ui->btnDelete->setVisible(false);
    ui->btnNewEntry->setVisible(false);
    ui->nullLabel->setVisible(true);
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
    ui->textNote->setVisible(true);
    ui->textUsername->setVisible(true);
    ui->textPassword->setVisible(true);
    ui->textLabel->setVisible(true);
    ui->listWidget->setVisible(true);
    ui->btnDelete->setVisible(true);
    ui->btnNewEntry->setVisible(true);
    ui->nullLabel->setVisible(false);
    clearContext();
    ui->listWidget->clear();
    data.clear();
}

void passzero::clearContext()
{
    ui->textLabel->clear();
    ui->textUsername->clear();
    ui->textPassword->clear();
    ui->textNote->clear();
    this->label="";
    this->user="";
    this->pass="";
    this->note="";
}
void passzero::changeActive(const QString &label, const QString &username, const QString &password, const QString &note)
{
    ui->textLabel->setText(label);
    ui->textUsername->setText(username);
    ui->textPassword->setText(password);
    ui->textNote->setText(note);
    this->label=label;
    this->user=username;
    this->pass=password;
    this->note=note;
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
    changeActive(text, QString(), QString(), QString());
}

void passzero::on_btnDelete_released()
{
    if(ui->listWidget->currentItem()==nullptr)
        return;

    qint64 idx=ui->listWidget->currentRow();
    delete ui->listWidget->takeItem(ui->listWidget->currentRow());
    data.remove(idx);
    clearContext();
}

void passzero::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    qint64 previdx=-1;
    qint64 curidx=-1;
    for(qint64 i=0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem* item = ui->listWidget->item(i);
        if(current!=nullptr && item==current)
        {
            curidx=i;
        }
        if(previous!=nullptr && item==previous)
        {
            previdx=i;
        }
    }
    if(previdx!=-1){
        dataitem &prev=data[previdx];
        prev.setData(label, user, pass, note);
    }
    if(curidx!=-1)
    {
        dataitem &cur=data[curidx];
        changeActive(cur.getLabel(),cur.getUser(), cur.getPass(), cur.getNote());
    }
}

void passzero::on_textLabel_textChanged(const QString &arg1)
{
    label=arg1;
}
void passzero::on_textPassword_textChanged(const QString &arg1)
{
    pass=arg1;
}
void passzero::on_textUsername_textChanged(const QString &arg1)
{
    user=arg1;
}

void passzero::on_textNote_textChanged()
{
    note=ui->textNote->toPlainText();
}
