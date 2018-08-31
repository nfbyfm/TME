#ifndef MFORMULA_H
#define MFORMULA_H

#include <QObject>
#include <Model/Math/mtoken.h>
//#include <Model/Math/mvariable.h>

/**
 * @brief
 *
 */
class MFormula : public QObject
{
    Q_OBJECT

private:
    //Variables
    QString ID;
    bool solvable;
    bool isSolved;

    QList<MToken *> tokenList;
    //QList<MVariable *> variableList;

    int comparator_count;
    bool contains_Function;
    int noOfVariables;
    bool comparator_IsEqualSign;

    //Functions

public:
    explicit MFormula(QObject *parent = nullptr);
    ~MFormula();

    /**
     * @brief returns a concated list of all tokens
     *
     */
    QString toString();

    /**
     * @brief getter-function
     *
     */
    QString getID() const;

    /**
     * @brief setter-function
     *
     */
    void setID(const QString &value);

    /**
     * @brief getter-function
     *
     */
    bool getSolvable() const;

    /**
     * @brief setter-function
     *
     */
    void setSolvable(bool value);

    /**
     * @brief getter-function
     *
     */
    QList<MToken *> getTokenList() const;

    /**
     * @brief setter-function
     *
     */
    void setTokenList(const QList<MToken *> &value);

    /**
     * @brief getter-function
     *
     */
    int getNoOfComparators();

    /**
     * @brief getter-function
     *
     */
    int getNoOfVariables();

    /**
     * @brief checks if tokenlist contains a function
     *
     */
    bool containsFunction();

    /**
     * @brief checks if there is a token with an equal sign and no other comparator
     *
     */
    bool comparatorIsEqualSign();

    /**
     * @brief getter-function
     *
     */
    QList<MToken *> getTokenVariables();

    /**
     * @brief getter-function
     *
     */
    QString getVariableNames();

    /**
     * @brief getter-function
     *
     */
    bool getIsSolved() const;

    /**
     * @brief setter-function
     *
     */
    void setIsSolved(bool value);

    /**
     * @brief getter-function
     *
     */
    bool hasBrackets();

    /**
     * @brief getter-function
     *
     */
    bool hasPowerFunction();

signals:

public slots:
};

#endif // MFORMULA_H
