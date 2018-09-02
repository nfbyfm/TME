/*
 * Main / most important class of the Application. Contains and controls all submodules.
 */

#include "controller.h"





Controller::Controller(QObject *parent) : QObject(parent)
{
    //init main Objects and SubModules
    this->mView = new MainWindow;
    this->mEngine = new MathEngine(this);               //for solving Equations
    this->fHandler = new FaultHandler(this);            //for handling Error-Messages
    this->sHandler = new SettingsHandler(this);         //for handling of Applicationsettings
    this->docHandler = new DocumentHandler(this);       //contains main document

    b_printDocument = false;
    b_printPDF = false;
    b_showPrintPreview = false;

    //create all the connections between views, controllers, models
    connect();

    //load application-settings
    sHandler->loadSettings();

    //start the main GUI
    mView->show();

    //create new, empty file
    mView->createNewFile();
}

void Controller::connect()
{

//Controller ..

    //Controller -> View
    QObject::connect(this, SIGNAL(changeLanguage(QString)), mView, SLOT(changeLanguage(QString)));  //to tell the UI to change the language

    //Controller -> SettingsHandler
    QObject::connect(this, SIGNAL(sshowSettingsDialog(QWidget*)), sHandler, SLOT(showSettingsDialog(QWidget*)));  //show the settings-dialog

    //Controller -> DocumentHandler
    //QObject::connect(this, SIGNAL(sendMathData(QList<MFormula*>,QList<MVariable*>)), docHandler, SLOT(recieveMathData(QList<MFormula*>,QList<MVariable*>)));






//View ...

    //View -> Controller
    QObject::connect(mView, SIGNAL(exitApplication(QStringList *)), this, SLOT(closeApp(QStringList *)));     //close program
    QObject::connect(mView, SIGNAL(languageChanged(QString)), this, SLOT(languageChanged(QString)));  //user has changed the language
    QObject::connect(mView, SIGNAL(showHelpDialog()), this, SLOT(showHelpDialog()));  //show the settings-dialog
    QObject::connect(mView, SIGNAL(showAboutDialog()), this, SLOT(showAboutDialog()));  //show the about-dialog
    QObject::connect(mView, SIGNAL(showSettingsDialog()), this, SLOT(rshowSettingsDialog()));  //show the settings-dialog

    QObject::connect(mView, SIGNAL(printFile(QStringList *)), this, SLOT(printDocument(QStringList *)));
    QObject::connect(mView, SIGNAL(printPDF(QStringList *)), this, SLOT(printPDF(QStringList *)));
    QObject::connect(mView, SIGNAL(showPrintPreview(QStringList *)), this, SLOT(showPrintPreview(QStringList *)));



    //View -> DocumentHandler
    QObject::connect(mView, SIGNAL(newFile(QStringList *)), docHandler, SLOT(newDocument(QStringList *)));
    QObject::connect(mView, SIGNAL(openFile(QStringList *)), docHandler, SLOT(openDocument(QStringList *)));
    QObject::connect(mView, SIGNAL(saveFile(QStringList *)), docHandler, SLOT(saveFile(QStringList *)));
    QObject::connect(mView, SIGNAL(saveFileAs(QStringList *)), docHandler, SLOT(saveFileAs(QStringList *)));

    /*
    QObject::connect(mView, SIGNAL(printFile()), docHandler, SLOT(filePrint()));
    QObject::connect(mView, SIGNAL(printPDF()), docHandler, SLOT(filePrintPdf()));
    QObject::connect(mView, SIGNAL(showPrintPreview()), docHandler, SLOT(filePrintPreview()));
    */




    //QObject::connect(mView, SIGNAL(formulaListUpdated(QStringList*)), docHandler, SLOT(recieveListOfFormulas(QStringList*)));
    //QObject::connect(mView, SIGNAL(variableListUpdated(QStringList*)), docHandler, SLOT(recieveListOfVariables(QStringList*)));

    //View -> FaultHandler
    QObject::connect(mView, SIGNAL(sendErrorMessage(ErrorMessage*)), fHandler, SLOT(addError(ErrorMessage*)));

    //View -> MathEngine
    QObject::connect(mView, SIGNAL(solveMath(QString,bool,QStringList *)), mEngine, SLOT(startSolver(QString,bool,QStringList *)));
    QObject::connect(mView, SIGNAL(solveMath(QStringList *)), mEngine, SLOT(startSolver(QStringList *)));



//DocumentHandler ...

    //DocumentHandler -> View
    QObject::connect(docHandler, SIGNAL(setTextDocument(QTextDocument*)), mView, SLOT(setDocument(QTextDocument*)));
    QObject::connect(docHandler, SIGNAL(updateWindowTitle(QString,bool)), mView, SLOT(setMainWindowTitle(QString,bool)));
    QObject::connect(docHandler, SIGNAL(showStatusMessage(QString,int)), mView, SLOT(showStatusMessage(QString,int)));

    //DocumentHandler -> MathEngine
    QObject::connect(docHandler, SIGNAL(solveMath(QString,bool,QStringList *)), mEngine, SLOT(startSolver(QString,bool,QStringList *)));
    QObject::connect(docHandler, SIGNAL(updateMathModel(MathModel*)), mEngine, SLOT(setMathModel(MathModel*)));

    //DocumentHandler -> faultHandler
    QObject::connect(docHandler, SIGNAL(sendError(ErrorMessage*)), fHandler, SLOT(addError(ErrorMessage*)));





//SettingsHanlder ...

    //SettingsHandler -> DocumentHandler
    QObject::connect(sHandler, SIGNAL(autosaveChanged(bool,double)), docHandler, SLOT(autosaveChanged(bool,double)));
    QObject::connect(sHandler, SIGNAL(showPdfAfterExportChanged(bool)), docHandler, SLOT(showPdfAfterExportChanged(bool)));

    //SettingsHandler -> Controller
    QObject::connect(sHandler, SIGNAL(changeLanguage(QString)), this, SLOT(languageChanged(QString)));

    //SettingsHandler -> View
    QObject::connect(sHandler, SIGNAL(setMainStyleSheet(QString&)), mView, SLOT(changeStyleSheet(QString&)));

    //SettingsHandler -> FaultHandler
    QObject::connect(sHandler, SIGNAL(sendError(ErrorMessage*)), fHandler, SLOT(addError(ErrorMessage*)));




//Math-Engine ...

    //Mathengine -> Controller
    QObject::connect(mEngine, SIGNAL(showErrorList()), this, SLOT(showErrorListDialog()));
    QObject::connect(mEngine, SIGNAL(solverDone()), this, SLOT(recieveSolverDone()));

    //MathEngine -> View
    QObject::connect(mEngine, SIGNAL(sendMathData(QList<MFormula*>,QList<MVariable*>)), mView, SLOT(updateMathData(QList<MFormula*>,QList<MVariable*>)));

    //Mathengine -> FaultHandler
    QObject::connect(mEngine, SIGNAL(sendError(ErrorMessage*)), fHandler, SLOT(addError(ErrorMessage*)));





//FaultHandler ...

    //Faulthandler -> Controller
    QObject::connect(fHandler, SIGNAL(showPopUp(ErrorMessage*)), this, SLOT(showPopUpError(ErrorMessage*)));
    //QObject::connect(fHandler, SIGNAL(showErrListDialog(QList<ErrorMessage*>)), this, SLOT(showErrorListDialog(QList<ErrorMessage*>)));

    //Faulthandler -> View
    QObject::connect(fHandler, SIGNAL(showStatusBarError(QString,int)), mView, SLOT(showStatusMessage(QString,int)));
    QObject::connect(fHandler, SIGNAL(resetMathDisplay()), mView, SLOT(resetMathData()));





}


void Controller::closeApp(QStringList * formulaList)
{
    if(docHandler->documentHasBeenSaved())
    {
        mView->close();
    }
    else
    {
        const QMessageBox::StandardButton ret = QMessageBox::warning(mView, QCoreApplication::applicationName(), tr("The document has been modified.\nDo you want to save your changes?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (ret == QMessageBox::Save)
            docHandler->saveFile(formulaList);
        else
            mView->close();
    }
}



//open a file
void Controller::openFile(QFileInfo fileName)
{
    if(fileName.exists())
    {
        if (fileName.isFile())
        {
            docHandler->openKnownFile(fileName);
            mView->showStatusMessage(tr("Opening file ") + fileName.baseName().toLatin1(),2000);

        }
        else
        {
            //show message that the given argument is not a file
            mView->showStatusMessage(fileName.absolutePath().toLatin1() + tr(" is not a file."),2000);
        }
    }
    else
    {
        //show message that the file does not exist
        mView->showStatusMessage(tr("File does not exist."),2000);
    }
}


//functions for showing various Dialogs
#define DIALOG_CALLS_START {

    void Controller::showPopUpError(ErrorMessage * eMessage)
    {
        QMessageBox messageBox;
        messageBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        //messageBox.setFixedSize(500,200);

        switch(eMessage->getEType() )
        {
            case ErrorType::ET_ERROR:
                 messageBox.critical(mView,tr("Error"),eMessage->getMeassage());
            break;
            case ErrorType::ET_WARNING:
                messageBox.warning(mView,tr("Warning"),eMessage->getMeassage());
                break;
            default:
                messageBox.warning(mView,tr("Warning"),eMessage->getMeassage());
                break;
        }

    }

    void Controller::showAboutDialog()
    {
        QMessageBox messageBox;
        messageBox.setIconPixmap(QPixmap("View/icon.jpg"));
        QString title = tr("about TME");
        QString text = tr("TME is a program with an integrated math-solver \nfor writing scientific / math-heavy documents.");
        messageBox.about(mView,title,text);

    }



    void Controller::showHelpDialog()
    {
        QDesktopServices::openUrl( QUrl(tr("https://github.com/nfbyfm/TME/wiki"), QUrl::TolerantMode));
    }

    void Controller::rshowSettingsDialog()
    {
        emit sshowSettingsDialog(mView);
    }


    void Controller::showErrorListDialog()
    {
        QString retVal;
        bool settingFound;

        sHandler->getSetting(SETTINGS_ID::MATHSOLVER_SHOWERRORLIST,retVal,settingFound);

        if(settingFound && retVal=="true")
        {
            fHandler->showErrorListDialog(mView);
        }
        else
        {
            if(!settingFound)
                qDebug()<<"Show Errorlistdialog called. Setting not found!";

            fHandler->clearErrorList();
        }
    }

#define DIALOG_CALLS_END }



//gets notified by UI-Methods that the language has to be changed -> save change to Settings and emit signal for UI
void Controller::languageChanged(QString language)
{
    sHandler->setSetting(SETTINGS_ID::LANGUAGE, language);
    emit changeLanguage(language);
}


/*
void  Controller::recieveMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList)
{
    emit sendMathData(formulaList,variableList);
    //only temporary!!!
    emit updateMathDataView(formulaList, variableList);
}
*/

void Controller::printDocument(QStringList * formulas)
{
    //start solver first (with suppressed ErrorHandler). When done, call the print-function of the document handler.
    qDebug()<<"Controller: recieved Signal to print Document. Calling solver.";
    b_printDocument = true;
    b_printPDF = false;
    b_showPrintPreview = false;
    fHandler->setSuppressMessages(true);

    mEngine->startSolver("",false,formulas);

}

void Controller::showPrintPreview(QStringList * formulas)
{
    b_printDocument = false;
    b_printPDF = false;
    b_showPrintPreview = true;
    fHandler->setSuppressMessages(true);

    mEngine->startSolver("",false,formulas);

}

void Controller::printPDF(QStringList * formulas)
{
    b_printDocument = false;
    b_printPDF = true;
    b_showPrintPreview = false;
    fHandler->setSuppressMessages(true);

    mEngine->startSolver("",false,formulas);

}

void Controller::recieveSolverDone()
{
    qDebug()<<"Controller: recieved that Math-Engine is done.";

    if(b_printDocument)
    {
        qDebug()<<"Controller: Calling printDocument-function of the Documenthandler.";
        docHandler->filePrint();
    }
    else if(b_printPDF)
    {
        qDebug()<<"Controller: Calling printPDF-function of the Documenthandler.";
        docHandler->filePrintPdf();
    }
    else if(b_showPrintPreview)
    {
        qDebug()<<"Controller: Calling showPrintPreview-function of Documenthandler.";
        docHandler->filePrintPreview();
    }

    fHandler->clearErrorList();
    fHandler->setSuppressMessages(false);

    b_printDocument = false;
    b_printPDF = false;
    b_showPrintPreview = false;
}
