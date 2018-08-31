#include "mathmodel.h"




MathModel::MathModel(QObject *parent) : QObject(parent)
{

}

MathModel::~MathModel()
{
    qDeleteAll(lFormulas);
    qDeleteAll(lVariables);
}






#define GETTERS_AND_SETTERS_START {

    void MathModel::recieveMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList)
    {
        this->lFormulas.clear();
        this->lFormulas = formulaList;

        this->lVariables.clear();
        this->lVariables = variableList;
        qDebug()<<"Mathmodel: Formulas and Variables recieved";
    }

    QList<MFormula *> MathModel::getLFormulas() const
    {
        return lFormulas;
    }

    QList<MVariable *> MathModel::getLVariables() const
    {
        return lVariables;
    }

#define GETTERS_AND_SETTERS_END }




