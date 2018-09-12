#include "mathengine.h"

MathEngine::MathEngine(QObject *parent) : QObject(parent)
{
    mLexer = new Lexer(this);
    mParser = new Parser(this);
    mPreSolver = new PreSolver(this);
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

    //connect Engine to Presolver
     QObject::connect(mPreSolver, SIGNAL(sendError(ErrorMessage*)), this, SLOT(recieveError(ErrorMessage*)));      //Handling of Error-Messages

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

    int numberOfUnsolvedFormulas=1;

    while(numberOfUnsolvedFormulas >0)
    {
        //plug in varaible-values of those that have already been solved, ignore solved formulas

        //create List of MFFormulas (solvable Formulas-model) out of the vetted formulaList
        QList<MFFormula *> *mfFormulaList = mPreSolver->getPartitionedFormulasList(formulaList);
        numberOfUnsolvedFormulas=mfFormulaList->count();

        if (numberOfUnsolvedFormulas >0)
        {
            qDebug()<<"Mathengine: simplifing Equations done. Calling solver";
            mSolver->startSolving(mfFormulaList);
        }

    }



    emit sendMathData(formulaList,variableList);
    emit showErrorList();
    emit solverDone();
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



