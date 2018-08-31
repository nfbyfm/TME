#include "mformula.h"



MFormula::MFormula(QObject *parent) : QObject(parent)
{
    comparator_count =0;
    comparator_IsEqualSign = false;
    noOfVariables =0;
    contains_Function = false;
    isSolved = false;
}

MFormula::~MFormula()
{
    qDeleteAll(tokenList);
}


#define GETTERS_AND_SETTERS_START {

    QList<MToken *> MFormula::getTokenList() const
    {
        return tokenList;
    }

    void MFormula::setTokenList(const QList<MToken *> &value)
    {
        tokenList = value;

        comparator_count =0;
        comparator_IsEqualSign = false;
        noOfVariables =0;
        contains_Function = false;

        for(int k=0; k<tokenList.size(); k++)
        {
            switch(tokenList.at(k)->getType())
            {
                case MTokenType::COMPARATOR:
                    comparator_count++;
                    if(tokenList.at(k)->getValue()=="=")
                        comparator_IsEqualSign=true;
                    break;
                case MTokenType::FUNCTION:
                    contains_Function=true;
                    break;
                case MTokenType::VARIABLE:
                    noOfVariables++;

                default:
                    break;
            }
        }
    }

    QList<MToken *> MFormula::getTokenVariables()
    {
        QList<MToken *> retList;

        if(noOfVariables>0)
        {
            for(int k=0; k<tokenList.size(); k++)
            {
                if(tokenList.at(k)->getType() == MTokenType::VARIABLE)
                {
                    retList.append(tokenList.at(k));
                }
            }
        }

        return retList;
    }

    QString MFormula::getVariableNames()
    {
        QString retval = "";

        if(noOfVariables>0)
        {
            for(int k=0; k<tokenList.size(); k++)
            {
                if(tokenList.at(k)->getType() == MTokenType::VARIABLE)
                {
                    retval = retval + tokenList.at(k)->getValue() + ", ";
                }
            }
        }

        if(retval.size() >2)
        {
            retval = retval.remove(retval.size()-2,2);
        }

        return retval;
    }


    QString MFormula::getID() const
    {
        return ID;
    }

    void MFormula::setID(const QString &value)
    {
        ID = value;
    }

    bool MFormula::getSolvable() const
    {
        return solvable;
    }

    void MFormula::setSolvable(bool value)
    {
        solvable = value;
    }

    int MFormula::getNoOfComparators()
    {
        return this->comparator_count;
    }

    int MFormula::getNoOfVariables()
    {
        return this->noOfVariables;
    }

    bool MFormula::containsFunction()
    {
        return this->contains_Function;
    }

    bool MFormula::comparatorIsEqualSign()
    {
        return this->comparator_IsEqualSign;
    }

    bool MFormula::getIsSolved() const
    {
        return isSolved;
    }

    void MFormula::setIsSolved(bool value)
    {
        isSolved = value;
    }

    bool MFormula::hasBrackets()
    {
        bool retVal = false;

        if(!tokenList.isEmpty())
        {
            for(int i =0; i< tokenList.count(); i++)
            {
                if(tokenList.at(i)->getType()==MTokenType::PRIORITIZER)
                {
                    retVal = true;
                }
            }
        }

        return retVal;
    }

    bool MFormula::hasPowerFunction()
    {
        bool retVal = false;

        if(!tokenList.isEmpty())
        {
            for(int i =0; i< tokenList.count(); i++)
            {
                if(tokenList.at(i)->getValue()=="^")
                {
                    retVal = true;
                }
            }
        }

        return retVal;
    }

#define GETTERS_AND_SETTERS_END }



QString MFormula::toString()
{
    QString retVal ="";
    for(int i =0; i< this->tokenList.size();i++)
    {
        retVal += tokenList.at(i)->getValue();
    }
    return retVal;
}


