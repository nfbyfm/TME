#ifndef MTOKEN_H
#define MTOKEN_H

#include <QObject>
#include <Model/Math/mtokentype.h>


/**
 * @brief Math-Token
 *
 */
class MToken : public QObject
{
    Q_OBJECT
private:
    /**
     * @brief value (single char or String like a variable-name
     *
     */
    QString value;

    /**
     * @brief what kind of Type the Token is (for example Variable or Number, ...)
     *
     */
    MTokenType type;

    /**
     * @brief Object usually used as a pointer to the MVariable that is defined in this token
     *
     */
    QObject *mObject;        //pointer to various possible Objects. mostly used as a pointer for variables

    /**
     * @brief turns TokenType into a QString
     *
     */
    QString TokenTypeToString(MTokenType type);

public:
    explicit MToken(QObject *parent = nullptr, QString string = "", MTokenType type = MTokenType::UNDEFINED);


    /**
     * @brief getter-function
     *
     */
    QString getValue() const;


    /**
     * @brief setter-function
     *
     */
    void setValue(const QString &value);


    /**
     * @brief getter-function
     *
     */
    MTokenType getType() const;


    /**
     * @brief setter-function
     *
     */
    void setType(const MTokenType &value);

    /**
     * @brief returns a QString containing the Tokentype and the Value
     *
     */
    QString toString();

    /**
     * @brief getter-function
     *
     */
    QObject *getMObject() const;

    /**
     * @brief setter-function
     *
     */
    void setMObject(QObject *object);

signals:

public slots:
};

#endif // MTOKEN_H
