#include "tabledialog.h"
#include "ui_tabledialog.h"

TableDialog::TableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableDialog)
{
    ui->setupUi(this);

    ui->comboBox_Alignment->clear();
    ui->comboBox_Alignment->addItem(tr("Left"));
    ui->comboBox_Alignment->addItem(tr("Center"));
    ui->comboBox_Alignment->addItem(tr("Right"));
    ui->comboBox_Alignment->setCurrentIndex(1);
}

TableDialog::~TableDialog()
{
    delete ui;
}

int TableDialog::getNumberOfColumns()
{
    return ui->spinBox_NumberOfColumns->value();
}


int TableDialog::getNumberOfRows()
{
    return ui->spinBox_NumberOfRows->value();
}


int TableDialog::getColumnWidth()
{
    return ui->spinBox_ColumnWidth->value();
}


Qt::AlignmentFlag TableDialog::getAlignment()
{
    switch(ui->comboBox_Alignment->currentIndex())
    {
        case 0:
            return Qt::AlignLeft;
            break;
        case 1:
            return Qt::AlignCenter;
            break;
        case 2:
            return Qt::AlignRight;
            break;
        default:
            return Qt::AlignLeft;
            break;
    }
}




