#include "mvariable.h"




MVariable::MVariable(QObject *parent) : QObject(parent)
{
    solved = false;
    this->numericValue = 0;
}

MVariable::~MVariable()
{
    qDeleteAll(formulaRefs);
}

#define GETTERS_AND_SETTERS_START {
    QString MVariable::getTextValue() const
    {
        return textValue;
    }

    void MVariable::setTextValue(const QString &value)
    {
        textValue = value;
    }

    double MVariable::getNumericValue() const
    {
        return numericValue;
    }

    void MVariable::setNumericValue(double value)
    {
        numericValue = value;
    }

    QList<MFormula *> MVariable::getFormulaRefs() const
    {
        return formulaRefs;
    }

    void MVariable::setFormulaRefs(const QList<MFormula *> &value)
    {
        formulaRefs = value;
    }

    bool MVariable::getSolved() const
    {
        return solved;
    }

    void MVariable::setSolved(bool value)
    {
        solved = value;
    }

    QString MVariable::getFormulaNumberList()
    {
        QString result="";
        foreach(MFormula *formula, formulaRefs)
        {
            result = result + " " + formula->getID();
        }
        return result;
    }

    bool MVariable::getOverdetermined() const
    {
        return overdetermined;
    }

    void MVariable::setOverdetermined(bool value)
    {
        overdetermined = value;
    }
#define GETTERS_AND_SETTERS_END }



void MVariable::addFormulaRef(MFormula *formula)
{
    if(formula != nullptr)
        formulaRefs.append(formula);
}



bool MVariable::isInFormula(MFormula * formula)
{
    bool result = false;

    for(int i = 0; i < formulaRefs.count(); i++)
    {
        if(formula == formulaRefs.at(i))
        {
            result = true;
            break;
        }
    }

    return result;
}
