#include <QMessageBox>
#include <QFileDialog>
#include <QtDebug>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QAction>

#include "passzero.h"
#include "ui_passzero.h"
#include "reader.h"
#include "writer.h"

zero::Passzero::Passzero(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::passzero), db(nullptr), curidx(-1), delproc(false)
{
    ui->setupUi(this);
    this->setFixedSize(this->geometry().width(), this->geometry().height());

    // Connect menubar sigals to the slots
    connect(ui->actionAbout,
            &QAction::triggered,
            this,
            &Passzero::about);
    connect(ui->actionExit,
            &QAction::triggered,
            this,
            &Passzero::exit);
    connect(ui->actionSave,
            &QAction::triggered,
            this,
            &Passzero::save);
    connect(ui->actionSave_As,
            &QAction::triggered,
            this,
            &Passzero::saveAs);
    connect(ui->actionOpen,
            &QAction::triggered,
            this,
            &Passzero::open);
    connect(ui->actionNew,
            &QAction::triggered,
            this,
            &Passzero::newFile);
    connect(ui->actionChange_Master_Key,
            &QAction::triggered,
            this,
            &Passzero::changeMasterKey);
    connect(ui->actionRotate_Database_keys,
            &QAction::triggered,
            this,
            &Passzero::rotateDbKey);
    setView(false);
}

zero::Passzero::~Passzero()
{
    delete ui;
    delete db;
}

void zero::Passzero::clearData()
{
    ui->listWidget->clear();
    db->clear();
}

void zero::Passzero::setView(const bool& b)
{
    ui->stackedWidget->setCurrentIndex(b);

    if (b)
    {
        ui->actionChange_Master_Key->setDisabled(false);
        ui->actionRotate_Database_keys->setDisabled(false);
    }
    else {
        ui->actionChange_Master_Key->setDisabled(true);
        ui->actionRotate_Database_keys->setDisabled(true);
    }
}

void zero::Passzero::clearDataView()
{
    ui->textLabel->clear();
    ui->textUsername->clear();
    ui->textPassword->clear();
    ui->textNote->clear();
}

void zero::Passzero::reset() {
    setView(true);
    curidx = -1;
    updateDataView();

    if (db != nullptr) clearData();
}

void zero::Passzero::updateDataView()
{
    if (curidx == -1) {
        clearDataView();
        return;
    }

    dataitem& cur = (*db->getItem(curidx));

    ui->textLabel->setText(cur.getLabel());
    ui->textUsername->setText(cur.getUser());
    ui->textPassword->setText(cur.getPass());
    ui->textNote->setText(cur.getNote());
}

void zero::Passzero::newFile()
{
    if (!currentfile.isEmpty())
    {
        // handle close ops
    }
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr(
                                                        "Create new Pass Zero file"),
                                                    "",
                                                    tr(
                                                        "Pass Zero (*.pzk);;All Files (*)"));

    if (!filename.endsWith(".pzk"))
    {
        filename += ".pzk";
    }

    if (filename.isEmpty())
    {
        return;
    }
    bool ok;
    QString masterstring =
        QInputDialog::getText(this,
                              tr("QInputDialog::getText()"),
                              tr(
                                  "Enter the master password:"),
                              QLineEdit::Normal,
                              QDir::home().dirName(),
                              &ok);

    if (!ok) {
        return;
    }
    currentfile = filename;

    if (db != nullptr) delete db;
    db = new database(static_cast<const std::string>(masterstring.toUtf8()));
    reset();
}

void zero::Passzero::save()
{
    if (currentfile.isEmpty())
    {
        return;
    }

    if (Writer::write((*db), currentfile))
    {
        QMessageBox::information(this,
                                 tr("Data saved successfully!"),
                                 tr(
                                     "The encrypted database is successfully saved"));
    }
}

void zero::Passzero::open()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Pass Zero file"),
                                                    "",
                                                    tr(
                                                        "Pass Zero (*.pzk);;All Files (*)"));

    if (filename.isEmpty())
    {
        return;
    }

    bool ok;
    QString masterstring =
        QInputDialog::getText(this,
                              tr("QInputDialog::getText()"),
                              tr(
                                  "Enter the master password:"),
                              QLineEdit::Normal,
                              QDir::home().dirName(),
                              &ok);

    if (!ok) {
        return;
    }
    database *openDb = database::genEmptyDb();

    try {
        Reader::read((*openDb), masterstring, filename);
    }
    catch (std::exception& e) {
        QMessageBox::information(this, tr("Failed to open database!"),
                                 tr(e.what()));
        return;
    }
    reset();
    db          = openDb;
    currentfile = filename;

    for (int i = 0; i < db->getSize(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem();
        dataitem *ditem;

        if ((ditem = db->getItem(i)) != nullptr) {
            item->setText(ditem->getLabel());
            ui->listWidget->addItem(item);
        }
    }
}

void zero::Passzero::saveAs()
{
    if (currentfile.isEmpty() || (db == nullptr)) return;

    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save Pass Zero file"),
                                                    "",
                                                    tr(
                                                        "Pass Zero (*.pzk);;All Files (*)"));

    if (filename.isEmpty())
    {
        return;
    }

    if (!Writer::write((*db), filename))
    {
        QMessageBox::information(this, tr("Unable to open file"),
                                 tr("Fatal error."));
        return;
    }
    currentfile = filename;
}

void zero::Passzero::exit()
{
    QMessageBox msgbox(this);

    msgbox.setText("Are you sure you want to Quit?");
    msgbox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Yes);
    int ret = msgbox.exec();

    if (ret == QMessageBox::Yes) {
        QApplication::exit();
    }
}

void zero::Passzero::about()
{
    QMessageBox msgbox(this);

    msgbox.setText("Ultra Secure lightweight password manager");
    msgbox.setInformativeText("Written by Dwaipayan Ray");
    msgbox.exec();
}

void zero::Passzero::changeMasterKey() {
    if (db == nullptr) {
        return;
    }

    bool ok;
    QString masterstring =
        QInputDialog::getText(this,
                              tr("QInputDialog::getText()"),
                              tr(
                                  "Enter new master password:"),
                              QLineEdit::Normal,
                              QDir::home().dirName(),
                              &ok);

    if (!ok) {
        return;
    }
    db->setMasterKey(std::string(masterstring.toUtf8()));

    if (Writer::write((*db), currentfile))
    {
        QMessageBox msgbox(this);

        msgbox.setText("Successfully changed Master Key!!");
        msgbox.exec();
    }
}

void zero::Passzero::rotateDbKey() {
    if (db == nullptr) {
        return;
    }
    db->rotateDbKey();
    QMessageBox msgbox(this);

    msgbox.setText("Successfully rotated Database Key!!");
    msgbox.exec();
}

void zero::Passzero::on_btnNewEntry_released()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("New Entry"),
                                         tr("Entry label:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);

    if (!ok) {
        return;
    }
    dataitem newitem(text, QString(), QString(), QString());

    db->addItem(newitem);

    QListWidgetItem *item = new QListWidgetItem();

    item->setText(newitem.getLabel());
    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentItem(item);
}

void zero::Passzero::on_btnDelete_released()
{
    if ((curidx == -1) || (curidx >= db->getSize())) delproc = true;
    delete ui->listWidget->takeItem(ui->listWidget->currentRow());
    delproc = false;
    db->removeItem(curidx);
    curidx = ui->listWidget->currentRow();
    updateDataView();
}

void zero::Passzero::on_textLabel_textChanged(const QString& arg1)
{
    if (curidx == -1) {
        return;
    }
    dataitem *item;

    if ((item = db->getItem(curidx)) != nullptr) item->setLabel(arg1);
}

void zero::Passzero::on_textPassword_textChanged(const QString& arg1)
{
    if (curidx == -1) {
        return;
    }
    dataitem *item;

    if ((item = db->getItem(curidx)) != nullptr) item->setPass(arg1);
}

void zero::Passzero::on_textUsername_textChanged(const QString& arg1)
{
    if (curidx == -1) {
        return;
    }
    dataitem *item;

    if ((item = db->getItem(curidx)) != nullptr) item->setUser(arg1);
}

void zero::Passzero::on_textNote_textChanged()
{
    if (curidx == -1) {
        return;
    }
    dataitem *item;

    if ((item = db->getItem(curidx)) != nullptr) item->setNote(
            ui->textNote->toPlainText());
}

void zero::Passzero::on_listWidget_currentRowChanged(int currentRow)
{
    if (delproc) {
        return;
    }
    curidx = currentRow;
    updateDataView();
}
