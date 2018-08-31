#include "mfpart.h"

/*
 * Formula-Part (needed by Parser and Translator)
 */




MFPart::MFPart(QObject *parent) : QObject(parent)
{
    this->gType = MFPartType::UNDEF;
}

void MFPart::setTokenValue(int index, QString newValue)
{
    if(!tokenList.isEmpty())
    {
        if(index < tokenList.count() && index >=0)
        {
            tokenList.at(index)->setValue(newValue);
        }
    }
}

void MFPart::removeLastToken()
{
    if(!tokenList.isEmpty())
        tokenList.removeLast();
}
#define GETTERS_AND_SETTERS_START {

    MFormula *MFPart::getOrigFormula() const
    {
        return origFormula;
    }

    void MFPart::setOrigFormula(MFormula *value)
    {
        origFormula = value;
    }

    QList<MToken *> MFPart::getTokenList() const
    {
        return tokenList;
    }

    void MFPart::setTokenList(const QList<MToken *> &value)
    {
        tokenList = value;
    }

    void MFPart::appendTokenList(MToken * newElement)
    {
        if(newElement!=nullptr)
        {
            tokenList.append(newElement);
            updateType();
        }
    }

    bool MFPart::getNegateElements() const
    {
        return negateElements;
    }

    void MFPart::setNegateElements(bool value)
    {
        negateElements = value;
    }

    MFPartType MFPart::getGType() const
    {
        return gType;
    }

    void MFPart::setGType(const MFPartType &value)
    {
        gType = value;
    }


    QString MFPart::tokenListToString()
    {
        QString result = "";

        if(!tokenList.isEmpty())
        {
            if(negateElements)
                result += "-(";

            for(int u =0; u <tokenList.count(); u++)
                result += tokenList.at(u)->getValue();

            if(negateElements)
                result += ")";
        }
        else
            result="List is empty";



        return result;
    }
#define GETTERS_AND_SETTERS_END }




//if there are more than one Token: try to multiply / divide / simplify equationpart
void MFPart::simplifyList()
{
    //if there are more than one Token: try to multiply / divide / simplify equationpart
    if(!tokenList.isEmpty())
    {
        updateType();

        //check if first Element is Minus-sign
        if(tokenList.at(0)->getValue()=="-")
        {
            qDebug()<<"Simplify Part: "<<tokenListToString()<<": Found '-' in first Token: "<< tokenList.at(0)->getValue();

            if(gType==MFPartType::NUMERIC || gType==MFPartType::NUMERIC_AND_VARIABLE)
            {
                //integrate minus-sign into numeric Token
                for(int i = 1; i<tokenList.count(); i++)
                {
                    if(tokenList.at(i)->getType()==MTokenType::NUMBER)
                    {
                        //
                        double firstValue = 0;
                        bool toDoubleSuccess = false;
                        firstValue =tokenList.at(i)->getValue().toDouble(&toDoubleSuccess);
                        if(toDoubleSuccess)
                        {
                            tokenList.at(i)->setValue(QString::number(firstValue*(-1)));
                            tokenList.removeAt(0); //remove minus Token
                            break;
                        }
                        else
                        {
                            qDebug()<<"Simplify Part: Minus-Sign found at beginning of Tokenlist. Could not convert Value of first numeric Token: " <<tokenList.at(i)->getValue();
                        }
                    }
                }
            }
        }

        updateType();

        //simplify numeric values
        if(tokenList.count()>1 && (gType==MFPartType::NUMERIC || gType==MFPartType::NUMERIC_AND_VARIABLE))
        {
            //qDebug()<<"Simplifying Part: try to combine numeric tokens. Part: " << tokenListToString();

            int i = tokenList.count()-1;
            while(i>=0 )
            {


                if(tokenList.at(i)->getType()==MTokenType::NUMBER)// && tokenList.count()>1)
                {

                    int k=0;
                    while( k<tokenList.count())
                    {


                        //check for other number
                        if(tokenList.at(k)->getType()==MTokenType::NUMBER)
                        {
                            //look for another number
                            bool multply = false;
                            bool divide = false;
                            bool found=false;
                            int firstIndex = k;
                            k++;

                            while(found==false)
                            {

                                if(tokenList.at(k)->getType()==MTokenType::OPERATOR)
                                {
                                    if(tokenList.at(k)->getValue()=="*")
                                    {
                                        multply = true;
                                        divide = false;
                                    }
                                    if(tokenList.at(k)->getValue()=="/")
                                    {
                                        multply = false;
                                        divide = true;
                                    }
                                    //k++;
                                }
                                else if (tokenList.at(k)->getType()==MTokenType::NUMBER)
                                {
                                    //
                                    if(multply || divide)
                                    {
                                        double firstValue = 0;
                                        bool toDoubleSuccess = false;
                                        firstValue = tokenList.at(firstIndex)->getValue().toDouble(&toDoubleSuccess);
                                        double secondValue = 0;
                                        bool toDoubleSuccess2 = false;
                                        secondValue = tokenList.at(k)->getValue().toDouble(&toDoubleSuccess2);


                                        if(toDoubleSuccess && toDoubleSuccess2)
                                        {
                                            if(multply)
                                            {
                                                tokenList.at(firstIndex)->setValue(QString::number(firstValue*secondValue));
                                                tokenList.removeAt(k);
                                                tokenList.removeAt(k-1);
                                                k = k-2;
                                            }
                                            else if (divide)
                                            {
                                                tokenList.at(firstIndex)->setValue(QString::number(firstValue/secondValue));
                                                tokenList.removeAt(k);
                                                tokenList.removeAt(k-1);
                                                k = k-2;
                                            }
                                        }
                                        else
                                            qDebug()<<"Error simplifying Part: couldn't convert QString to double: First number: "<<  tokenList.at(firstIndex)->getValue() << " second Number: " << tokenList.at(k)->getValue();


                                    }
                                    else
                                        qDebug()<<"Error simplifying Part: Second Number found but no divison- or multipication-operator";
                                    //k++;
                                }

                                k++;

                                //qDebug()<<"simplify Part: third Loopindex: " <<k << " size of part: "<< tokenList.count() << "     part: "<<tokenListToString();

                                if(k>tokenList.count()-1)
                                    found=true;
                            }
                            if(found==true)
                                i=0;
                        }

                        //qDebug()<<"simplify Part: second Loopindex: "<<k;
                        k++;
                    }
                }


                i--;
                //qDebug()<<"simplify Part: first for Loopindex: " << i;
            }

        }

        //qDebug()<<"start updating Type";
        updateType();

        //qDebug()<<"sorting Part starting";

        //sort TokenList
        if(tokenList.count()>=3 && (gType==MFPartType::NUMERIC || gType==MFPartType::NUMERIC_AND_VARIABLE))
        {
            int i =0;
            while(i<tokenList.count()-1)
            {
                if(tokenList.at(i)->getType()==MTokenType::VARIABLE)
                {
                    //MToken *tempToken = tokenList.at(0);
                    if(i==0)
                    {
                        tokenList.append(new MToken(nullptr,"*",MTokenType::OPERATOR));
                        tokenList.move(i,tokenList.count()-1);
                    }
                    else
                    {
                        tokenList.move(i-1,tokenList.count()-1);    //Operator
                        tokenList.move(i,tokenList.count()-1);      //Variable
                    }

                }
                else
                    i++;
            }

        }


        //qDebug()<<"start negation resolution";

        //resolve negation
        if (tokenList.count()==1)
        {
            //List contains only one Token
            if(tokenList.at(0)->getType()==MTokenType::NUMBER)
            {
                //handle negation
                if(negateElements)
                {
                    double firstValue = 0;
                    bool toDoubleSuccess = false;
                    firstValue = tokenList.at(0)->getValue().toDouble(&toDoubleSuccess);
                    if(toDoubleSuccess)
                    {
                        tokenList.at(0)->setValue(QString::number((firstValue*(-1))));
                    }
                    else
                        qDebug()<<"Simplifier: Handling of Negation: Partvalue could not be converted to double: "<< tokenList.at(0)->getValue();
                }


            }
            else if(tokenList.at(0)->getType()==MTokenType::VARIABLE)
            {
                //add NumberToken infront with the correct value
                MToken *newNumToken = new MToken(nullptr, "",MTokenType::NUMBER);
                if(negateElements)
                    newNumToken->setValue("-1");
                else
                    newNumToken->setValue("1");

                tokenList.insert(0,new MToken(nullptr, "*", MTokenType::OPERATOR));
                tokenList.insert(0,newNumToken);
            }
            else
            {
                qDebug()<<"Simplification: Part contains unknown / illegal Tokentype";
            }
        }
        else if(tokenList.count()>1)
        {
            //
            if(negateElements && (gType==MFPartType::NUMERIC || gType==MFPartType::NUMERIC_AND_VARIABLE))
            {
                //find first numeric Token and negate it's value
                for(int i=0; i <tokenList.count(); i++)
                {
                    if(tokenList.at(i)->getType()==MTokenType::NUMBER)
                    {
                        double firstValue = 0;
                        bool toDoubleSuccess = false;
                        firstValue = tokenList.at(i)->getValue().toDouble(&toDoubleSuccess);
                        if(toDoubleSuccess)
                        {
                            tokenList.at(i)->setValue(QString::number((firstValue*(-1))));
                        }
                        else
                            qDebug()<<"Simplifier: Handling of Negation: Partvalue could not be converted to double: "<< tokenList.at(i)->getValue();
                    }
                }
            }
        }

        negateElements = false;
        updateType();
    }



}


//checks if two Variables get multiplied (not supported by current softwareversion)
bool MFPart::multiplError()
{
    bool retVal = false;
    if(!tokenList.isEmpty())
    {
        if(tokenList.count()>1)
        {
            bool firstVariableFound = false;
            bool multiplicationFound = false;
            for(int i = 0; i < tokenList.count(); i++)
            {
                if(tokenList.at(i)->getType()==MTokenType::VARIABLE)
                {
                    if(firstVariableFound && multiplicationFound)
                    {
                        // a multiplication of two variables has been detected
                        retVal = true;
                        break;
                        //qDebug()<<"Error part: "<<tokenListToString() <<". Multiplication of two varaibles detected.";
                    }
                    else
                        firstVariableFound = true;
                }
                else if(tokenList.at(i)->getType()==MTokenType::OPERATOR)
                {
                    //find out what kind of operator has been used last
                    //Variable1*Number*Number/Variable2 =>multiplication found = false
                    //Variable1*Number*Number*Variable2 =>multiplication found = true
                    if(tokenList.at(i)->getValue()=="*")
                        multiplicationFound=true;

                    if(tokenList.at(i)->getValue()=="/")
                        multiplicationFound=false;
                }
            }
        }

    }

    return retVal;
}

//checks if there's a division by variable in the equation
bool MFPart::divisionError()
{
    bool retVal = false;
    if(!tokenList.isEmpty())
    {
        if(tokenList.count()>1)
        {
            //bool firstVariableFound = false;
            bool divisionFound = false;
            for(int i = 0; i < tokenList.count(); i++)
            {
                if(tokenList.at(i)->getType()==MTokenType::VARIABLE)
                {
                    if(divisionFound)
                    {
                        // a division with variable has been detected
                        retVal = true;
                        break;
                    }

                }
                else if(tokenList.at(i)->getType()==MTokenType::OPERATOR)
                {
                    //find out what kind of operator has been used last
                    //Variable1*Number*Number/Variable2 =>division found = true
                    //Variable1*Number*Number*Variable2 =>division found = false
                    if(tokenList.at(i)->getValue()=="/")
                        divisionFound=true;

                }
            }
        }
    }

    return retVal;
}

void MFPart::updateType()
{
    if(tokenList.count()>0)
    {
        int numberOfVaraibles=0;
        int numberOfNumValues=0;
        bool unwantedType=false;

        for(int i =0 ; i < tokenList.count(); i++)
        {
            switch(tokenList.at(i)->getType())
            {
            case MTokenType::CONSTANT:
            case MTokenType::NUMBER:
                numberOfNumValues++;
                break;
            case MTokenType::VARIABLE:
                numberOfVaraibles++;
                break;
            case MTokenType::OPERATOR:
                break;
            default:
                unwantedType=true;
                break;
            }

            if(unwantedType)
                break;
        }


        //define type
        if(numberOfNumValues >0 && numberOfVaraibles<=0)
        {
            gType= MFPartType::NUMERIC;
        }
        else if(numberOfNumValues >0 && numberOfVaraibles>0)
        {
            gType = MFPartType::NUMERIC_AND_VARIABLE;
        }
        else if(numberOfNumValues <=0 && numberOfVaraibles>0)
        {
            gType = MFPartType::VARIABLE_ONLY;
        }
        else
            gType = MFPartType::UNDEF;
    }
    else
        gType = MFPartType::UNDEF;
}

//if value could be retrieved returnvalue equals true. Eles it's false
bool MFPart::getNumericValue(double &value)
{
    bool retVal=false;

    updateType();

    if(gType==MFPartType::NUMERIC)
    {
        double firstValue = 0;
        bool toDoubleSuccess = false;
        firstValue = tokenList.at(0)->getValue().toDouble(&toDoubleSuccess);

        if(toDoubleSuccess)
        {
            value = firstValue;
            retVal = true;
        }
        else
            qDebug()<<"Parts: getNumericValue: couldn't convert numeric Value: " << tokenList.at(0)->getValue();
    }
    else if(gType==MFPartType::NUMERIC_AND_VARIABLE)
    {
        for(int i =0; i< tokenList.count(); i++)
        {
            if(tokenList.at(i)->getType()==MTokenType::NUMBER)
            {
                double firstValue = 0;
                bool toDoubleSuccess = false;
                firstValue = tokenList.at(i)->getValue().toDouble(&toDoubleSuccess);

                if(toDoubleSuccess)
                {
                    value = firstValue;
                    retVal = true;
                    break;
                }
                else
                    qDebug()<<"Parts: getNumericValue: couldn't convert numeric Value: " << tokenList.at(i)->getValue();
            }
        }
    }

    return retVal;
}


//returnValue = number of Variables. If Variables get found, the Value (String) of the Last variable will get written into &name
int MFPart::getVariableName(QString &name)
{
    int returnValue = -1;

    if(!tokenList.isEmpty())
    {
        returnValue =0;

        for(int i =0; i<tokenList.count();i++)
        {
            if(tokenList.at(i)->getType()==MTokenType::VARIABLE)
            {
                returnValue++;
                name = tokenList.at(i)->getValue();
            }
        }
    }

    return returnValue;
}


//used in solver -> Coefficient and Variable-Pointer
QPair<double, MVariable*> *MFPart::getVariablePair()
{
    QPair<double, MVariable*> *retVal = nullptr;

    if(gType==MFPartType::NUMERIC )
    {
        //get double Value of number
        double val=-1;
        if(getNumericValue(val))
        {
            retVal = new QPair<double,MVariable*>;
            retVal->first = val;
            retVal->second = nullptr;
        }

    }
    else if(gType==MFPartType::NUMERIC_AND_VARIABLE)
    {
        //
        //get MVariable-Pointer
        for(int i =0; i < tokenList.count(); i++)
        {
            if(tokenList.at(i)->getType()==MTokenType::VARIABLE)
            {
                MVariable *mVal = qobject_cast<MVariable *>(tokenList.at(i)->getMObject());

                if(mVal != nullptr)
                {
                    //get double Value of coeficient
                    double val=-1;
                    if(getNumericValue(val))
                    {
                        retVal = new QPair<double,MVariable*>;
                        retVal->first = val;
                        retVal->second = mVal;
                    }
                }
                break;
            }
        }

    }

    return retVal;
}
