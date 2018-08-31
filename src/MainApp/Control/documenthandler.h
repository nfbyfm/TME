#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <QObject>
#include <QFileDialog>
#include <QTextCodec>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocumentWriter>
#include <QMessageBox>
#include <QCoreApplication>
#include <QPrintPreviewDialog>
#include <QTimer>
#include <QMimeDatabase>
#include <QMimeType>
#include <QXmlStreamReader>

#include <Model/Math/mathmodel.h>
#include <Control/FaultHandler/errormessage.h>

/**
 * @brief calss for handling all the documents
 *
 */
class DocumentHandler : public QObject
{
    Q_OBJECT
private:
    //Mainmodel not needed for the first release (would consist out of these two
    /**
     * @brief main models
     * QTextDocument get used by the Mainwindow
     * mModel gets also used by the Math-Engine
     * @{
     */
    MathModel *mModel;
    QTextDocument *tDocument;
    /** @} */

    /**
     * @brief similar to tDocument, neede for printing
     * $link(... ,...)$ get replaced with actual values
     */
    QTextDocument *documentForPrint;//same document as above but with rendered / replaced formulas


    /**
     * @brief current filename
     *
     */
    QString fileName;

    /**
     * @brief variables for the autosave-function
     * @{
     */
    QTimer *autoSaveTimer;
    bool autoSaveIsEnabled;
    /** @}*/

    /**
     * @brief main fucntions for saving and opening files
     * @{
     */
    void loadFile(QString fName);
    void loadProjectFile(QString fName);
    bool saveProjectFile(QStringList * formulaList);

    bool maybeSave(QStringList * formulaList);
    void setCurrentFileName(const QString &fiName);
    /** @}*/


    /**
     * @brief create documentForPrint / take tDocument and replace all '$link(...,...)$'-Commands in the Text with rendered / solved Equations / Variables
     *
     */
    void createPrintDocument();

    QString formulaToStringWithPluggedInValues(MFormula *formula);
public:
    explicit DocumentHandler(QObject *parent = nullptr);

    /**
     * @brief for checking if the document has been saved yet or not
     *
     */
    bool documentHasBeenSaved();

    /**
     * @brief helper-function for getting the xml-version of a project file
     *
     */
    static inline QString versionAttribute() { return QStringLiteral("version"); }

    /**
     * @brief function that gets called by main.cpp -> directly open file without showing a dialog
     *
     */
    void openKnownFile(QFileInfo fileName);

signals:
    /**
     * @brief function for sending errormessages
     *
     */
    void sendError(ErrorMessage *errmsg);

    /**
     * @brief function for setting the document
     * connected to the view / MainWindow
     *
     */
    void setTextDocument(QTextDocument *doc);

    /**
     * @brief function for starting the math-solver
     *
     */
    void solveMath(QString formulas, bool overwriteExistingFormulas, QStringList *formulaList);

    /**
     * @brief function for updating the MainWindow-Title
     *
     */
    void updateWindowTitle(QString filename, bool fileModified);

    /**
     * @brief function for showing a statusbar message in the MainWindow
     *
     */
    void showStatusMessage(QString message, int timeoutMS=1000);          //show a message in the statusBar

    /**
     * @brief function for updating the MathModel of the Mathengine
     *
     */
    void updateMathModel(MathModel * model);

    /**
     * @brief calling save-function of the Mainwindow /GUI
     *
     */
    void saveFileViaView();

public slots:
    /**
     * @brief core functions for opening and saving files
     * @{
     */
    void openDocument(QStringList *formulaList);
    void newDocument(QStringList * formulaList);

    bool saveFile(QStringList *formulaList);
    bool saveFileAs(QStringList * formulaList);
    /** @}*/

    /*
    void filePrint(QStringList *formulaList);
    void filePrintPreview(QStringList *formulaList);
    void filePrintPdf(QStringList *formulaList);
    */

    /**
     * @brief core function for printing a document
     * @{
     */
    void filePrint();
    void filePrintPreview();
    void filePrintPdf();
    /** @}*/

    /**
     * @brief method for recieving updated autosave-Options
     * connect to settingshandler
     */
    void autosaveChanged(bool enabled, double timeout);

    //void recieveMathData(QList<MFormula*> fList, QList<MVariable*> vList);

    /**
     * @brief function for recieving errormessages from submodules
     *
     */
    void recieveError(ErrorMessage *errmsg);

    //void recieveListOfFormulas(QStringList *formList);
    //void recieveListOfVariables(QStringList *variaList);

private slots:
    /**
     * @brief function for showing the printpreview
     *
     */
    void printPreview(QPrinter *);

    /**
     * @brief function for telling if the document has changed or not
     *
     */
    void documentChanged();

    /**
     * @brief autosave-function
     *
     */
    void autoSave();
};

#endif // DOCUMENTHANDLER_H
