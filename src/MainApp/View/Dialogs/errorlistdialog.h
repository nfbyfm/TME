#ifndef ERRORLISTDIALOG_H
#define ERRORLISTDIALOG_H

#include <QDialog>
#include <QDebug>
#include <Control/FaultHandler/errormessage.h>

namespace Ui {
class ErrorListDialog;
}

/**
 * @brief class for showing a list of errors
 *
 */
class ErrorListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorListDialog(QWidget *parent = nullptr);
    ~ErrorListDialog();

    /**
     * @brief setter-function for setting the list of errormessages
     *
     */
    void setErrorMessages(QList <ErrorMessage *> list);

    /**
     * @brief function for setting the windowtitle
     *
     */
    void setTitle(QString text);

private:
    Ui::ErrorListDialog *ui;
};

#endif // ERRORLISTDIALOG_H
