#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QDebug>

#include <Model/Math/mtoken.h>
#include <Model/Math/mformula.h>
#include <Model/Math/mvariable.h>
#include <Model/Math/mfformula.h>
//#include <Control/FaultHandler/errormessage.h>

/**
 * @brief Class for parsing tokenized formulas
 *
 */
class Parser : public QObject
{
    Q_OBJECT

#define Abs(x)    ((x) < 0 ? -(x) : (x))
#define Max(a, b) ((a) > (b) ? (a) : (b))

private:
    /**
     * @brief helper-function for setting the formula-ID
     *
     */
    QString padZeroNumber(int number);

    /**
     * @brief helper-function for solving simple equations like a=10 or 10=a
     *
     */
    bool solveSimpleEquation(MFormula *formula);//, QList<MVariable *> v_List);

    /**
     * @brief helper-function for calculation the difference between two double-values
     *
     */
    double relDif(double a, double b);
    const double Tolerance = 0.001; //allowed deviation between two double Values in order to be considered the same


    /**
     * @brief helper-function for converting a MToken of Type::Constant into a MToken of Type::numeric
     *
     */
    MToken *constantTokenToNumeric(QString constValue);

    /**
     * @brief helper-function for converting a MToken of Type::Variable into a MToken of Type::numeric
     *
     */
    MToken *variableTokenNumeric(MToken* tokenPoinster);

    /**
     * @brief helper-function for checking if a division by number is supposed to happen. ALters MFPart accordingly.
     *
     */
    void numberTokenReciproque(MToken* tokenPointer, MFPart *tmpPart);
public:
    explicit Parser(QObject *parent = nullptr);

signals:
    /**
     * @brief function for sending error messages. connect to faulthandler
     *
     */
    //void sendError(ErrorMessage * errmsg);

    /**
     * @brief function that gets triggered when calculations are done
     *
     */
    void sendMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList, QList <MFFormula *> * partitionedFormulasList);


public slots:
    /**
     * @brief main entrypoint for calling modules. starts the parsing-process
     *
     */
    QList <MFFormula *> * startParsing(QList< QList<MToken *> > tf_list, QList <MFormula *> &f_List, QList <MVariable *> &v_List);

};

#endif // PARSER_H
