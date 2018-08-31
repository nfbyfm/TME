#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>


namespace Ui {
class FindDialog;
}

/**
 * @brief Dialog for showing a search and-replace dialog
 *
 */
class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = nullptr, bool search_only=false);
    ~FindDialog();

private:
    Ui::FindDialog *ui;

    /**
     * @brief if true, only the ui-elements conecering the search function will be shown
     *
     */
    bool showSearchOnly;


    /**
     * @brief fucntion for displaying how many times the search-word has been found
     *
     * @param n number of times the searchword has been found. Shows no text if equals zero.
     */
    void displayFoundXTimes(int n);
};

#endif // FINDDIALOG_H
