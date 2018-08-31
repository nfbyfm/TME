#ifndef TEXTDOCUMENTPROPERTYDIALOG_H
#define TEXTDOCUMENTPROPERTYDIALOG_H

#include <QDialog>

namespace Ui {
class TextDocumentPropertyDialog;
}

/**
 * @brief dialog for setting documentproperties like pagesize and margins
 *
 */
class TextDocumentPropertyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TextDocumentPropertyDialog(QWidget *parent = nullptr);
    ~TextDocumentPropertyDialog();

private:
    Ui::TextDocumentPropertyDialog *ui;
};

#endif // TEXTDOCUMENTPROPERTYDIALOG_H
