#ifndef MFFORMULA_H
#define MFFORMULA_H

#include <QObject>
#include <QDebug>
#include <Model/Math/mfpart.h>

/**
 * @brief Class for mathematical formulas. Contains a list of MFFOrmula-Objects.
 *
 */
class MFFormula : public QObject
{
    Q_OBJECT

#define Abs(x)    ((x) < 0 ? -(x) : (x))
#define Max(a, b) ((a) > (b) ? (a) : (b))

private:
    QList <MFPart*> * formulaParts;

public:
    explicit MFFormula(QObject *parent = nullptr);

    /**
     * @brief getter-function
     *
     */
    QList<MFPart *> *getFormulaParts() const;

    /**
     * @brief setter-function
     *
     */
    void setFormulaParts(QList<MFPart *> *value);

    /**
     * @brief function for adding another MFPart
     *
     */
    void appendList(MFPart *newElement);

    /**
     * @brief function for getting the number of variables (in whole List)
     *
     */
    int getNumberOfVariables();

    /**
     * @brief function for simplifiying the List / formula
     *
     */
    void simplify();

    /**
     * @brief function for calculating the difference of two double-values
     *
     */
    double relDif(double a, double b);
    const double Tolerance = 0.001; //allowed deviation between two double Values in order to be considered the same

    /**
     * @brief function for getting each MFPart as a Pair of <double, MVarialbe*>
     * (needed for the Math-solver)
     */
    QList<QPair<double,MVariable*> *> *getCoeficientList();

    /**
     * @brief better 'toString'-function
     * (returns Formula as MFPart + MFPart + ... + MFPart = 0')
     */
    QString getSimplifiedFormulaString();

signals:

public slots:
};

#endif // MFFORMULA_H
