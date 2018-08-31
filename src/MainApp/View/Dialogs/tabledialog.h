#ifndef TABLEDIALOG_H
#define TABLEDIALOG_H

#include <QDialog>

namespace Ui {
class TableDialog;
}

/**
 * @brief dialog for crating a new table
 *
 */
class TableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableDialog(QWidget *parent = nullptr);
    ~TableDialog();

    /**
     * @brief getter-function
     *
     */
    int getNumberOfColumns();

    /**
     * @brief getter-function
     *
     */
    int getNumberOfRows();

    /**
     * @brief getter-function
     *
     */
    int getColumnWidth();

    /**
     * @brief getter-function
     *
     */
    Qt::AlignmentFlag getAlignment();

private:
    Ui::TableDialog *ui;
};

#endif // TABLEDIALOG_H
