#include "mathengine.h"

MathEngine::MathEngine(QObject *parent) : QObject(parent)
{
    mLexer = new Lexer(this);
    mParser = new Parser(this);
    mSolver = new MSolver(this); //linear Algebra-Solver

    formulasFromText = new QStringList();

    connect();
}

MathEngine::~MathEngine()
{
    formulasFromText->clear();
}

void MathEngine::setMathModel(MathModel *mathModel)
{
    mMathModel = mathModel;
}


void MathEngine::connect()
{
    //Connect Engine to Lexer
    QObject::connect(mLexer, SIGNAL(sendError(ErrorMessage*)), this, SLOT(recieveError(ErrorMessage*)));      //Handling of Error-Messages
    QObject::connect(mLexer, SIGNAL(sendTokenizedFormulas(QList<QList<MToken*> >)), this, SLOT(recieveTokenizedFormulas(QList<QList<MToken*> >)));      //

    //Connect Engine to Parser
    QObject::connect(this, SIGNAL(startParser(QList<QList<MToken*> >)), mParser, SLOT(startParsing(QList<QList<MToken*> >)));     //
    QObject::connect(mParser, SIGNAL(sendError(ErrorMessage*)), this, SLOT(recieveError(ErrorMessage*)));      //Handling of Error-Messages
    QObject::connect(mParser, SIGNAL(sendMathData(QList<MFormula*>,QList<MVariable*>)), this, SLOT(recieveMathDataFromParser(QList<MFormula*>,QList<MVariable*>)));      //

    QObject::connect(mSolver, SIGNAL(sendError(ErrorMessage*)), this, SLOT(recieveError(ErrorMessage*)));
}


/**
 * @brief function for starting the solver. Checks if the text is not null or empty and then starts the lexer.
 *
 * @param text
 */
void MathEngine::startSolver(QString text, bool overwriteExistingFormulas, QStringList *formulasFromModel)
{
    //implement!!! -> use overwriteExistingFormulas-> if true, don't get formulas from documenthandler / overwrite them
    //if false -> get formulas from documenthandler and compare them with the found formulas

    if(mMathModel != nullptr)//check if math-Model has been set
    {

        if(overwriteExistingFormulas)
        {
            //get List of formulas from text
            if(searchFormulas(text))
            {
                //formulas found -> overwrite the ones saved in the model, start lexer
                //mMathModel->resetQStringLists();
                //mMathModel->recieveListOfFormulas(formulasFromText);
                mLexer->start(formulasFromText);
            }
            else
            {
                //no formulas found in the given text -> show errormessage, reset formulas in the model
                emit sendError(new ErrorMessage(nullptr,ERROR_ID::MATHENGINE_NoFormulasFoundInText,nullptr));
                emit solverDone();
                //mMathModel->resetQStringLists();
            }
        }
        else
        {
            //get List of formulas from text
            if(searchFormulas(text))
            {
                //formulas found in text -> compare / merge the ones saved in the model, start lexer with merged List

                //QStringList *formulasFromModel = mMathModel->getFormulasList();
                if(formulasFromModel!=nullptr)
                {
                    if(formulasFromModel->count()>0)
                    {
                        //merge formula-lists and start the solver
                        QStringList *mergedLists = new QStringList();

                        for(int u=0; u<formulasFromText->count();u++)
                            mergedLists->append(formulasFromText->at(u));

                        //qDebug()<<"lists before merging:\nList from Text: " << formulasFromText->join("; ") << "\nList from Model: " << formulasFromModel->join("; ");
                        for(int i =0; i<formulasFromModel->count(); i++)
                        {
                            if(!inList(mergedLists, formulasFromModel->at(i)))
                            {
                                mergedLists->append(formulasFromModel->at(i));
                            }
                        }
                        //qDebug()<<"Lists joined: "<<formulasFromText->join("; ");

                        //mMathModel->resetQStringLists();
                        //mMathModel->recieveListOfFormulas(mergedLists);

                        qDebug()<<"starting lexer with List from Model, merged with the list of the text-formulas.";
                        mLexer->start(mergedLists);
                    }
                    else
                    {
                        //formulas found only in the text -> write them into the model, start the lexer
                        qDebug()<<"Mathengine: Error: formulas found only in the text. Starting Lexer with formulas from text.";
                        mLexer->start(formulasFromText);
                    }
                }
                else
                {
                    qDebug()<<"Mathengine: Error occured: FormulaList from mathModel is null.";
                    emit solverDone();
                }

            }
            else
            {
                //no formulas found in the given text, check if model maybe has some

                //QStringList *formulasFromModel = mMathModel->getFormulasList();
                qDebug()<<"Mathengine: formulaslist from mathmodel: " << formulasFromModel->join((", "));
                if(formulasFromModel!=nullptr)
                {
                    if(formulasFromModel->count()>0)
                    {
                        //no formulas in the given text but some in the model-> show errormessage, solve formulas from Mathmodel
                        qDebug()<<"starting lexer with List from Model. Contents: "<< formulasFromModel->join("; ");
                        mLexer->start(formulasFromModel);
                    }
                    else
                    {
                        //both lists are empty -> show error-list
                        qDebug()<<"Mathengine: Error: No formulas in neither the formulalist of the MathModel nor the given text.";
                        emit sendError(new ErrorMessage(this, ERROR_ID::MATHENGINE_NoFormulasInBothLists, nullptr));
                        emit solverDone();
                    }
                }
                else
                {
                    qDebug()<<"Mathengine: Error occured: FormulaList from mathModel is null.";
                    emit solverDone();
                }

            }
        }

    }
    else
    {
        qDebug()<<"Mathengine: Catastrophic Error occured: Mathmodel has not been set.";
        emit solverDone();
    }
}

//solve without lexing
void MathEngine::startSolver(QStringList *formulasFromModel)
{
    if(mMathModel != nullptr)
    {
        //QStringList *formulasFromModel = mMathModel->getFormulasList();

        if(formulasFromModel!=nullptr)
        {
            if(formulasFromModel->count()>0)
            {
                //start the Lexer
                qDebug()<<"Start Sovler directly: starting lexer with List from Model. Contents: "<< formulasFromModel->join("; ");
                mLexer->start(formulasFromModel);
            }
            else
            {
                qDebug()<<"Mathengine: Error: No formulas in the formulalist of the MathModel." << formulasFromModel->join(", ");
                emit sendError(new ErrorMessage(this, ERROR_ID::MATHENGINE_NoFormulasFoundInMathModel, nullptr));
                emit solverDone();
            }
        }
        else
        {
            qDebug()<<"Mathengine: Error occured: FormulaList from mathModel is null.";
            emit solverDone();
        }
    }
    else
    {
        qDebug()<<"Mathengine: Catastrophic Error occured: Mathmodel has not been set.";
        emit solverDone();
    }
}





void MathEngine::recieveError(ErrorMessage *errmsg)
{
    emit sendError(errmsg);
}

void MathEngine::recieveTokenizedFormulas(QList<QList<MToken *> > tf_list)
{
    emit startParser(tf_list);
}



void MathEngine::recieveMathDataFromParser(QList<MFormula*> formulaList, QList<MVariable*> variableList)
{
    //parser: creates list of formulas and variables
    mMathModel->recieveMathData(formulaList,variableList);

    //plug in varaible-values of those that have already been solved, ignore solved formulas

    //create List of MFFormulas (solvable Formulas-model) out of the vetted formulaList
    QList<MFFormula *> *mfFormulaList = createPartitionedFormulasList(formulaList);

    qDebug()<<"Mathengine: calling simplifyEquations";
    simplifyEquations(mfFormulaList);

    qDebug()<<"Mathengine: simplifing Equations done. Calling solver";

    mSolver->startSolving(mfFormulaList);

    //run simplification and simple solver again
    simplifyUnsolvedEquations(formulaList);

    qDebug()<<"";
    qDebug()<<"after simplifying again:";
    //just for debugging: show list of unsolvable equations again
    for(int i=0; i< formulaList.count(); i++)
    {
        if(formulaList.at(i)->getIsSolved()==false)
            qDebug()<<"unsolved equation: " + formulaList.at(i)->toString();
    }

    emit sendMathData(formulaList,variableList);
    emit showErrorList();
    emit solverDone();
}

//simplify equations
void MathEngine::simplifyEquations(QList<MFFormula *> *mfFormulaList)
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

//simplify unsolved equations
void MathEngine::simplifyUnsolvedEquations(QList<MFormula *> mFormulaList)
{
    if(!mFormulaList.isEmpty())
    {
        qDebug()<<"Solve unsolved formulas";

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



//****************************************************************************************//

                    }
                    else
                    {
                        //if number of unsolved variables equals one, solve the equation
                        qDebug()<<"unsolved equation: " + mFormulaList.at(i)->toString();
                        if(noOfunsolvedVariables==0)
                            mFormulaList.at(i)->setIsSolved(true);
                    }
                }

            }
        }





    }
    else
    {
        qDebug()<<"Error Solver: simplifyEquations: recieved List of Parts-Formulas is empty (nullptr).";
    }
}


/**
 * @brief function for finding formulas in a text
 *
 * @param text
 * @return bool true if at least one formula has been found. False if no formula could be found
 */
bool MathEngine::searchFormulas(QString text)
{
    //use Regular Expression to find formulas inside the text
    //search for different types of notations? e.g. latex and others?

    ErrorMessage *msg = nullptr;

    formulasFromText->clear();

    if(!text.isNull())
    {
        if(!text.isEmpty())
        {
            QRegExp rx("\\\\begin\\{equation\\}(.*)\\\\end\\{equation\\}");
            rx.setMinimal(true);

            int pos = 0;

            while ((pos = rx.indexIn(text, pos)) != -1)
            {
                //list << rx.cap(1);
                //qDebug() << pos << ": |" << rx.cap(1) <<"|";
                QString newFormula = replaceEscapeSequences(rx.cap(1));
                newFormula = newFormula.replace(" ","");
                if(!formulasFromText->contains(newFormula))
                {
                    formulasFromText->append(newFormula);
                    //qDebug()<<"Formula: '" << newFormula <<"' added to list.";
                }

                pos += rx.matchedLength();
            }

            QRegExp rx2("\\$(.*)\\$");
            rx2.setMinimal(true);
            pos = 0;
            while ((pos = rx2.indexIn(text, pos)) != -1)
            {
                //qDebug() << pos << ": |" << rx2.cap(1) <<"|";
                QString newFormula =replaceEscapeSequences(rx2.cap(1));
                newFormula = newFormula.replace(" ","");

                //filter possible Formulas disguised as links
                if(!newFormula.contains("link("))
                {
                    if(!formulasFromText->contains(newFormula) )
                    {
                        formulasFromText->append(newFormula);
                        //qDebug()<<"Formula: '" << newFormula <<"' ";
                    }
                }
                else
                {
                    qDebug()<<"link found:" << newFormula;
                }

                pos += rx2.matchedLength();
            }
        }
        else
            msg = new ErrorMessage(nullptr,ERROR_ID::MATHENGINE_TextIsEmpty,nullptr);
    }
    else
        msg = new ErrorMessage(nullptr,ERROR_ID::MATHENGINE_TextIsNull,nullptr);


    //show Error-Messages (in Statusbar)
    if(msg != nullptr)
    {
        emit sendError(msg);
    }




    return (formulasFromText->count()>0);
}

QString MathEngine::replaceEscapeSequences(QString formula)
{
    QStringList escapeSeq = {"\n","\t", "\v", "\b", "\r", "\f"};


    for(int i = 0; i < escapeSeq.size();i++)
    {
        formula = formula.remove(escapeSeq.at(i));
    }

    return formula;
}

//check if one formula is in the list (caseinsensitive, escapesequences and spaces removed)
bool MathEngine::inList(QStringList *list, QString value)
{
    bool result = false;

    QString listitem = "";
    QString tempVal = value;
    tempVal = replaceEscapeSequences(tempVal).remove(" ").toLower();

    for(int i = 0; i< list->count(); i++)
    {
        listitem = replaceEscapeSequences(list->at(i)).remove(" ");
        if(listitem.toLower() == tempVal)
        {
            result = true;
            break;
        }
    }

    return result;
}




QList<MFFormula *> *MathEngine::createPartitionedFormulasList(QList <MFormula *> f_List)
{
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
    return partitionedFormulaList;
}

//replaces a Constant-Token with a Number-Token
MToken * MathEngine::constantTokenToNumeric(QString constValue)
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
MToken * MathEngine::variableTokenNumeric(MToken* tokenPointer)
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
 void MathEngine::numberTokenReciproque(MToken* tokenPointer, MFPart *tmpPart)
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
                        qDebug()<<"Parser: division by Number detected. turned into multiplication." << tmpPart->tokenListToString();
                    }
                    else
                        qDebug()<<"Parser: division by Number detected. could not turn into mulitplication.";

                }

        tmpPart->appendTokenList(newElement);
        qDebug()<<"Parser: numberTokenReciproque: " << tmpPart->tokenListToString();

    }
}
