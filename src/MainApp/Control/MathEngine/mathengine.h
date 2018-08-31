#ifndef MATHENGINE_H
#define MATHENGINE_H

#include <QObject>
#include <QDebug>
#include <Model/Math/mathmodel.h>
#include <Control/MathEngine/lexer.h>
#include <Control/MathEngine/parser.h>
#include <Control/MathEngine/msolver.h>
#include <Control/FaultHandler/errormessage.h>


/**
 * @brief Main class for all the math-related functionalities.
 * contains the Lexer, parser and solver.
 */
class MathEngine : public QObject
{
    Q_OBJECT

public:
    explicit MathEngine(QObject *parent = nullptr);
    ~MathEngine();

private:

    QStringList *formulasFromText;

    /**
     * @brief pointer to the MathModel
     * which is in reality owned by the documenthandler
     *
     */
    MathModel *mMathModel;

    /**
     * @brief Lexer for the tozenization of formulas given as a List of QStrings
     *
     */
    Lexer *mLexer;

    /**
     * @brief Parser for the tokenized formulas of the parser
     * presolves, simplifies and prepares formulas for the solver
     */
    Parser *mParser;

    /**
     * @brief Solver. Takes the equations generated by the parser and solves them.
     * Results get writeen into the MathModel via pointer
     */
    MSolver *mSolver;


    /**
     * @brief function for connecting lexer, parser, model, ...
     *
     */
    void connect();
    void simplifyEquations(QList<MFFormula *> *mfFormulaList);


    /**
     * @brief function for finding formulas and similar math-expressions in the given text
     *
     * @param text has to be of Type QString
     * @return bool true if at least one formula could be found. False otherwise.
     */
    bool searchFormulas(QString text);

    /**
     * @brief helper-function for removing escape-sequneces from QStrings
     * needed mostly for getting formulas out of a text / preparing them for the Lexer
     */
    QString replaceEscapeSequences(QString formula);

    /**
     * @brief helper-function for checking whether the string is in one of the listentries
     *
     */
    bool inList(QStringList *list, QString value);

signals:
    /**
     * @brief function for sending errormessages to the faulthandler
     *
     */
    void sendError(ErrorMessage *errmsg);

    //void startLexer(QString text);
    /**
     * @brief legacy function
     *
     */
    void sendTokenizedFormulas();

    /**
     * @brief signal for starting the parser
     *
     */
    void startParser(QList< QList<MToken *> > tf_list);

    /**
     * @brief triggers the showing of the error-dialog
     *
     */
    void showErrorList();

    /**
     * @brief for sending the calculation results to the mathmodel
     *
     */
    void sendMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList);

    /**
     * @brief signals when the solver is / calculations are done
     *
     */
    void solverDone();

public slots:
    /**
     * @brief entrypoints for calling modules
     * @{
     */
    void startSolver(QString text, bool overwriteExistingFormulas, QStringList *formulasFromModel);
    void startSolver(QStringList *formulasFromModel);
    /** @}*/

    /**
     * @brief slot for Lexer, parser and solver. Errors get reemitted.
     *
     */
    void recieveError(ErrorMessage *errmsg);

    /**
     * @brief function for recieving tokenized formulas from the lexer
     *
     */
    void recieveTokenizedFormulas(QList< QList<MToken *> > tf_list);

    /**
     * @brief function for recieving data from the parser
     *
     */
    void recieveMathDataFromParser(QList<MFormula*> formulaList, QList<MVariable*> variableList, QList<MFFormula *> *mfFormulaList);

    /**
     * @brief importatnt slot for setting the mathmodel. connect to documenthandler or similar.
     *
     */
    void setMathModel(MathModel *mathModel);
};

#endif // MATHENGINE_H
