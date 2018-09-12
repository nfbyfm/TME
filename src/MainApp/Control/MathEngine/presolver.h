#ifndef PRESOLVER_H
#define PRESOLVER_H

#include <QObject>
#include <Model/Math/mathmodel.h>
#include <Model/Math/mfformula.h>
#include <Control/FaultHandler/errormessage.h>

class PreSolver : public QObject
{
    Q_OBJECT
private:



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

    /**
     * @brief function for simplifying a single formula
     *
     */
    void simplifyEquations(QList<MFFormula *> *mfFormulaList);

    /**
     * @brief function for connecting lexer, parser, model, ...
     *
     */
    void simplifyUnsolvedEquations(QList<MFormula *> mFormulaList);

public:
    explicit PreSolver(QObject *parent = nullptr);

    /**
     * @brief
     *
     */
    QList <MFFormula *> * getPartitionedFormulasList(QList <MFormula *> f_List);


signals:
    /**
     * @brief function for sending errormessages to the faulthandler
     *
     */
    void sendError(ErrorMessage *errmsg);
public slots:
};

#endif // PRESOLVER_H
