#include "mathform.h"
#include "ui_mathform.h"

MathForm::MathForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MathForm)
{
    ui->setupUi(this);


    ui->groupBox_4->hide();
    setupTableWidgets();
    setupButtons();
    setupComboBoxes();



}

MathForm::~MathForm()
{
    delete ui;
}



#define SETUP_FUNCTIONS_START {
    void MathForm::setupTableWidgets()
    {
        ui->formulaTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->formulaTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->formulaTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
        ui->formulaTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

        ui->variableTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->variableTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->variableTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
        ui->variableTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

        setupTableHeaders();
    }

    void MathForm::setupTableHeaders()
    {
        ui->formulaTableWidget->clear();
        ui->variableTableWidget->clear();

        QStringList headerlabels;
        headerlabels.append(tr("Nr."));
        //headerlabels.append(tr("solvable"));
        headerlabels.append(tr("Formula"));
        headerlabels.append(tr("Variables"));

        ui->formulaTableWidget->setColumnCount(3);
        ui->formulaTableWidget->setHorizontalHeaderLabels(headerlabels);


        QStringList headerlabels2;
        headerlabels2.append(tr("Variable"));
        //headerlabels2.append(tr("solved"));
        headerlabels2.append(tr("Value"));
        //headerlabels2.append(tr("Formulas"));

        ui->variableTableWidget->setColumnCount(2);
        ui->variableTableWidget->setHorizontalHeaderLabels(headerlabels2);
    }

    void MathForm::setupButtons()
    {
        connect(ui->toolButtonAddFormula, &QToolButton::released, this, &MathForm::addFormula);
        connect(ui->toolButtonRemoveFormula, &QToolButton::released, this, &MathForm::removeFormula);
        connect(ui->toolButtonAddVariable, &QToolButton::released, this, &MathForm::addVaraible);
        connect(ui->toolButtonRemoveVariable, &QToolButton::released, this, &MathForm::removeVariable);

        connect(ui->toolButton_addFormulaToText, &QToolButton::released, this, &MathForm::addFormulaToText);
        connect(ui->toolButton_addVariableToText, &QToolButton::released, this, &MathForm::addVaraibleToText);

        connect(ui->lineEditFormulas, &QLineEdit::returnPressed, this, &MathForm::addFormula);
    }

    void MathForm::setupComboBoxes()
    {
        ui->comboBox_FormulaProperty->clear();
        ui->comboBox_FormulaProperty->addItem(tr("Formula as is"));
        ui->comboBox_FormulaProperty->addItem(tr("Formula with Values"));
        //ui->comboBox_FormulaProperty->addItem(tr("Formula with Values, simplyfied"));

        ui->comboBox_VariableProperty->clear();
        ui->comboBox_VariableProperty->addItem(tr("Value"));
        ui->comboBox_VariableProperty->addItem(tr("Variablename = Value"));
    }

    void MathForm::setMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList)
    {
        setupTableHeaders();

        ui->formulaTableWidget->setRowCount(formulaList.size());

        //qDebug()<<"called setting of the TableWidget Headers. List size: " << list.size();
        for(int i = 0; i<formulaList.size();i++)
        {
            QColor backgroundColor;
            if(formulaList.at(i)->getSolvable())
            {
                backgroundColor = QColor::fromRgb(255,255,255,200);//solvable -> white
            }
            else
            {
                backgroundColor = QColor::fromRgb(128,128,128,200);//unsolvable -> gray
            }

        //Number of the formula
            QTableWidgetItem *newItem = new QTableWidgetItem(formulaList.at(i)->getID());
            newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
            newItem->setBackgroundColor(backgroundColor);
            ui->formulaTableWidget->setItem(i,0,newItem);
/*
        //solvable
            bool solvable = false;
            QString strValue ="";
            QColor backgroundColor;
            QColor textColor;
            solvable = formulaList.at(i)->getSolvable();

            //set background color
            if(solvable)
            {
                strValue = tr("yes");
                backgroundColor = QColor::fromRgb(124,252,0,200);     //lawngreen
                textColor = QColor::fromRgb(0,0,0,255);               //black
            }
            else
            {
                strValue = tr("no");
                backgroundColor = QColor::fromRgb(255,0,0,200);     //red
                textColor = QColor::fromRgb(255,255,255,255);       //white
            }

            newItem = new QTableWidgetItem(strValue);
            newItem->setTextColor(textColor);
            newItem->setBackgroundColor(backgroundColor);
            newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
            ui->formulaTableWidget->setItem(i,1,newItem);
*/
        //Formula
            newItem = new QTableWidgetItem(formulaList.at(i)->toString());
            newItem->setBackgroundColor(backgroundColor);
            ui->formulaTableWidget->setItem(i,1,newItem);

        //Variables
            newItem = new QTableWidgetItem(formulaList.at(i)->getVariableNames());
            newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
            newItem->setBackgroundColor(backgroundColor);
            ui->formulaTableWidget->setItem(i,2,newItem);


        }






        ui->variableTableWidget->setRowCount(variableList.size());

        for(int i = 0; i<variableList.size();i++)
        {

            //solved / unsolved -> set background-Color of whole row accordingly
            QColor backgroundColor;
            QColor textColor;
            if( variableList.at(i)->getSolved())
            {
                backgroundColor = QColor::fromRgb(255,255,255,200);//solved -> white
            }
            else
            {
                backgroundColor = QColor::fromRgb(128,128,128,200);//unsolved -> gray
            }


        //Variable name
            QTableWidgetItem *newItem = new QTableWidgetItem(variableList.at(i)->getTextValue());
            newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
            newItem->setBackgroundColor(backgroundColor);
            ui->variableTableWidget->setItem(i,0,newItem);
/*
        //solved
            bool solved = false;
            bool overdetermined;
            QString strValue ="";
            QColor backgroundColor;
            QColor textColor;
            solved = variableList.at(i)->getSolved();
            overdetermined = variableList.at(i)->getOverdetermined();

            //set background color
            if(solved)
            {
                strValue = tr("yes");
                backgroundColor = QColor::fromRgb(124,252,0,200);     //lawngreen
                textColor = QColor::fromRgb(0,0,0,255);               //black
            }
            else if (overdetermined)
            {
                strValue = tr("overdetermined");
                backgroundColor = QColor::fromRgb(255,165,0,200);     //orange
                textColor = QColor::fromRgb(0,0,0,255);                //black
            }
            else
            {
                strValue = tr("no");
                backgroundColor = QColor::fromRgb(255,0,0,200);     //red
                textColor = QColor::fromRgb(255,255,255,255);       //white
            }

            newItem = new QTableWidgetItem(strValue);
            newItem->setTextColor(textColor);
            newItem->setBackgroundColor(backgroundColor);
            newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
            ui->variableTableWidget->setItem(i,1,newItem);
*/
        //Value
            newItem = new QTableWidgetItem(QString::number(variableList.at(i)->getNumericValue()));
            newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
            newItem->setBackgroundColor(backgroundColor);
            ui->variableTableWidget->setItem(i,1,newItem);
/*
        //Formulas
            newItem = new QTableWidgetItem(variableList.at(i)->getFormulaNumberList());
            newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
            newItem->setBackgroundColor(backgroundColor);
            ui->variableTableWidget->setItem(i,2,newItem);
*/

        }

        qDebug()<<"Mathform: set Mathdata finished";
    }

    void MathForm::resetTables()
    {
        ui->formulaTableWidget->clear();
        ui->formulaTableWidget->setRowCount(0);
        ui->variableTableWidget->clear();
        ui->variableTableWidget->setRowCount(0);
        setupTableWidgets();

        qDebug()<<"Mathform: resetTables done";
    }


#define SETUP_FUNCTIONS_END }


#define GETTER_AND_SETTER_FUNCTIONS_START {

    QStringList *MathForm::getListofCurrentFormulas()
    {
        QStringList * result = new QStringList();

        for(int i = 0; i<ui->formulaTableWidget->rowCount(); i++)
        {
            result->append(ui->formulaTableWidget->item(i,1)->text().replace(",","."));
        }

        qDebug()<<"MathForm: get List of current Formulas called";
        return result;
    }

    QStringList *MathForm::getListofCurrentVariables()
    {
        QStringList * result = new QStringList();

        for(int i = 0; i<ui->variableTableWidget->rowCount(); i++)
        {
            result->append(ui->variableTableWidget->item(i,0)->text());
        }

        return result;
    }
    int MathForm::numberOfFormulas()
    {
        return ui->formulaTableWidget->rowCount();
    }

    int MathForm::numberOfVariables()
    {
        return ui->variableTableWidget->rowCount();
    }

#define GETTER_AND_SETTER_FUNCTIONS_END }

#define GUI_FUNCTIONS_START {

    void MathForm::retranslateUI()
    {
        ui->retranslateUi(this);
        setupComboBoxes();
    }

    void MathForm::addVaraible()
    {
        QString variableName = ui->lineEditVariables->text();



        if(!variableName.isEmpty() && !getListofCurrentVariables()->contains(variableName, Qt::CaseInsensitive))
        {
            int rowIndex = ui->variableTableWidget->rowCount();
            ui->variableTableWidget->insertRow(rowIndex);

            //Variable name
                QTableWidgetItem *newItem = new QTableWidgetItem(variableName);
                newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
                ui->variableTableWidget->setItem(rowIndex,0,newItem);
/*
            //solved
                bool solved = false;
                QString strValue ="";
                QColor backgroundColor;
                QColor textColor;
                solved = false;

                //set background color
                if(solved)
                {
                    strValue = tr("yes");
                    backgroundColor = QColor::fromRgb(124,252,0,200);     //lawngreen
                    textColor = QColor::fromRgb(0,0,0,255);               //black
                }
                else
                {
                    strValue = tr("no");
                    backgroundColor = QColor::fromRgb(255,0,0,200);     //red
                    textColor = QColor::fromRgb(255,255,255,255);       //white
                }

                newItem = new QTableWidgetItem(strValue);
                newItem->setTextColor(textColor);
                newItem->setBackgroundColor(backgroundColor);
                newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
                ui->variableTableWidget->setItem(rowIndex,1,newItem);
*/
            //Value
                newItem = new QTableWidgetItem(QString::number(0));
                newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
                ui->variableTableWidget->setItem(rowIndex,1,newItem);
/*
            //Formulas
                newItem = new QTableWidgetItem("-");
                newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
                ui->variableTableWidget->setItem(rowIndex,3,newItem);
*/
            ui->lineEditVariables->setText("");
        }
        else
        {
            if(getListofCurrentVariables()->contains(variableName, Qt::CaseInsensitive))
            {
                ui->lineEditVariables->setText("");
                emit sendError(new ErrorMessage(this,ERROR_ID::MATHINPUT_VariableAlreadyInList,new MetaError(this,new QStringList({variableName}))));
            }
        }
        qDebug()<<"MathForm: added Variable";
        emit valuesChanged();
    }

    void MathForm::removeVariable()
    {
        if(ui->variableTableWidget->currentRow()>=0)
        {
            ui->variableTableWidget->removeRow(ui->variableTableWidget->currentRow());
        }
        qDebug()<<"MathForm: remove Variable";
        emit valuesChanged();
    }

    void MathForm::addFormula()
    {
        QString formulaName = ui->lineEditFormulas->text();

        if(!formulaName.isEmpty() && !getListofCurrentFormulas()->contains(formulaName,Qt::CaseInsensitive))
        {
            int rowIndex = ui->formulaTableWidget->rowCount();
            ui->formulaTableWidget->insertRow(rowIndex);

            //Number of the formula
                QTableWidgetItem *newItem = new QTableWidgetItem("-");
                newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
                ui->formulaTableWidget->setItem(rowIndex,0,newItem);
/*
            //solvable
                newItem = new QTableWidgetItem("");
                newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
                ui->formulaTableWidget->setItem(rowIndex,1,newItem);
*/
            //Formula
                newItem = new QTableWidgetItem(formulaName);
                ui->formulaTableWidget->setItem(rowIndex,1,newItem);

            //Variables
                newItem = new QTableWidgetItem("");
                newItem->setFlags(newItem->flags()^Qt::ItemIsEditable);     //read-only
                ui->formulaTableWidget->setItem(rowIndex,2,newItem);

            ui->lineEditFormulas->setText("");
        }
        else
        {
            if(getListofCurrentFormulas()->contains(formulaName,Qt::CaseInsensitive))
            {
                ui->lineEditFormulas->setText("");
                emit sendError(new ErrorMessage(this,ERROR_ID::MATHINPUT_FormulaAlreadyInList,new MetaError(this,new QStringList({formulaName}))));
            }
        }
        qDebug()<<"MathForm: added Formula";
        emit valuesChanged();
    }

    void MathForm::removeFormula()
    {
        if(ui->formulaTableWidget->currentRow()>=0)
        {
            ui->formulaTableWidget->removeRow(ui->formulaTableWidget->currentRow());
        }
        qDebug()<<"MathForm: remove Formula";
        emit valuesChanged();
    }



    void MathForm::addVaraibleToText()
    {
        if(ui->variableTableWidget->currentRow()>=0)
        {
            QString variable = ui->variableTableWidget->item(ui->variableTableWidget->currentRow(),0)->text();

            variable = "$link(" + variable + ",";

            switch(ui->comboBox_VariableProperty->currentIndex())
            {
                case 0: //Value
                    variable += "value";
                    break;
                case 1: //Variablename = Value
                    variable += "name_eq_value";
                    break;
                default:
                    variable += "value";
                    break;
            }
            variable += ")$";

            emit addTextToDocument(variable);
        }
        else
        {
            //qDebug()<<"No Variable selected.";
            emit sendError(new ErrorMessage(this,ERROR_ID::MATHINPUT_NoVariableSelected,nullptr));
        }
    }

    void MathForm::addFormulaToText()
    {
        if(ui->formulaTableWidget->currentRow()>=0)
        {
            QString formula = ui->formulaTableWidget->item(ui->formulaTableWidget->currentRow(),1)->text();

            formula = "$link(" + formula + ",";

            switch(ui->comboBox_FormulaProperty->currentIndex())
            {
                case 0: //Formula as is
                    formula += "as_is";
                    break;
                case 1: //Formula with Variablevalues set in
                    formula += "with_values";
                    break;
                default:
                    formula += "as_is";
                    break;
            }
            formula += ")$";

            emit addTextToDocument(formula);
        }
        else
        {
            //qDebug()<<"No Formula selected.";
            emit sendError(new ErrorMessage(this,ERROR_ID::MATHINPUT_NoFormulaSelected,nullptr));
        }
    }


    void MathForm::resizeEvent(QResizeEvent* event)
    {
        QWidget::resizeEvent(event);

        //change splitter orientation
        QRect rectangl =this->geometry();
        if(rectangl.width()>rectangl.height())
            ui->splitter->setOrientation(Qt::Horizontal);
        else
            ui->splitter->setOrientation(Qt::Vertical);

    }
#define GUI_FUNCTIONS_END }




