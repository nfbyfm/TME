#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent, bool search_only, QTextDocument *doc) :
    QDialog(parent),
    ui(new Ui::FindDialog),
    showSearchOnly(search_only),
    document(doc)
{
    ui->setupUi(this);
    ui->radioButtonCurrentDocument->setChecked(true);
    isFirstTime=true;

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

    connect(ui->pushButton_Find,&QPushButton::clicked, this, &FindDialog::findText);
    connect(this, &QDialog::accepted, this, &FindDialog::closeDialog);
    connect(this, &QDialog::rejected, this, &FindDialog::closeDialog);
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


void FindDialog::findText()
{

    QString searchString = ui->textToFind->text();


    bool found = false;

    if (isFirstTime == false)
        document->undo();

    if (searchString.isEmpty())
    {
        qDebug()<<"FindDialog: Searchfield is empty.";
     //QMessageBox::information(this, tr("Empty Search Field"),
     //       "The search field is empty. Please enter a word and click Find.");
    }
    else
    {
        QTextCursor highlightCursor(document);
        QTextCursor cursor(document);

        cursor.beginEditBlock();

        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat = plainFormat;
        colorFormat.setForeground(Qt::red);

        while (!highlightCursor.isNull() && !highlightCursor.atEnd())
        {
            highlightCursor = document->find(searchString, highlightCursor, QTextDocument::FindWholeWords);

            if (!highlightCursor.isNull())
            {
                found = true;
                highlightCursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
                highlightCursor.mergeCharFormat(colorFormat);
            }
        }

        cursor.endEditBlock();
        isFirstTime = false;

         if (found == false)
         {
             qDebug()<<"FindDialog: couldn't find the searchword";
             //document->undo();
             //QMessageBox::information(this, tr("Word Not Found"),  "Sorry, the word cannot be found.");
         }
    }
}

void FindDialog::closeDialog()
{
    if(showSearchOnly)
    {
        document->undo();
    }
}
