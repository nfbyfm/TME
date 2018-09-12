#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QDebug>

#include <Model/Math/mtoken.h>
#include <Model/Math/mformula.h>
#include <Model/Math/mvariable.h>
#include <Model/Math/mfformula.h>
#include <Control/FaultHandler/errormessage.h>

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



public:
    explicit Parser(QObject *parent = nullptr);

signals:
    /**
     * @brief function for sending error messages. connect to faulthandler
     *
     */
    void sendError(ErrorMessage * errmsg);

    /**
     * @brief function that gets triggered when calculations are done
     *
     */
    void sendMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList);


public slots:
    /**
     * @brief main entrypoint for calling modules. starts the parsing-process
     *
     */
    void startParsing(QList< QList<MToken *> > tf_list);

};

#endif // PARSER_H
