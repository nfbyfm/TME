#include "presolver.h"

PreSolver::PreSolver(QObject *parent) : QObject(parent)
{

}



QList<MFFormula *> * PreSolver::getPartitionedFormulasList(QList <MFormula *> f_origList)
{
    //first: for each formula: plug in varaible-values if possible, set formula 'solvable' anew accordingly
    qDebug()<<"";
    qDebug()<< "FormulaList before update: ";
    for(int i =0; i<f_origList.count();i++)
    {
        qDebug()<<f_origList.at(i)->toString() + "      solvable: " + QString::number(f_origList.at(i)->getSolvable()) + "      solved: " + QString::number(f_origList.at(i)->getIsSolved());;
    }

    QList <MFormula *> f_List = updateUnsolvedEquations(f_origList);

    qDebug()<<"";
    qDebug()<< "FormulaList after update: ";
    for(int i =0; i<f_List.count();i++)
    {
        qDebug()<<f_List.at(i)->toString() + "      solvable: " + QString::number(f_List.at(i)->getSolvable()) + "      solved: " + QString::number(f_List.at(i)->getIsSolved());
    }
    //QList <MFormula *> f_List = f_origList;

    //create standardized List for the Translator (a_n*x_n + a_n-1 * x_n-1 + .... + a_0 = 0)
    QList <MFFormula *> * partitionedFormulaList = new QList <MFFormula *>();

    for(int i = 0; i< f_List.count(); i++)
    {
        if(f_List.at(i)->getSolvable() && !f_List.at(i)->getIsSolved())
        {

            //MFormula *tempFormula = new MFormula(nullptr);
            QList <MFPart *> * partsList = new QList<MFPart *>();
            QList <MToken * > origTokenList = f_List.at(i)->getTokenList();
            MFPart *tmpPart = new MFPart();
            bool negatePart = false;

            for(int k =0; k < origTokenList.count(); k++)
            {
                //
                QString tokenVal = origTokenList.at(k)->getValue();
                tmpPart->setOrigFormula(f_List.at(i));
                switch(origTokenList.at(k)->getType())
                {
                    case MTokenType::CONSTANT:
                        //replace by numeric value
                        tmpPart->setNegateElements(negatePart);
                        tmpPart->appendTokenList(constantTokenToNumeric(tokenVal));
                        break;

                    case MTokenType::NUMBER:
                        tmpPart->setNegateElements(negatePart);
                        //don't use original because number will get changed
                        //check if prevoious element in tempList is Operator "/"

                        numberTokenReciproque(origTokenList.at(k), tmpPart);
                        break;
                    case MTokenType::VARIABLE:
                        //check if Variable has already been solved -> replace by Numeric-Value Token !!!
                        tmpPart->setNegateElements(negatePart);
                        tmpPart->appendTokenList(variableTokenNumeric(origTokenList.at(k)));
                        break;
                    case MTokenType::COMPARATOR:
                        if(tokenVal=="=")
                        {
                            tmpPart->setNegateElements(negatePart);
                            partsList->append(tmpPart);
                            //qDebug()<<"= Sign found. Adding Part to List: " << tmpPart->tokenListToString();
                            tmpPart = new MFPart();
                            negatePart=true;
                        }
                        else
                        {
                            f_List.at(i)->setSolvable(false);
                            k = origTokenList.count();
                        }
                        break;
                    case MTokenType::OPERATOR:
                        if(tokenVal == "+")
                        {
                            tmpPart->setNegateElements(negatePart);
                            partsList->append(tmpPart);
                            //qDebug()<<"+ Sign found. Adding Part to List: " << tmpPart->tokenListToString();
                            tmpPart = new MFPart();

                        }
                        else if (tokenVal=="-")
                        {
                            tmpPart->setNegateElements(negatePart);
                            //
                            if(tmpPart->getTokenList().count()>0)
                                partsList->append(tmpPart);
                            //qDebug()<<"- Sign found. Adding Part to List: " << tmpPart->tokenListToString();
                            tmpPart = new MFPart();
                            //tmpPart->appendTokenList(origTokenList.at(k));
                            tmpPart->appendTokenList(new MToken(nullptr,"-1",MTokenType::NUMBER));
                            tmpPart->appendTokenList(new MToken(nullptr,"*",MTokenType::OPERATOR));

                        }
                        else if (tokenVal == "*")
                        {
                            tmpPart->appendTokenList(origTokenList.at(k));
                        }
                        else if(tokenVal == "/")
                        {
                            tmpPart->appendTokenList(origTokenList.at(k));
                        }
                        else if(tokenVal =="^")
                        {
                            f_List.at(i)->setSolvable(false);
                            k = origTokenList.count();
                        }
                        break;
                    default:
                        break;
                }
            }
            //add the last element

            if(tmpPart->getTokenList().count()>0 && !((tmpPart->getTokenList().count()==2) && (tmpPart->getTokenList().at(0)->getValue()=="-1") && (tmpPart->getTokenList().at(1)->getValue()=="*") ))
                partsList->append(tmpPart);

            /*
            qDebug()<<"Formula: " + f_List.at(i)->toString();

            QString newLine = "Formula from parts: ";
            for(int u = 0; u < partsList->count(); u++)
                newLine += partsList->at(u)->tokenListToString() + " + ";
            newLine = newLine.remove(newLine.lastIndexOf("+"),2);
            newLine += "= 0";

            qDebug()<<newLine;
            */

            //check for errors
            bool errorFound=false;
            for(int u = 0; u < partsList->count(); u++)
            {
                if(partsList->at(u)->divisionError())
                {
                    //emit Error
                    f_List.at(i)->setSolvable(false);
                    qDebug()<<"Error in equation " << f_List.at(i)->toString() << ", Part: " << partsList->at(u)->tokenListToString() << ": Division by variable found.";
                    errorFound = true;
                }
                if(partsList->at(u)->multiplError())
                {
                    //emit Error
                    f_List.at(i)->setSolvable(false);
                    qDebug()<<"Error in equation " << f_List.at(i)->toString() << ", Part: " << partsList->at(u)->tokenListToString() << ": Multiple variables get multiplied.";
                    errorFound = true;
                }
            }

            //if no errors found in any of the Formula-Parts -> add list to Mainlist
            if(!errorFound)
            {
                MFFormula *newFormula = new MFFormula(f_List.at(i));
                newFormula->setFormulaParts(partsList);
                partitionedFormulaList->append(newFormula);
            }

        }
    }


    simplifyEquations(partitionedFormulaList);

    return partitionedFormulaList;
}


//simplify equations
void PreSolver::simplifyEquations(QList<MFFormula *> *mfFormulaList)
{
    if(mfFormulaList!=nullptr)
    {
        //simplify each formula
        int i= 0;
        while( i< mfFormulaList->count())
        {
            mfFormulaList->at(i)->simplify();

            if(mfFormulaList->at(i)->getNumberOfVariables()<=0)
            {
                //formula is invalid
                //qDebug()<<"Mathengine: simplifier: found Formula that is invalid / has no Variables in it after simplification.";
                MFormula *mVal = qobject_cast<MFormula *>(mfFormulaList->at(i)->parent());
                if(mVal!=nullptr)
                {
                    //qDebug()<<"Mathengine: simplifier: set formula to unsolvable:" << mVal->toString();
                    mVal->setSolvable(false);
                    mfFormulaList->removeAt(i);
                    emit sendError(new ErrorMessage(this,ERROR_ID::MATHENGINE_NoVariableInForumla,mVal));
                    qDebug()<<"removed MFFormula at index " << i;
                    //i=i-1;
                }
                else
                {
                    qDebug()<<"Mathengine: simplifier: Invalid Formula couldn't be cast / set to invalid!!";
                    i++;
                }
            }
            else
                i++;
            //qDebug()<<i << " of " << mfFormulaList->count();
        }
        /*
        qDebug()<<"Solver: simplifyEquations done";
        for(int u =0; u< mfFormulaList->count();u++)
        {
            qDebug()<<mfFormulaList->at(u)->getSimplifiedFormulaString();
        }
        */
    }
    else
    {
        qDebug()<<"Error Solver: simplifyEquations: recieved List of Parts-Formulas is empty (nullptr).";
    }

}

//update unsolved equations
QList<MFormula *> PreSolver::updateUnsolvedEquations(QList<MFormula *> mFormulaList)
{
    QList<MFormula *> retVal;

    if(!mFormulaList.isEmpty())
    {
        qDebug()<<"";
        qDebug()<<"find and update unsolved formulas";

        for(int i=0; i< mFormulaList.count(); i++)
        {
            if(mFormulaList.at(i)->getIsSolved()==false)
            {
                //check if formula is really unsolved

                if(!mFormulaList.at(i)->getTokenVariables().isEmpty())
                {
                    QList<MToken *> tokenList = mFormulaList.at(i)->getTokenList();
                    int noOfunsolvedVariables =0;
                    QList<MToken *> newFormulaTokenList;
                    for(int u =0; u<tokenList.count();u++)
                    {
                        //check each token: if it is a unsolved variable add 1 to counter
                        //otherwise: plug in the numeric value
                        if(tokenList.at(u)->getType()==MTokenType::VARIABLE)
                        {
                            //try to get Varaible
                            MVariable *tmpVar = qobject_cast<MVariable*>(tokenList.at(u)->getMObject());
                            if(tmpVar!=nullptr)
                            {
                                if(tmpVar->getSolved())
                                {
                                    //add new numeric token to newFormulaList
                                    MToken *newNumToken = new MToken(tokenList.at(u),QString::number(tmpVar->getNumericValue()),MTokenType::NUMBER);
                                    newFormulaTokenList.append(newNumToken);
                                }
                                else
                                {
                                    //add to list, up counter
                                    noOfunsolvedVariables++;
                                    newFormulaTokenList.append(tokenList.at(u));
                                }
                            }
                            else
                            {
                                newFormulaTokenList.append(tokenList.at(u));
                                qDebug()<<"Mathengine: simplifyUnsolvedEquations: Error casting MToken-parent to MVaraible.";
                            }
                        }
                        else
                        {
                            newFormulaTokenList.append(tokenList.at(u));
                        }

                    }

                    if(noOfunsolvedVariables ==1)
                    {
                        //solve newFormulaTokenList -> write
                        qDebug()<<"found formula to solve: " + mFormulaList.at(i)->toString();

                        MFormula *newFormula = new MFormula(nullptr);
                        newFormula->setTokenList(newFormulaTokenList);
                        newFormula->setSolvable(true);
                        retVal.append(newFormula);
                    }
                    else
                    {
                        //if number of unsolved variables equals one, solve the equation
                        qDebug()<<"unsolved equation: " + mFormulaList.at(i)->toString();
                        if(noOfunsolvedVariables==0)
                        {
                            mFormulaList.at(i)->setSolvable(true);
                            mFormulaList.at(i)->setIsSolved(true);
                        }
                        retVal.append(mFormulaList.at(i));
                    }
                }
                else
                {
                    retVal.append(mFormulaList.at(i));
                }

            }
            else
            {
                //these formulas have already been solved!!
                //retVal.append(mFormulaList.at(i));
            }
        }





    }
    else
    {
        qDebug()<<"Error Presolver: updateEquations: recieved List of Parts-Formulas is empty (nullptr).";
    }

    return retVal;
}




//replaces a Constant-Token with a Number-Token
MToken * PreSolver::constantTokenToNumeric(QString constValue)
{
    MToken *newToken = new MToken(nullptr,"const", MTokenType::NUMBER);
    if(constValue.contains("pi",Qt::CaseInsensitive))
    {
        newToken->setValue(QString::number(M_PI));
    }
    else
    {
        //unknown constant
        newToken->setValue(QString::number(1));
    }
    return newToken;
}

//checks if given token is Varaible. Returns Number-Token if varaible has been solved.
MToken * PreSolver::variableTokenNumeric(MToken* tokenPointer)
{
    MToken *retVal = tokenPointer;

    if(tokenPointer != nullptr)
    {
        MVariable *mVal = qobject_cast<MVariable *>(tokenPointer->getMObject());
        if(mVal != nullptr)
        {
            if(mVal->getSolved() && !mVal->getOverdetermined())
            {
                retVal = new MToken(nullptr, QString::number(mVal->getNumericValue()),MTokenType::NUMBER);
                //qDebug()<<"replaced a variable "<<mVal->getTextValue()<<" by it's numeric value: " <<mVal->getNumericValue();
            }
        }
    }
    return retVal;
}




//checks if a division by number is supposed to take place
 void PreSolver::numberTokenReciproque(MToken* tokenPointer, MFPart *tmpPart)
{


    if(tokenPointer!=nullptr && tmpPart !=nullptr)
    {
        MToken *newElement = new MToken(tokenPointer,tokenPointer->getValue(),MTokenType::NUMBER);

        int numberOfElements = tmpPart->getTokenList().count();
        if(numberOfElements > 0)
            if(tmpPart->getTokenList().at(numberOfElements-1)->getType()==MTokenType::OPERATOR)
                if(tmpPart->getTokenList().at(numberOfElements-1)->getValue()=="/")
                {
                    //get double-value and calculate reciproque value
                    double value=-1;
                    bool toDoubleSuccess = false;
                    value = newElement->getValue().toDouble(&toDoubleSuccess);//tmpPart->getTokenList().at(numberOfElements)->getValue().toDouble(&toDoubleSuccess);

                    if(toDoubleSuccess)
                    {
                        //
                        //tmpPart->getTokenList().removeLast();
                        tmpPart->removeLastToken();
                        tmpPart->appendTokenList(new MToken(nullptr, "*", MTokenType::OPERATOR));
                        newElement = new MToken(tokenPointer,QString::number(1/value),MTokenType::NUMBER);
                        qDebug()<<"Presolver: division by Number detected. turned into multiplication." << tmpPart->tokenListToString();
                    }
                    else
                        qDebug()<<"Presolver: division by Number detected. could not turn into mulitplication.";

                }

        tmpPart->appendTokenList(newElement);
        qDebug()<<"Presolver: numberTokenReciproque: " << tmpPart->tokenListToString();

    }
}
