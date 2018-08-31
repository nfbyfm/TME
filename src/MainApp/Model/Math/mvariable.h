#ifndef MVARIABLE_H
#define MVARIABLE_H

#include <QObject>
#include <Model/Math/mformula.h>

/**
 * @brief class for a Variable used in an mathematical equation
 *
 */
class MVariable : public QObject
{
    Q_OBJECT

private:
    /**
     * @brief List of references to formulas where it's being used
     *
     */
    QList<MFormula *> formulaRefs;

    /**
     * @brief Varaiblename given by the user
     *
     */
    QString textValue;

    /**
     * @brief actual numeric value of the varaible (get calculated by math-engine)
     *
     */
    double numericValue;

    /**
     * @brief indicates wheter the Variable has been solved / the numeric value has been set
     *
     */
    bool solved;

    /**
     * @brief indicates whether the varaible gets use in more than one location and the calculated numeric results are different
     *
     */
    bool overdetermined;

public:
    explicit MVariable(QObject *parent = nullptr);
    ~MVariable();

    /**
     * @brief getter-function
     *
     */
    QString getTextValue() const;

    /**
     * @brief setter-function
     *
     */
    void setTextValue(const QString &value);

    /**
     * @brief getter-function
     *
     */
    double getNumericValue() const;

    /**
     * @brief setter-function
     *
     */
    void setNumericValue(double value);

    /**
     * @brief function for adding a reference to a formula (where is't being used)
     *
     */
    void addFormulaRef(MFormula *formula);

    /**
     * @brief getter-function
     *
     */
    QList<MFormula *> getFormulaRefs() const;

    /**
     * @brief setter-function
     *
     */
    void setFormulaRefs(const QList<MFormula *> &value);

    /**
     * @brief getter-function
     *
     */
    QString getFormulaNumberList();

    /**
     * @brief getter-function
     *
     */
    bool getSolved() const;

    /**
     * @brief setter-function
     *
     */
    void setSolved(bool value);

    /**
     * @brief function for checking whether this variable in in the given formula or not
     *
     */
    bool isInFormula(MFormula * formula);

    /**
     * @brief getter-function
     *
     */
    bool getOverdetermined() const;

    /**
     * @brief setter-function
     *
     */
    void setOverdetermined(bool value);

signals:

public slots:
};

#endif // MVARIABLE_H
