#include "textdocumentpropertydialog.h"
#include "ui_textdocumentpropertydialog.h"

TextDocumentPropertyDialog::TextDocumentPropertyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextDocumentPropertyDialog)
{
    ui->setupUi(this);
}

TextDocumentPropertyDialog::~TextDocumentPropertyDialog()
{
    delete ui;
}
