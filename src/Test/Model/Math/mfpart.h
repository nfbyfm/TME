#ifndef MFPART_H
#define MFPART_H

#include <QObject>
#include <QtDebug>
#include <Model/Math/mformula.h>
#include <Model/Math/mvariable.h>
#include <Model/Math/mfparttype.h>

/**
 * @brief class for standardizing an equation-part
 *
 */
class MFPart : public QObject
{
    Q_OBJECT

private:
    MFormula *origFormula;
    MFPartType gType;

    QList <MToken *> tokenList;
    bool negateElements;

    /**
     * @brief if there have been changes made in the Tokenlist, call this to update the Type
     *
     */
    void updateType();
public:
    explicit MFPart(QObject *parent = nullptr);

    void removeLastToken();
    /**
     * @brief getter-function
     *
     */
    MFormula *getOrigFormula() const;

    /**
     * @brief setter-function
     *
     */
    void setOrigFormula(MFormula *value);

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


    void appendTokenList(MToken * newElement);

    /**
     * @brief getter-function
     *
     */
    bool getNegateElements() const;

    /**
     * @brief setter-function
     *
     */
    void setNegateElements(bool value);

    /**
     * @brief function for getting a concated String of the Tokenlist
     *
     */
    QString tokenListToString();

    /**
     * @brief function for simplifying the tokenList
     *
     */
    void simplifyList();

    /**
     * @brief getter-function
     *
     */
    MFPartType getGType() const;

    /**
     * @brief setter-function
     *
     */
    void setGType(const MFPartType &value);

    /**
     * @brief for checking if two or more Variables get multiplied
     *
     */
    bool multiplError();

    /**
     * @brief for checking if there's a division by varaible
     *
     */
    bool divisionError();

    /**
     * @brief getter-function
     *
     */
    bool getNumericValue(double &value);

    /**
     * @brief getter-function
     * if returnvalue != 1 -> Error
     */
    int getVariableName(QString &name);

    /**
     * @brief getter-function
     *
     */
    QPair<double, MVariable*> *getVariablePair();
signals:

public slots:
};

#endif // MFPART_H
