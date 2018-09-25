#include "faulthandler.h"

/**
 * @brief Constructor for the Faulthandler
 *
 * @param parent
 */
FaultHandler::FaultHandler(QObject *parent) : QObject(parent)
{
    //init maps for Errormessages
    listOfErrMSG.clear();
    suppressMessages = false;
    initMaps();
}


FaultHandler::~FaultHandler()
{
    qDeleteAll(listOfErrMSG);
    listOfErrMSG.clear();

    //qDeleteAll(errMediumMap); //only neede whe contains pointers
    errMediumMap.clear();

    //qDeleteAll(errStrMap);
    errStrMap.clear();

    //qDeleteAll(errTypeMap);
    errTypeMap.clear();
}

void FaultHandler::addError(ErrorMessage *errorMessage)
{
    //since the sender of the errormessage has to only give the ERROR_ID, the actual Message, how it should be displayed and so on, have to be set first
    setErrorProperties(errorMessage);


    switch(errorMessage->getEMedium())
    {
        case ErrorViewMedium::MSG_POPUP:
            emit showPopUp(errorMessage);
            break;
        case ErrorViewMedium::MSG_STATUSBAR:
            emit showStatusBarError(errorMessage->getMeassage(), 2000);
            break;
        case ErrorViewMedium::MSG_LISTDIALOG:
            //add Message to list until another slot gets called
            listOfErrMSG.append(errorMessage);
            break;
        default:

            ErrorMessage *errMsg = new ErrorMessage(nullptr,ERROR_ID::FAULTHANDLER_UnknownError,nullptr);
            setErrorProperties(errMsg);
            emit showPopUp(errMsg);
            break;
    }


    //in case of certain errors, reset UI-Elements
    ERROR_ID tmpErrID = errorMessage->getErrID();

    //Mathengine: reset UI-Elements if no formulas could be found
    if(tmpErrID==ERROR_ID::LEXER_NoFormulasFound || tmpErrID==ERROR_ID::MATHENGINE_TextIsEmpty || tmpErrID==ERROR_ID::MATHENGINE_TextIsNull)
    {
        emit resetMathDisplay();
    }

}


void FaultHandler::showErrorListDialog(QWidget *parentview)
{

    //show whole Dialog with Errorlist (if List is empty do nothing)
    if(listOfErrMSG.size()>0 && suppressMessages==false)
    {
        //shopw Dialog
        qDebug() << "calling Errorlistdialog";



        ErrorListDialog *dialog = new ErrorListDialog(parentview);
        dialog->setTitle(tr("Errorlist Mathsolver"));
        dialog->setErrorMessages(this->listOfErrMSG);
        dialog->setModal(true);
        int dialogCode = dialog->exec();

        if(dialogCode == QDialog::Accepted || dialogCode == QDialog::Rejected)
        {
            qDebug() << "closed the errorlist-dialog";
            listOfErrMSG.clear();
        }

    }
    else
    {
        //do nothing
        if(suppressMessages==true)
            qDebug()<<"FaultHandler: showErrorList called but Showing Messages is suppressed.";
        else
            qDebug()<<"FaultHandler: showErrorList called but there are no messages to show.";
    }

}




void FaultHandler::clearErrorList()
{
    //clear List
    listOfErrMSG.clear();
    qDebug()<<"Faulthandler: Errormessages for list dialog have been cleared.";
}


void FaultHandler::setErrorProperties(ErrorMessage * errorMsg)
{
    ERROR_ID tmpErrID = errorMsg->getErrID();

    //set properties of the Error-Message according to the QMaps
    QString msg = tr("unknown error");
    ErrorViewMedium errViewMedium = ErrorViewMedium::NONE;
    ErrorType errType = ErrorType::ET_NONE;

    if(errStrMap.contains(tmpErrID))
        msg = errStrMap.value(tmpErrID);

    if(errMediumMap.contains(tmpErrID))
        errViewMedium = errMediumMap.value(tmpErrID);

    if(errTypeMap.contains(tmpErrID))
        errType = errTypeMap.value(tmpErrID);

    if(msg.contains("%1"))
    {
        MetaError *err = qobject_cast<MetaError*>(errorMsg->getMetaInfoObject());

        if(err)
        {
            QStringList *errArg = err->getErrorList();
            if(errArg->size()>=3 && msg.contains("%2") && msg.contains("%3"))
            {
                msg = msg.arg(errArg->at(0)).arg(errArg->at(1)).arg(errArg->at(2));
            }
            else
            {
                if(errArg->size()>=2 && msg.contains("%2"))
                {
                    msg = msg.arg(errArg->at(0)).arg(errArg->at(1));
                }
                else
                {
                    if(errArg->size()>=1)
                    {
                        msg = msg.arg(errArg->at(0));
                    }
                }
            }
        }
    }


    errorMsg->setProperties(msg,errViewMedium,errType);
}



void FaultHandler::setSuppressMessages(bool value)
{
    suppressMessages = value;
    QString boolText = value ? "true" : "false";
    qDebug()<<"FaultHandler: setSuppressMessages has been set to: " + boolText;
}

//link Enum-Items of ERROR_ID with the Error-Text
void FaultHandler::initMaps()
{

    this->errStrMap.clear();
    this->errMediumMap.clear();
    this->errTypeMap.clear();

//Faulthandler
    this->errStrMap.insert(ERROR_ID::FAULTHANDLER_UnknownError, tr("Error of unknown type has been triggered."));
    this->errMediumMap.insert(ERROR_ID::FAULTHANDLER_UnknownError, ErrorViewMedium::MSG_POPUP);
    this->errTypeMap.insert(ERROR_ID::FAULTHANDLER_UnknownError, ErrorType::ET_ERROR);

//Mathengine
    this->errStrMap.insert(ERROR_ID::MATHENGINE_TextIsNull, tr("Mathengine: given text for formula-search is null."));
    this->errMediumMap.insert(ERROR_ID::MATHENGINE_TextIsNull, ErrorViewMedium::MSG_STATUSBAR);
    this->errTypeMap.insert(ERROR_ID::MATHENGINE_TextIsNull, ErrorType::ET_WARNING);

    this->errStrMap.insert(ERROR_ID::MATHENGINE_TextIsEmpty, tr("Mathengine: given text for formula-search is empty."));
    this->errMediumMap.insert(ERROR_ID::MATHENGINE_TextIsEmpty, ErrorViewMedium::MSG_STATUSBAR);
    this->errTypeMap.insert(ERROR_ID::MATHENGINE_TextIsEmpty, ErrorType::ET_WARNING);

    this->errStrMap.insert(ERROR_ID::MATHENGINE_NoFormulasFoundInMathModel, tr("No formulas could be found in the current list."));
    this->errMediumMap.insert(ERROR_ID::MATHENGINE_NoFormulasFoundInMathModel, ErrorViewMedium::MSG_STATUSBAR);
    this->errTypeMap.insert(ERROR_ID::MATHENGINE_NoFormulasFoundInMathModel, ErrorType::ET_NONE);

    this->errStrMap.insert(ERROR_ID::MATHENGINE_NoFormulasFoundInText, tr("No formulas could be found in the given text."));
    this->errMediumMap.insert(ERROR_ID::MATHENGINE_NoFormulasFoundInText, ErrorViewMedium::MSG_STATUSBAR);
    this->errTypeMap.insert(ERROR_ID::MATHENGINE_NoFormulasFoundInText, ErrorType::ET_NONE);

    this->errStrMap.insert(ERROR_ID::MATHENGINE_NoFormulasInBothLists, tr("No formulas could be found in the given text or current list."));
    this->errMediumMap.insert(ERROR_ID::MATHENGINE_NoFormulasInBothLists, ErrorViewMedium::MSG_STATUSBAR);
    this->errTypeMap.insert(ERROR_ID::MATHENGINE_NoFormulasInBothLists, ErrorType::ET_NONE);

    this->errStrMap.insert(ERROR_ID::MATHENGINE_NoVariableInForumla, tr("No variable in formula after simplification."));
    this->errMediumMap.insert(ERROR_ID::MATHENGINE_NoVariableInForumla, ErrorViewMedium::MSG_LISTDIALOG);
    this->errTypeMap.insert(ERROR_ID::MATHENGINE_NoVariableInForumla, ErrorType::ET_WARNING);


    this->errStrMap.insert(ERROR_ID::MATHSOLVER_TooManyEquations, tr("Mathsolver: There are not enough variables for the amount of solvable equations (over-defined)."));
    this->errMediumMap.insert(ERROR_ID::MATHSOLVER_TooManyEquations, ErrorViewMedium::MSG_POPUP);
    this->errTypeMap.insert(ERROR_ID::MATHSOLVER_TooManyEquations, ErrorType::ET_WARNING);

    this->errStrMap.insert(ERROR_ID::MATHSOLVER_NotEnoughEquations, tr("Mathsolver: There are not enough equations for the amount of variables (under-defined)."));
    this->errMediumMap.insert(ERROR_ID::MATHSOLVER_NotEnoughEquations, ErrorViewMedium::MSG_POPUP);
    this->errTypeMap.insert(ERROR_ID::MATHSOLVER_NotEnoughEquations, ErrorType::ET_WARNING);





//Mathengine: Lexer
    this->errStrMap.insert(ERROR_ID::LEXER_NoFormulasFound, tr("No formulas found in current text."));
    this->errMediumMap.insert(ERROR_ID::LEXER_NoFormulasFound, ErrorViewMedium::MSG_POPUP);
    this->errTypeMap.insert(ERROR_ID::LEXER_NoFormulasFound, ErrorType::ET_WARNING);


//Mathengine: Parser
    this->errStrMap.insert(ERROR_ID::PARSER_ContainsFunctions, tr("Formula contains function (not supported in this version)."));
    this->errMediumMap.insert(ERROR_ID::PARSER_ContainsFunctions, ErrorViewMedium::MSG_LISTDIALOG);
    this->errTypeMap.insert(ERROR_ID::PARSER_ContainsFunctions, ErrorType::ET_WARNING);

    this->errStrMap.insert(ERROR_ID::PARSER_TooManyComparators, tr("Formula contains multiple comparators (not supported in this version)."));
    this->errMediumMap.insert(ERROR_ID::PARSER_TooManyComparators, ErrorViewMedium::MSG_LISTDIALOG);
    this->errTypeMap.insert(ERROR_ID::PARSER_TooManyComparators, ErrorType::ET_WARNING);

    this->errStrMap.insert(ERROR_ID::PARSER_ComparatorNotSupported, tr("Formula contains prohibited comparator (not supported in this version)."));
    this->errMediumMap.insert(ERROR_ID::PARSER_ComparatorNotSupported, ErrorViewMedium::MSG_LISTDIALOG);
    this->errTypeMap.insert(ERROR_ID::PARSER_ComparatorNotSupported, ErrorType::ET_WARNING);

    this->errStrMap.insert(ERROR_ID::PARSER_NoComparatorInEquation, tr("No comparator in formula found."));
    this->errMediumMap.insert(ERROR_ID::PARSER_NoComparatorInEquation, ErrorViewMedium::MSG_LISTDIALOG);
    this->errTypeMap.insert(ERROR_ID::PARSER_NoComparatorInEquation, ErrorType::ET_WARNING);

    this->errStrMap.insert(ERROR_ID::PARSER_Contains_Brackets, tr("Usage of brackets not supported yet."));
    this->errMediumMap.insert(ERROR_ID::PARSER_Contains_Brackets, ErrorViewMedium::MSG_LISTDIALOG);
    this->errTypeMap.insert(ERROR_ID::PARSER_Contains_Brackets, ErrorType::ET_WARNING);

    this->errStrMap.insert(ERROR_ID::PARSER_ContainsPowerFunction, tr("Powerfunction not supported yet."));
    this->errMediumMap.insert(ERROR_ID::PARSER_ContainsPowerFunction, ErrorViewMedium::MSG_LISTDIALOG);
    this->errTypeMap.insert(ERROR_ID::PARSER_ContainsPowerFunction, ErrorType::ET_WARNING);


    this->errStrMap.insert(ERROR_ID::PARSER_NoVariableFound, tr("No varialbe found in formula."));
    this->errMediumMap.insert(ERROR_ID::PARSER_NoVariableFound, ErrorViewMedium::MSG_LISTDIALOG);
    this->errTypeMap.insert(ERROR_ID::PARSER_NoVariableFound, ErrorType::ET_WARNING);




//SettingsHandler
    this->errStrMap.insert(ERROR_ID::SETTINGS_SettingNotFound, tr("Setting %1 could not be found."));
    this->errMediumMap.insert(ERROR_ID::SETTINGS_SettingNotFound, ErrorViewMedium::MSG_STATUSBAR);
    this->errTypeMap.insert(ERROR_ID::SETTINGS_SettingNotFound, ErrorType::ET_WARNING);

    this->errStrMap.insert(ERROR_ID::SETTINGS_StylesheetNotFound, tr("Stylesheet '%1' could not be found."));
    this->errMediumMap.insert(ERROR_ID::SETTINGS_StylesheetNotFound, ErrorViewMedium::MSG_POPUP);
    this->errTypeMap.insert(ERROR_ID::SETTINGS_StylesheetNotFound, ErrorType::ET_ERROR);


//DocumentHandler
    this->errStrMap.insert(ERROR_ID::DOCHANDLER_FileCanNotBeOpened, tr("File '%1' could not be opened. Permission denied."));
    this->errMediumMap.insert(ERROR_ID::DOCHANDLER_FileCanNotBeOpened, ErrorViewMedium::MSG_POPUP);
    this->errTypeMap.insert(ERROR_ID::DOCHANDLER_FileCanNotBeOpened, ErrorType::ET_ERROR);

    this->errStrMap.insert(ERROR_ID::DOCHANDLER_FileDoesNotExist, tr("File '%1' doen't exist."));
    this->errMediumMap.insert(ERROR_ID::DOCHANDLER_FileDoesNotExist, ErrorViewMedium::MSG_POPUP);
    this->errTypeMap.insert(ERROR_ID::DOCHANDLER_FileDoesNotExist, ErrorType::ET_ERROR);

    this->errStrMap.insert(ERROR_ID::DOCHANDLER_FileAlreadyOpen, tr("File is already open."));
    this->errMediumMap.insert(ERROR_ID::DOCHANDLER_FileAlreadyOpen, ErrorViewMedium::MSG_STATUSBAR);
    this->errTypeMap.insert(ERROR_ID::DOCHANDLER_FileAlreadyOpen, ErrorType::ET_WARNING);

    this->errStrMap.insert(ERROR_ID::DOCHANDLER_CouldNotSaveFile, tr("Could not save file '%1'. Permission denied."));
    this->errMediumMap.insert(ERROR_ID::DOCHANDLER_CouldNotSaveFile, ErrorViewMedium::MSG_POPUP);
    this->errTypeMap.insert(ERROR_ID::DOCHANDLER_CouldNotSaveFile, ErrorType::ET_ERROR);

    this->errStrMap.insert(ERROR_ID::DOCHANDLER_WrongXMLVersion, tr("XML-Version isn't correct (Needed: %1)."));
    this->errMediumMap.insert(ERROR_ID::DOCHANDLER_WrongXMLVersion, ErrorViewMedium::MSG_POPUP);
    this->errTypeMap.insert(ERROR_ID::DOCHANDLER_WrongXMLVersion, ErrorType::ET_ERROR);

    this->errStrMap.insert(ERROR_ID::DOCHANDLER_XMLError, tr("XML-Error: %1"));
    this->errMediumMap.insert(ERROR_ID::DOCHANDLER_XMLError, ErrorViewMedium::MSG_POPUP);
    this->errTypeMap.insert(ERROR_ID::DOCHANDLER_XMLError, ErrorType::ET_ERROR);

    this->errStrMap.insert(ERROR_ID::DOCHANDLER_FileError, tr("File-Error: %1"));
    this->errMediumMap.insert(ERROR_ID::DOCHANDLER_FileError, ErrorViewMedium::MSG_POPUP);
    this->errTypeMap.insert(ERROR_ID::DOCHANDLER_FileError, ErrorType::ET_ERROR);




//MathInput (part of the GUI / View)
    this->errStrMap.insert(ERROR_ID::MATHINPUT_FormulaAlreadyInList, tr("Formula '%1' is already in List."));
    this->errMediumMap.insert(ERROR_ID::MATHINPUT_FormulaAlreadyInList, ErrorViewMedium::MSG_STATUSBAR);
    this->errTypeMap.insert(ERROR_ID::MATHINPUT_FormulaAlreadyInList, ErrorType::ET_WARNING);

    this->errStrMap.insert(ERROR_ID::MATHINPUT_VariableAlreadyInList, tr("Variable '%1' is already in List."));
    this->errMediumMap.insert(ERROR_ID::MATHINPUT_VariableAlreadyInList, ErrorViewMedium::MSG_STATUSBAR);
    this->errTypeMap.insert(ERROR_ID::MATHINPUT_VariableAlreadyInList, ErrorType::ET_WARNING);

    this->errStrMap.insert(ERROR_ID::MATHINPUT_NoFormulaSelected, tr("No Formula has been selected."));
    this->errMediumMap.insert(ERROR_ID::MATHINPUT_NoFormulaSelected, ErrorViewMedium::MSG_STATUSBAR);
    this->errTypeMap.insert(ERROR_ID::MATHINPUT_NoFormulaSelected, ErrorType::ET_NONE);

    this->errStrMap.insert(ERROR_ID::MATHINPUT_NoVariableSelected, tr("No Variable has been selected."));
    this->errMediumMap.insert(ERROR_ID::MATHINPUT_NoVariableSelected, ErrorViewMedium::MSG_STATUSBAR);
    this->errTypeMap.insert(ERROR_ID::MATHINPUT_NoVariableSelected, ErrorType::ET_NONE);



    /*
    this->errStrMap.insert(ERROR_ID::, tr(""));
    this->errMediumMap.insert(ERROR_ID::, ErrorViewMedium::);
    this->errTypeMap.insert(ERROR_ID::, ErrorType::);
    */
}



