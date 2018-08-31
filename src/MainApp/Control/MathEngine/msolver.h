#ifndef MSOLVER_H
#define MSOLVER_H

#include <QObject>
#include <Model/Math/mfformula.h>
#include <Model/Math/mvariable.h>
#include <Libraries/alglib_3_14_0/alglib.h>
#include <Control/FaultHandler/errormessage.h>

/**
 * @brief class for solving linear equation systems
 * A*x = b
 * uses the ALGLIB-library for solving the equation above
 */
class MSolver : public QObject
{
    Q_OBJECT
private:
    /**
     * @brief Matrix and vectors for A*x = b
     *@{
     */
    alglib::real_2d_array aMatrix;
    alglib::real_1d_array bVector;
    alglib::real_1d_array xVector;
    /**@}*/
public:
    explicit MSolver(QObject *parent = nullptr);

signals:
    /**
     * @brief function for sending errormessages. connect to faulthandler.
     *
     */
    void sendError(ErrorMessage *errmsg);

public slots:
    /**
     * @brief main enrtypoint. call this function for starting the solver
     *
     */
    bool startSolving(QList<MFFormula *> *formulaList);
};

#endif // MSOLVER_H
