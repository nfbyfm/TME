#ifndef FAULTHANDLER_H
#define FAULTHANDLER_H

#include <QObject>
#include <QDebug>
#include <Control/FaultHandler/errormessage.h>
#include <QMetaEnum>
#include <View/Dialogs/errorlistdialog.h>


/**
 * @brief Class for handling of all Errormessages.
 * In order for a message to be processed the slot 'addError' or 'showErrorListDialog' has to be used *
 */
class FaultHandler : public QObject
{
    Q_OBJECT

private:
    //Variables
    /**
     * @brief List of Errormessages for the ErrorListDialog
     *
     */
    QList <ErrorMessage *> listOfErrMSG;

    /**
     * @brief Maps for determining the properties of an errormessage
     *@{
     */
    QMap <ERROR_ID, QString> errStrMap;
    QMap <ERROR_ID, ErrorViewMedium> errMediumMap;
    QMap <ERROR_ID, ErrorType> errTypeMap;
    /** @}*/

    /**
     * @brief used to supress / ignore Warnings
     *
     */
    bool suppressMessages;

    //functions
    /**
     * @brief for initializing the maps needed for setting Errormessageporperties
     *
     */
    void initMaps();

    /**
     * @brief function for setting the properties of a recieved Errormessage
     *
     */
    void setErrorProperties(ErrorMessage * errorMsg);

public:
    explicit FaultHandler(QObject *parent = nullptr);
    ~FaultHandler();

    /**
     * @brief method for supressing error-messages. Used by the main controller when calling the math-engine when printing a file (messages from mathsolver are not supposed to be shown during that time).
     *
     */
    void setSuppressMessages(bool value);

signals:
    /**
     * @brief function for showing a Pop-Message
     *
     */
    void showPopUp(ErrorMessage *eMessage);

    /**
     * @brief function for show a message in the statusbar of the main window
     *
     */
    void showStatusBarError(QString message, int timeout);

    void changeLanguage(QString language);

    /**
     * @brief function for clearing the math-display of the main window
     * gets triggered if the errormessage that says that there are no formulasto be displayed gets called
     */
    void resetMathDisplay();

public slots:
    /**
     * @brief primary slot for recieving Errormessages from other modules
     *
     */
    void addError(ErrorMessage *errorMessage);

    /**
     * @brief slot for recieving errormessages that shal be shown in a errorlistdialog
     *
     */
    void showErrorListDialog(QWidget *parentview);

    /**
     * @brief slot that clears all errormessages meant for display in the errorlistdialog
     *
     */
    void clearErrorList();

};

#endif // FAULTHANDLER_H
