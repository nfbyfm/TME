#include "errorlistdialog.h"
#include "ui_errorlistdialog.h"

ErrorListDialog::ErrorListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorListDialog)
{

    ui->setupUi(this);

    this->setLayout(ui->verticalLayout);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->setWindowTitle(tr("Errorlist")); //default
}

ErrorListDialog::~ErrorListDialog()
{
    delete ui;
}


void ErrorListDialog::setErrorMessages(QList <ErrorMessage *> list)
{
    QStringList headerlabels;
    headerlabels.append(tr("Nr."));
    headerlabels.append(tr("solvable"));
    headerlabels.append(tr("Formula"));
    headerlabels.append(tr("Error"));

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(list.size());

    ui->tableWidget->setHorizontalHeaderLabels(headerlabels);

    //qDebug()<<"called setting of the TableWidget Headers. List size: " << list.size();
    for(int i = 0; i<list.size();i++)
    {

    //Number of the formula
        QTableWidgetItem *newItem = new QTableWidgetItem(list.at(i)->getFormulaNumber());
        ui->tableWidget->setItem(i,0,newItem);

    //solvable
        bool solvable = false;
        QString strValue ="";

        list.at(i)->getSolvable(solvable,strValue);

        newItem = new QTableWidgetItem(tr("no"));//strValue);
        newItem->setTextColor(QColor::fromRgb(255,255,255,255));
        //set background color
        /*
        if(solvable)
            newItem->setBackgroundColor(QColor::fromRgb(124,252,0,200)); //lawngreen
        else
            newItem->setBackgroundColor(QColor::fromRgb(255,0,0,200)); //red
            */
        newItem->setBackgroundColor(QColor::fromRgb(255,0,0,200)); //red
        ui->tableWidget->setItem(i,1,newItem);

    //Formula
        newItem = new QTableWidgetItem(list.at(i)->getFormula());
        ui->tableWidget->setItem(i,2,newItem);

    //Errormessage
        newItem = new QTableWidgetItem(list.at(i)->getMeassage());
        ui->tableWidget->setItem(i,3,newItem);


    }
}

void ErrorListDialog::setTitle(QString text)
{
    this->setWindowTitle(text);
}
