#ifndef PASSZERO_H
#define PASSZERO_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class passzero; }
QT_END_NAMESPACE

namespace zero {
class Passzero : public QMainWindow {
    Q_OBJECT

public:

    /*!
     * @brief Constructor for passzero
     * @param parent takes the parent Qwidget
     */
    Passzero(QWidget *parent = nullptr);

    /*!
     * @brief Destructor for passzero
     */
    ~Passzero();

private slots:

    /*!
     * @brief Exit from the program
     */
    void exit();

    /*!
     * @brief Shows information about the application
     */
    void about();

    /*!
     * @brief Encrypts and saves the open database to a file
     */
    void save();

    /*!
     * @brief Opens a database file
     */
    void open();

    /*!
     * @brief Saves the file by the filename from QDialog
     */
    void saveAs();

    /*!
     * @brief creates and initialize a new database file
     */
    void newFile();

    /*!
     * @brief resets the current gui view
     */
    void reset();

    /*!
     * @brief clears the window components related to current selected entry
     */
    void clearDataView();

    /*!
     * @brief updates the window components related to current selected entry
     */
    void updateDataView();

    /*!
     * @brief clears data from list widget and data vector
     */
    void clearData();

    /*!
     * @brief Changes the stacked widget view
     * @param b boolean containing the level of stacked widgets to display
     */
    void setView(const bool& b);

    /*!
     * @brief change the master key associated with the current database
     */
    void changeMasterKey();

    /*!
     * @brief regenerate the database keys associated with the current database
     */
    void rotateDbKey();

    /*!
     * @brief Slot for the password field changes
     * @param arg1 contains the latest string for the field
     */
    void on_textPassword_textChanged(const QString& arg1);

    /*!
     * @brief on_textLabel_textChanged
     * @param arg1 contains the lastest string for the field
     */
    void on_textLabel_textChanged(const QString& arg1);

    /*!
     * @brief Slot for username field changes
     * @param arg1 contains the latest string for the field
     */
    void on_textUsername_textChanged(const QString& arg1);

    /*!
     * @brief Slot for note field changes
     */
    void on_textNote_textChanged();

    /*!
     * @brief Slot for new Entry button click
     */
    void on_btnNewEntry_released();

    /*!
     * @brief Slot for Delete button click
     */
    void on_btnDelete_released();

    /*!
     * @brief Slot for row changes in list widget
     * @param currentRow contains the latest active row number
     */
    void on_listWidget_currentRowChanged(int currentRow);

private:

    Ui::passzero *ui;
    database *db;
    QString currentfile;
    int curidx;
    bool delproc;
};
}
#endif // PASSZERO_H
