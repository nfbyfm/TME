#include "parser.h"


Parser::Parser(QObject *parent) : QObject(parent)
{

}

void Parser::startParsing(QList< QList<MToken *> > tf_list)
{


    //qDebug() << "Parser: List of tokenized formulas recieved";
    int f_counter =1;
    QList <MFormula *> f_List;
    QList <MVariable *> v_List;

    for(int u=0; u<tf_list.size(); u++)
    {
        if( tf_list.at(u).size() >0)
        {
            if(tf_list.at(u).size()==1 && tf_list.at(u).at(0)->getType()==MTokenType::LINK)
            {
                //simple link detected -> ignore
                qDebug() << "Parser found simple Link-functioncall. Ignoring it.";
            }
            else
            {
                //create a formula-Object, add to temporary List
                MFormula *tempFormula = new MFormula();
                tempFormula->setTokenList(tf_list.at(u));
                tempFormula->setSolvable(true);
                tempFormula->setID("F_" + padZeroNumber(f_counter));
                f_counter++;
                f_List.append(tempFormula);
            }
        }
    }

    //filter equations that definitely can not be solved -> add to Errorlist
    for(int i = 0; i< f_List.size(); i++)
    {
        //qDebug() << "Formula number: " << f_List.at(i)->getID() << "  Formula: " << f_List.at(i)->toString();

        int comparator_count = f_List.at(i)->getNoOfComparators();
        bool contains_Function = f_List.at(i)->containsFunction();
        bool comparatorIsEqualSign = f_List.at(i)->comparatorIsEqualSign();
        int noOfVariables = f_List.at(i)->getNoOfVariables();

        ErrorMessage *msg;

        if(contains_Function)
        {
            f_List.at(i)->setSolvable(false);
            msg = new ErrorMessage(nullptr, ERROR_ID::PARSER_ContainsFunctions, f_List.at(i));
            emit sendError(msg);
        }

        if(f_List.at(i)->hasBrackets())
        {
            f_List.at(i)->setSolvable(false);
            msg = new ErrorMessage(nullptr, ERROR_ID::PARSER_Contains_Brackets, f_List.at(i));
            emit sendError(msg);
        }


        if(f_List.at(i)->hasPowerFunction())
        {
            f_List.at(i)->setSolvable(false);
            msg = new ErrorMessage(nullptr, ERROR_ID::PARSER_ContainsPowerFunction, f_List.at(i));
            emit sendError(msg);
        }


        if( (comparator_count>1))
        {
            f_List.at(i)->setSolvable(false);
            msg = new ErrorMessage(nullptr, ERROR_ID::PARSER_TooManyComparators, f_List.at(i));
            emit sendError(msg);
        }
        else
        {
            if(comparator_count==1)
            {
                //check if equal sign
                if(!comparatorIsEqualSign)
                {
                    //error: Comparator not supported
                    f_List.at(i)->setSolvable(false);
                    msg = new ErrorMessage(nullptr, ERROR_ID::PARSER_ComparatorNotSupported, f_List.at(i));
                    emit sendError(msg);
                }
            }
            else
            {
                //error: no comparator in equation
                f_List.at(i)->setSolvable(false);
                msg = new ErrorMessage(nullptr, ERROR_ID::PARSER_NoComparatorInEquation, f_List.at(i));
                emit sendError(msg);
            }
        }

        if(noOfVariables<1)
        {
            //non-sense formula (?)
            f_List.at(i)->setSolvable(false);
            msg = new ErrorMessage(nullptr, ERROR_ID::PARSER_NoVariableFound, f_List.at(i));
            emit sendError(msg);
        }
        else
        {
            //add Variables to List
            QList <MToken *> varialist = f_List.at(i)->getTokenVariables();
            bool bfound;
            foreach(MToken *vToken, varialist)
            {
                bfound = false;
                foreach(MVariable *var, v_List)
                {
                    //
                    if(var->getTextValue() == vToken->getValue())
                    {
                        bfound = true;
                        var->addFormulaRef(f_List.at(i));
                        vToken->setMObject(var);
                        //vToken->setVariableRef(var);
                        break;
                    }
                }

                if(!bfound)
                {
                    MVariable *newVar = new MVariable(nullptr);
                    newVar->addFormulaRef(f_List.at(i));
                    newVar->setTextValue(vToken->getValue());
                    newVar->setOverdetermined(false);
                    vToken->setMObject(newVar);
                    //vToken->setVariableRef(newVar);
                    v_List.append(newVar);
                }
            }
            /*
            foreach (MToken *varToken, varialist)
            {
                qDebug()<<varToken->getValue();
            }*/
            /*
            if(noOfVariables ==1)
            {
                //directly solvable equation
            }
            else
            {
                //multiple varaibles in the equation
            }
            */
        }
    }

/*
    //List of Varaibles:
    qDebug()<<"Variablelist:";
    foreach(MVariable *var, v_List)
    {
        qDebug() << "Variable: " << var->getTextValue() << " used in: " << var->getFormulaNumberList();
    }
*/
    //QList <MFormula *> *f_pList = new QList <MFormula *>();

    //solve simple equations (e.g. Varaible = numeric value)
    for(int i=0; i<f_List.size();i++)
    {
        MFormula *formula = f_List.at(i);
        if(formula->getNoOfComparators()==1 && formula->comparatorIsEqualSign() && formula->getNoOfVariables()==1 && formula->getSolvable())
        {
            //check if variable has already been solved and if the result is the same
            if(solveSimpleEquation(formula))//, v_List))
            {
                //mark equation as solved
                formula->setIsSolved(true);
            }
        }
    }





    emit sendMathData(f_List,v_List);//needed for model and translator

}

//returns true if the equation could be solved
bool Parser::solveSimpleEquation(MFormula *formula)//, QList <MVariable *> v_List)
{
    bool result = false;

    if(formula != nullptr)
    {
        QList<MToken *> tList = formula->getTokenList();
        if(tList.size()==3)
        {
            bool config1 = (tList.at(0)->getType()==MTokenType::VARIABLE && tList.at(2)->getType()==MTokenType::NUMBER);
            bool config2 = (tList.at(2)->getType()==MTokenType::VARIABLE && tList.at(0)->getType()==MTokenType::NUMBER);
            result = config1 || config2;

            int valueIndex = -1;
            int variableIndex = -1;

            if(config1)//Variable stands at the start (Variable = Number)
            {
                valueIndex = 2;
                variableIndex = 0;
            }

            if(config2)
            {
                valueIndex = 0;
                variableIndex = 2;
            }

            if((config1 || config2) && valueIndex>=0)
            {

                double value = 0;
                bool toDoubleSuccess = false;
                value = tList.at(valueIndex)->getValue().toDouble(&toDoubleSuccess);

                if(toDoubleSuccess)
                {
                    //check if the Varaible can be found and if the Value has already been set
                    MVariable * tempVaria = qobject_cast<MVariable *>(tList.at(variableIndex)->getMObject());

                    if(tempVaria != nullptr)
                    {
                        //qDebug()<<"Successfull cast the Variable Pointer! " << tempVaria->getTextValue();
                        if(tempVaria->getOverdetermined())
                        {
                            //skip. Varaible is already overdetermined
                            result = false;
                        }
                        else
                        {
                            if(tempVaria->getSolved()) //Variable has already a solution from another formula
                            {
                                //compare results
                                if(relDif(tempVaria->getNumericValue(), value) <= Tolerance)
                                {
                                    tempVaria->setSolved(true);
                                    result = true;
                                }
                                else
                                {
                                    //Error: difference between found value and already given value is too big -> overdetermined
                                    qDebug()<<"Error simple solver: Variable " << tempVaria->getTextValue() << " is overdetermined.";
                                    tempVaria->setSolved(false);
                                    tempVaria->setOverdetermined(true);
                                    result = false;
                                }
                            }
                            else //Varaible has not been solved yet -> set value
                            {
                                tempVaria->setNumericValue(value);
                                tempVaria->setSolved(true);
                                tempVaria->setOverdetermined(false);
                                result = true;
                            }
                        }
                    }
                    else
                    {
                        qDebug()<<"Parser: Error simple solver: Could not cast variable: " << tList.at(variableIndex)->getValue();
                    }

                    /*
                    int index = -1;
                    for(int k =0; k< v_List.count(); k++)
                    {
                        if(v_List.at(k)->isInFormula(formula))
                        {
                            index = k;
                            break;
                        }
                    }


                    //Varaible found in List -> check if already solved
                    if(index >=0)
                    {
                        if(v_List.at(index)->getOverdetermined())
                        {
                            //skip. Varaible is already overdetermined
                            result = false;
                        }
                        else
                        {
                            if(v_List.at(index)->getSolved()) //Variable has already a solution from another formula
                            {
                                //compare results
                                if(relDif(v_List.at(index)->getNumericValue(), value) <= Tolerance)
                                {
                                    v_List.at(index)->setSolved(true);
                                    result = true;
                                }
                                else
                                {
                                    //Error: difference between found value and already given value is too big -> overdetermined
                                    qDebug()<<"Error simple solver: Variable " << v_List.at(index)->getTextValue() << " is overdetermined.";
                                    v_List.at(index)->setSolved(false);
                                    v_List.at(index)->setOverdetermined(true);
                                    result = false;
                                }
                            }
                            else //Varaible has not been solved yet -> set value
                            {
                                v_List.at(index)->setNumericValue(value);
                                v_List.at(index)->setSolved(true);
                                v_List.at(index)->setOverdetermined(false);
                                result = true;
                            }
                        }

                    }
                    else
                    {
                        qDebug()<<"Parser: simple solver: Varaible " << tList.at(1)->getValue() << " could not be found in formula " << formula->toString();
                    }
                    */
                }
                else
                    qDebug()<<"Parser: Error: could not convert value " << tList.at(1)->getValue() << " to double.";
            }
        }
    }

    return result;
}

QString Parser::padZeroNumber(int number)
{
    QString result="";
    int strNumberLength = QString::number(number).length();
    for(int i=0; i<6-strNumberLength; i++)
    {
        result+="0";
    }
    result+=QString::number(number);
    return result;
}

double Parser::relDif(double a, double b)
{
    double c = Abs(a);
    double d = Abs(b);

    d = Max(c, d);

    return d == 0.0 ? 0.0 : Abs(a - b) / d;
}

