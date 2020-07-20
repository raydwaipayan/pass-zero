#include "passzero.h"
#include "ui_passzero.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QtDebug>
#include <QListWidgetItem>
#include <QInputDialog>

passzero::passzero(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::passzero), curidx(-1), db(nullptr),delproc(false)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(),this->geometry().height());
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
    db->clear();
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
    if(db!=nullptr)
        clearData();
}

void passzero::updateDataView()
{
    if(curidx==-1){
        clearDataView();
        return;
    }
    dataitem *cur;
    cur=db->getItem(curidx);
    ui->textLabel->setText(cur->getLabel());
    ui->textUsername->setText(cur->getUser());
    ui->textPassword->setText(cur->getPass());
    ui->textNote->setText(cur->getNote());
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
    bool ok;
    QString masterstring = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                             tr("Enter the master password:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
    if(!ok) return;
    currentfile=filename;
    if(db!=nullptr)
        delete db;
    db=new database(static_cast<const std::string>(masterstring.toUtf8()));
    reset();
}
void passzero::save()
{
    if(currentfile.isEmpty())
    {
        return;
    }
    if(db->write(currentfile))
    {
        QMessageBox::information(this,tr("Data saved successfully!"),tr("Your details are stored in an encrypted file"));
    }
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

    bool ok;
    QString masterstring = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                             tr("Enter the master password:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
    if(!ok) return;
    database *openDB=db->read(filename, masterstring);
    if(openDB==nullptr){
        QMessageBox::information(this,tr("Failed to open database!"),tr("Incorrect password!"));
        return;
    }
    if(db==nullptr) delete db;
    reset();
    db=openDB;

    currentfile=filename;

    for(int i=0;i<db->getSize();i++)
    {
        QListWidgetItem *item=new QListWidgetItem();
        dataitem *ditem;
        if((ditem=db->getItem(i))!=nullptr){
            item->setText(ditem->getLabel());
            ui->listWidget->addItem(item);
        }
    }
}

void passzero::saveAs()
{
    if(currentfile.isEmpty() || db==nullptr)
        return;
    QString filename=QFileDialog::getSaveFileName(this,
                                                  tr("Save Pass Zero file"),"",
                                                  tr("Pass Zero (*.pzk);;All Files (*)"));
    if(filename.isEmpty())
    {
        return;
    }

    if(!db->write(filename))
    {
        QMessageBox::information(this,tr("Unable to open file"),tr("Fatal error."));
        return;
    }
    currentfile=filename;
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
    db->addItem(newitem);

    QListWidgetItem *item = new QListWidgetItem();
    item->setText(newitem.getLabel());
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
}

void passzero::on_btnDelete_released()
{
    if(curidx==-1 || curidx>=db->getSize())
        return;
    delproc=true;
    delete ui->listWidget->takeItem(ui->listWidget->currentRow());
    delproc=false;
    db->removeItem(curidx);
    curidx=ui->listWidget->currentRow();
    updateDataView();
}

void passzero::on_textLabel_textChanged(const QString &arg1)
{
    if(curidx==-1) return;
    dataitem *item;
    if((item=db->getItem(curidx))!=nullptr)
        item->setLabel(arg1);
}
void passzero::on_textPassword_textChanged(const QString &arg1)
{
    if(curidx==-1) return;
    dataitem *item;
    if((item=db->getItem(curidx))!=nullptr)
        item->setPass(arg1);
}
void passzero::on_textUsername_textChanged(const QString &arg1)
{
    if(curidx==-1) return;
    dataitem *item;
    if((item=db->getItem(curidx))!=nullptr)
        item->setUser(arg1);
}

void passzero::on_textNote_textChanged()
{
    if(curidx==-1) return;
    dataitem *item;
    if((item=db->getItem(curidx))!=nullptr)
        item->setNote(ui->textNote->toPlainText());
}

void passzero::on_listWidget_currentRowChanged(int currentRow)
{
    if(delproc)
        return;
    curidx=currentRow;
    updateDataView();
}

