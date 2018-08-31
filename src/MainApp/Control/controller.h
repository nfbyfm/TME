#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QSettings>
#include <QFileDialog>
#include <QErrorMessage>
#include <QDebug>

#include <View/mainwindow.h>
#include <View/Dialogs/errorlistdialog.h>

#include <Control/MathEngine/mathengine.h>
#include <Control/FaultHandler/faulthandler.h>
#include <Control/documenthandler.h>
#include <Control/settingshandler.h>

#include <Model/mainmodel.h>

/**
 * @brief Main Controller. Contains views, models and submodules (Math-Engine, View-Controller, ...).
 * Most important class of the whole program. Contains all, controlls all.
 */
class Controller : public QObject
{
    Q_OBJECT

private:
    MainWindow *mView; /**< Main View */

    DocumentHandler *docHandler;    /**< Document-Handler, contains the Main-Document */

    MathEngine *mEngine;    /**< Math-Engine */
    FaultHandler *fHandler; /**< Main Faulthandler */
    SettingsHandler *sHandler;  /**< Main Settings-Handler */

    /**
     * @brief helper-variables for remembering if a document is suppossed to be printed
     * in order to print the solver has to be called first. once he is done / the solverDone-signal
     * gets emitted a check-function looks at these three variables and triggers the print-function if one of them is set to true
     * @{
     */
    bool b_printDocument;
    bool b_showPrintPreview;
    bool b_printPDF;
    /** @}*/

    void connect(); /**< function for connecting views, controllers and so on */

public:
    /**
     * @brief constructor
     *
     * @param parent
     */
    explicit Controller(QObject *parent = nullptr);



signals:
    /**
     * @brief function that call methods of the view / MainWindow
     *
     */
    void showStatusBarMessage(QString message);
    void changeLanguage(QString language);
    void sshowSettingsDialog(QWidget *parentView);
    /** @}*/

    /**
     * @brief function for redirecting Math-Data
     *
     */
    void sendMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList);
    //void updateMathDataView(QList<MFormula*> formulaList, QList<MVariable*> variableList);

public slots:

    /**
     * @brief open file by filename
     *
     * @param fileName
     */
    void openFile(QFileInfo fileName);                  //open file by filename

    /**
     * @brief print-file functions
     * solver gets called first. when done methods of the documenthandler get called
     * @{
     */
    void printDocument(QStringList * formulas);
    void showPrintPreview(QStringList * formulas);
    void printPDF(QStringList * formulas);
    /** @} */

    /**
     * @brief slot for recieving the Done-signal of the Math-Engine
     * checks print-varaibles and triggers fucntions of the documenthandler accordingly
     */
    void recieveSolverDone();

    /**
     * @brief close Application
     *
     */
    void closeApp(QStringList *formulaList);

    /**
     * @brief method for showing a error-message Popup
     * gets called by the faulthandler
     */
    void showPopUpError(ErrorMessage *eMessage);

    /**
     * @brief method for displaying a errorlistdialog
     *
     */
    void showErrorListDialog();

    /**
     * @brief method for changing language of application
     * gets called by the settingshandler
     */
    void languageChanged(QString language);

    /**
     * @brief method for showing the about-dialog
     *
     */
    void showAboutDialog();

    /**
     * @brief mehtod for triggering the help-function
     *
     */
    void showHelpDialog();

    /**
     * @brief function for showing the settings-dialog
     *
     */
    void rshowSettingsDialog();

    //void recieveMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList);
};

#endif // CONTROLLER_H
