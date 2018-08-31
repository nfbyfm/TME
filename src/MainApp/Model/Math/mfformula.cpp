#include "mfformula.h"

MFFormula::MFFormula(QObject *parent) : QObject(parent)
{
    formulaParts = new QList<MFPart*>();
}

#define GETTERS_AND_SETTERS_START {


    QList<MFPart *> *MFFormula::getFormulaParts() const
    {
        return formulaParts;
    }

    void MFFormula::setFormulaParts(QList<MFPart *> *value)
    {
        formulaParts = value;
    }

    void MFFormula::appendList(MFPart *newElement)
    {
        if(formulaParts == nullptr)
            formulaParts = new QList<MFPart*>();

        formulaParts->append(newElement);
    }

    int MFFormula::getNumberOfVariables()
    {
        int retVal = -1;
        if(!formulaParts->isEmpty())
        {
            retVal=0;
            for(int i =0; i<formulaParts->count(); i++)
            {
                if(formulaParts->at(i)->getGType()==MFPartType::NUMERIC_AND_VARIABLE || formulaParts->at(i)->getGType()==MFPartType::VARIABLE_ONLY)
                    retVal++;
            }
        }

        return retVal;
    }

#define GETTERS_AND_SETTERS_END }

void MFFormula::simplify()
{
    //QString simplifiedparts="MFFormula: simplified formula (part 1): ";
    for(int u =0; u < formulaParts->count(); u++)
    {
        //qDebug()<<"MFFormula: simplify: start simplifying Part: " << formulaParts->at(u)->tokenListToString();
        formulaParts->at(u)->simplifyList();
        //simplifiedparts += formulaParts->at(u)->tokenListToString() + " + ";
    }
    //simplifiedparts = simplifiedparts.remove(simplifiedparts.lastIndexOf("+"), simplifiedparts.count()) + " = 0";
    //qDebug()<<simplifiedparts;

    //search for multiple definitions of variables within the List and multiple Numeric-only parts -> combine them
    int g=0;
    int numFoundIndex =-1;  //help-variable for numeric parts
    QMap <QString, int> *varMap = new QMap<QString, int>();

    while( g<formulaParts->count())
    {
        //qDebug()<<"MFFormula: simplify: start simplifying Part: " << partsList->at(i)->at(u)->tokenListToString();
        if(formulaParts->at(g)->getGType()==MFPartType::NUMERIC)
        {
            if(numFoundIndex != -1)
            {
                //combine both numeric parts, remove current one
                double val1 = -1;
                double val2 = -1;
                if(formulaParts->at(numFoundIndex)->getNumericValue(val1) && formulaParts->at(g)->getNumericValue(val2))
                {
                    formulaParts->at(numFoundIndex)->getTokenList().at(0)->setValue(QString::number(val1+val2));
                    formulaParts->removeAt(g);
                    //don't increase g (we just removed a listitem)
                }

            }
            else
            {
                //first numeric Formulapart found
                numFoundIndex = g;
                g++;
            }
        }
        else if(formulaParts->at(g)->getGType()==MFPartType::NUMERIC_AND_VARIABLE)
        {
            //

            QString varName="";
            if(formulaParts->at(g)->getVariableName(varName)==1)
            {
                QMap<QString, int>::const_iterator iter = varMap->find(varName);
                if(iter != varMap->end())
                {
                    //Variable was found in Map
                    int foundVarIndex = iter.value();
                    double val1=-1;
                    double val2=-1;
                    if(formulaParts->at(foundVarIndex)->getNumericValue(val1) && formulaParts->at(g)->getNumericValue(val2))
                    {
                        //Parts have to be sorted!!
                        formulaParts->at(foundVarIndex)->getTokenList().at(0)->setValue(QString::number(val1+val2));
                        formulaParts->removeAt(g);
                    }
                    else
                    {
                        qDebug()<<"MFFormula: simplify: could not convert Variable-Koeffizients.";
                        g++;
                    }
                }
                else
                {
                    //Variable not in Map yet
                    varMap->insert(varName,g);
                    g++;
                }

            }
            else
                g++;
        }
        else
            g++;

        //qDebug()<<"MFFormula: simplify: outer while loop. Counter: "<< QString::number(g) <<"   Listsize: " <<  formulaParts->count();
    }


/*
    simplifiedparts="MFFormula: simplified formula (part 2): ";
    for(int u =0; u < formulaParts->count(); u++)
    {
        //qDebug()<<"simplify: start simplifying Part: " << partsList->at(i)->at(u)->tokenListToString();
        simplifiedparts += formulaParts->at(u)->tokenListToString() + " + ";
    }
    simplifiedparts = simplifiedparts.remove(simplifiedparts.lastIndexOf("+"), simplifiedparts.count()) + " = 0";
    qDebug()<<simplifiedparts;
*/

    //remove entries that are null
    int u =0;
    while( u < formulaParts->count())
    {
        if(formulaParts->at(u)->getGType() == MFPartType::NUMERIC || formulaParts->at(u)->getGType() == MFPartType::NUMERIC_AND_VARIABLE)
        {
            double coefVal;
            if(formulaParts->at(u)->getNumericValue(coefVal))
            {
                if(relDif(coefVal, 0) <= Tolerance)
                {
                    formulaParts->removeAt(u);
                }
                else
                    u++;
            }
            else
                u++;
        }
        else
            u++;
    }
/*
    simplifiedparts="MFFormula: simplified formula (part 3): ";
    for(int u =0; u < formulaParts->count(); u++)
    {
        //qDebug()<<"simplify: start simplifying Part: " << partsList->at(i)->at(u)->tokenListToString();
        simplifiedparts += formulaParts->at(u)->tokenListToString() + " + ";
    }
    simplifiedparts = simplifiedparts.remove(simplifiedparts.lastIndexOf("+"), simplifiedparts.count()) + " = 0";
    qDebug()<<simplifiedparts;
*/
}


//creates a List of all the formula-Parts (each part represented by coeficientvalue and VariablePointer)
QList<QPair<double,MVariable*> *> *MFFormula::getCoeficientList()
{
    QList<QPair<double,MVariable*>*> *retVal = nullptr;
    if(!formulaParts->isEmpty())
    {
        retVal = new QList<QPair<double,MVariable*>*>();

        for(int i = 0; i<formulaParts->count(); i++)
        {
            if(formulaParts->at(i)->getVariablePair() != nullptr)
                retVal->append(formulaParts->at(i)->getVariablePair());
        }
    }
    return retVal;
}


QString MFFormula::getSimplifiedFormulaString()
{
    QString result="";

    if(!formulaParts->isEmpty())
    {
        for(int i = 0; i<formulaParts->count();i++)
        {
            result += formulaParts->at(i)->tokenListToString() + " + ";
        }
        result = result.remove(result.lastIndexOf("+"),2) + " = 0";
    }
    return result;
}


double MFFormula::relDif(double a, double b)
{
    double c = Abs(a);
    double d = Abs(b);

    d = Max(c, d);

    return d == 0.0 ? 0.0 : Abs(a - b) / d;
}
