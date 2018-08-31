#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent, bool search_only) :
    QDialog(parent),
    ui(new Ui::FindDialog),
    showSearchOnly(search_only)
{
    ui->setupUi(this);
    ui->radioButtonCurrentDocument->setChecked(true);

    //show / enable Search-fields only
    if(search_only)
    {
        ui->textToReplaceWith->setEnabled(false);
        ui->label_2->setEnabled(false);
        ui->pushButton_Replace->setEnabled(false);
        ui->pushButton_ReplaceAll->setEnabled(false);
    }

    ui->groupBoxSearchIn->setEnabled(false);
    ui->groupBoxSearchIn->setVisible(false);

    displayFoundXTimes(0);
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::displayFoundXTimes(int n)
{
    if (n > 0)
    {
       ui->label_FoundXTimes->setText(n == 1 ? tr("Searchword found %1 time.").arg(n) : tr("Searchword found %1 times.").arg(n));// tr("Searchword found %1 times.").arg(n));
    }
    else
    {
        ui->label_FoundXTimes->setText("");
    }
}
