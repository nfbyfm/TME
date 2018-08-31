#ifndef MATHMODEL_H
#define MATHMODEL_H

#include <QObject>
#include <QDebug>
#include <iostream>
#include <Model/Math/mformula.h>
#include <Model/Math/mvariable.h>

/**
 * @brief main math model,
 * contains a list of formulas and a list their variables
 */
class MathModel : public QObject
{
    Q_OBJECT

private:
    /**
     *  @brief List of Fromulas and their Variables
     * @{
     */
    QList <MFormula *> lFormulas;
    QList <MVariable *> lVariables;
    /** @}*/
public:
    /**
     * @brief Constructor
     *
     * @param parent
     */
    explicit MathModel(QObject *parent = nullptr);
    ~MathModel();


    /**
     * @brief Getter-function for Fromulas
     *
     */
    QList<MFormula *> getLFormulas() const;

    /**
     * @brief Getter-function for Variables
     *
     */
    QList<MVariable *> getLVariables() const;

signals:

public slots:

    /**
     * @brief setter-function for Formulas and variables
     *
     */
    void recieveMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList);


};

#endif // MATHMODEL_H
