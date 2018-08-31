#include "mainmodel.h"

MainModel::MainModel(QObject *parent) : QObject(parent)
{
    mMathModel = new MathModel(this);
    //tDocument = new QTextDocument(this);
    isUntitled=true;
    connect();
}

/*
QTextDocument *MainModel::getTDocument()
{
    return tDocument;
}

void MainModel::setTDocument(QTextDocument *value)
{
    tDocument = value;
}
*/

QString MainModel::getFileName() const
{
    return fileName;
}

void MainModel::setFileName(const QString &value)
{
    isUntitled = (value.isEmpty());
    fileName = value;
}

bool MainModel::getIsUntitled() const
{
    return isUntitled;
}

MathModel *MainModel::getMathModel() const
{
    return mMathModel;
}

void MainModel::connect()
{
    //this sendMathData with mathmodel
    QObject::connect(this, SIGNAL(sendMathData(QList<MFormula*>,QList<MVariable*>)), mMathModel, SLOT(recieveMathData(QList<MFormula*>,QList<MVariable*>)));
}
/*
void MainModel::recieveTokenizedFormulas()
{

}
*/

void  MainModel::recieveMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList)
{
    emit sendMathData(formulaList,variableList);
}

/*
QString MainModel::getHTMLFormulaAppendix()
{
    QString result = "\n<!-- \n";

    //result += mMathModel->getFormulaListForAppendix();

    result += "\n-->";

    return result;
}
*/
