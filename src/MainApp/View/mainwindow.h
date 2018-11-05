#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QCloseEvent>
#include <QFileInfo>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QTranslator>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QList>
#include <QFontDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QFontComboBox>
#include <QAction>
#include <QTextCharFormat>
#include <QColorDialog>
#include <QClipboard>
#include <QTextList>
#include <QTextDocumentFragment>
#include <QImageReader>
#include <QPair>

#include <Model/Math/mvariable.h>
#include <View/UI-Elements/PagesTextEdit.h>
#include <View/UI-Elements/imageform.h>
#include <View/UI-Elements/mathform.h>
#include <View/Dialogs/finddialog.h>
#include <View/Dialogs/tabledialog.h>

namespace Ui
{
    class MainWindow;
}

/**
 * @brief class of the main Window
 * @details Class for the main Window. Displays documents, contains most of the GUI-functions.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief constructor
     *
     * @param parent-Widget, usually null
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */
    ~MainWindow();

signals:
    /**
     * @brief user wants to close the application
     *
     */
    void exitApplication(QStringList * listOfFormulas);


    /**
     * @brief gets emitted when the user changes the language
     *
     */
    void languageChanged(QString newLanguage);

    /**
     * @brief calls the math-solver, which searches for formulas in the current text and solves them
     *
     * @param mainText
     */
    void solveMath(QString text, bool overwriteExistingFormulas, QStringList * listOfFormulas);

    /**
     * @brief calls the math-solver. No detection of formulas from text, uses just the ones that are in the MathModel-Lists.
     *
     */
    void solveMath(QStringList * listOfFormulas);

    /**
     * @brief show the about-dialog
     *
     */
    void showAboutDialog();

    /**
     * @brief show the settings-dialog
     *
     */
    void showSettingsDialog();

    /**
     * @brief function for showing the Help / calling the wikipage
     *
     */
    void showHelpDialog();

    /**
     * @brief function for closing the current document
     *
     */
    void closeCurrentDocument();


    /**
     * @brief function creating a new file
     *
     */
    void newFile(QStringList *formulaList);

    /**
     * @brief function for opening a file
     *
     */
    void openFile(QStringList *formulaList);

    /**
     * @brief function for saving a file
     *
     */
    void saveFile(QStringList *formulaList);

    /**
     * @brief function for saving faile under another name or types
     *
     */
    void saveFileAs(QStringList *formulaList);

    /**
     * @brief print-function
     *
     */
    void printFile(QStringList *formulaList);

    /**
     * @brief print-function
     *
     */
    void printPDF(QStringList *formulaList);

    /**
     * @brief print-function
     *
     */
    void showPrintPreview(QStringList *formulaList);

    /**
     * @brief function for sending an errormessage
     * (connected to fualthandler)
     */
    void sendErrorMessage(ErrorMessage *message);

    /**
     * @brief signal to show the document properties-dialog
     *
     */
    void showDocumentProperties();

public slots:


    /**
     * @brief
     *
     */
    void createNewFile();

    /**
     * @brief
     *
     */
    void setDocument(QTextDocument *document);

    /**
     * @brief
     *
     */
    void documentHasChanged();

    /**
     * @brief
     *
     */
    void updateMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList);

    /**
     * @brief
     *
     */
    void resetMathData();

    /**
     * @brief function for setting the Windowtitle
     *
     * @details If the filename is left empty, only the program-name is being displayed.
     *
     * @param fileName  filepath of the currently displayed / opened file
     * @param changesSaved if set to false, a star-symbol (oppened file not saved yet) gets displayed
     */
    void setMainWindowTitle(QString fileName, bool changesSaved);       //set title of the Window anew


    /**
     * @brief function for showing messages in the status-bar
     *
     * @param message
     * @param timeoutMS, how long to display the message in milliseconds
     */
    void showStatusMessage(QString message, int timeoutMS=1000);          //show a message in the statusBar

    /**
     * @brief change the language of the gui-elements
     *
     * @param language (de, en, ...)
     */
    void changeLanguage(QString language);


    /**
     * @brief function for changing the style of the whole mainwindow
     *
     * @param style the whole stylesheet-Text
     */
    void changeStyleSheet(QString &style);



private slots:

    /**
     * @brief functions for triggering other functions, which have to be appended with mathdata
     *
     */
    void emitNewFile();
    void emitOpenFile();
    void emitSaveFile();
    void emitSaveAsFile();
    void emitCloseApp();

    void emitprintFile();
    void emitshowPrintPreview();
    void emitprintPDF();

    /**
     * @brief call the math-solver
     *
     */
    void on_action_solve_triggered();

    /**
     * @brief call the math-solver with current text as parameter
     *
     */
    void on_actiondetect_formulas_triggered();

    /**
     * @brief text-formating-function
     * @{
     */
    void textBold();
    void textUnderline();
    void textItalic();
    void textOverline();
    void textStrikeOut();
    void textFamily(const QString &f);
    void textSize(const QString &p);
    void textStyle(int styleIndex);
    void textColor();
    void textBackgroundColor();
    void textAlign(QAction *a);
    void textShowFontDialog();
    void textSubscript();
    void textSuperscript();
    void textSelectionChanged();

    void textList_Standard();
    void textList_Bullet_Disc();
    void textList_Bullet_Circle();
    void textList_Bullet_Square();
    void textList_Ordered_Decimal();
    void textList_Ordered_AlphaLower();
    void textList_Ordered_AlphaUpper();
    void textList_Ordered_RomanLower();
    void textList_Ordered_RomanUpper();


    void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorPositionChanged();
    /** @} */

    /**
     * @brief function for enabling certain actions
     *
     */
    void clipboardDataChanged();

    /**
     * @brief image-editing-functions
     * @{
     */
    void insertImage();
    void changeImage(double width, double height, QString newFilename, bool useNewFile);
    void insertTable();
    /** @} */

    /**
     * @brief
     *
     */
    void searchText();
    void searchAndReplaceText();


    /**
     * @brief detect if an image is selected and show the ImageForm (Toolbox) accordingly
     *
     */
    void showImageForm();

    /**
     * @brief function for recieving and forwarding errormessages from other submodules
     *
     */
    void recieveErrorMessage(ErrorMessage *msg);



private:
    Ui::MainWindow *ui; //pointer to the Ui
    QTranslator m_translator; // contains the translations for this application
    QTranslator m_baseTranslator;

    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;

    QToolBar *tb;
    QString fileName;

    Imageform *imgForm;
    MathForm *mathForm;

    PagesTextEdit *pageEdit;

    /**
     * @brief setup-functions
     * @{
     */
    void setupTextEdits();
    void connectTextEdit();
    void setupWidgets();
    void setupActions();
    void setupShortcuts();
    void setupTextToolBar();
    /** @}*/

    /**
     * @brief text-functions
     * @{
     */
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void fontChanged(const QFont &f);
    void alignmentChanged(Qt::Alignment a);
    /** @} */



//translation-functions

    /**
     * @brief gets the qml-files in the folder with the qml-files
     *
     * @return QStringList
     */
    QStringList findQmFiles();

    /**
     * @brief gets the language of a qml-file
     *
     * @param qmFile
     * @return QString
     */
    QString languageName(const QString &qmFile);

    /**
     * @brief check if qmFile: i18n_xx.qm matches the lang-String
     *
     * @param lang (de, en, ...)
     * @param qmFile (i18n_xx.qm)
     * @return bool (true if match, e.g. true if qmFile = "i18n_de.qm" and lang = "de")
     */
    static bool languageMatch(const QString& lang, const QString& qmFile);

    /**
     * @brief change the gui-elements language
     *
     * @param translator
     * @param filename
     */
    void switchTranslator(QTranslator& translator, const QString& filename);

    /**
     * @brief change the gui-elements language (using Qt base translations)
     *
     * @param language "de", "en", ...
     */
    void switchbaseTranslator(QString language);

protected:

    /**
     * @brief function for reacting to drag and drop-events
     *
     * @param e
     */
    void dragEnterEvent(QDragEnterEvent *e);

    /**
     * @brief function for reacting to drag and drop-events
     *
     * @param e
     */
    void dropEvent(QDropEvent *e);

    /**
     * @brief changes translator
     * @details used for changing the gui-language by switching the translator
     * @param
     */
    void changeEvent(QEvent *);

    /**
     * @brief closeEvent
     * @details function which gets called when the user closes the application via Alt+F4 or similar ways
     * @param event
     */
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
