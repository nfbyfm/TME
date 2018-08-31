#include "mtoken.h"


MToken::MToken(QObject *parent, QString string, MTokenType type) : QObject(parent)
{
    this->value = string;
    this->type = type;
    this->mObject = nullptr;
}


#define GETTERS_AND_SETTERS_START {

    QString MToken::getValue() const
    {
        return value;
    }

    void MToken::setValue(const QString &value)
    {
        this->value = value;
    }

    MTokenType MToken::getType() const
    {
        return type;
    }

    void MToken::setType(const MTokenType &value)
    {
        type = value;
    }

    QObject *MToken::getMObject() const
    {
        return mObject;
    }

    void MToken::setMObject(QObject *object)
    {
        mObject = object;
    }

#define GETTERS_AND_SETTERS_END }


#define DIAGNOSTICS_FUNCTIONS_START {
    QString MToken::toString()
    {
        return "Tokenvalue: " + value + "     Type: " + TokenTypeToString(this->type);
    }

    QString MToken::TokenTypeToString(MTokenType type)
    {
        QString result = "unknown type";

        switch(type)
        {
            case MTokenType::PRIORITIZER:
                result = "Prioritizer";
                break;
            case MTokenType::OPERATOR:
                result = "Operator";
                break;
            case MTokenType::NUMBER:
                result = "Number";
                break;
            case MTokenType::VARIABLE:
                result = "Variable";
                break;
            case MTokenType::FUNCTION:
                result = "Function";
                break;
            case MTokenType::CONSTANT:
                result = "Constant";
                break;
            case MTokenType::COMPARATOR:
                result = "Comparator";
                break;
            case MTokenType::LINK:
                result = "Link-Function";
                break;
            case MTokenType::UNDEFINED:
                result = "Undefined";
                break;
            //default:
            //    result = "unknown type";
            //    break;
        }
        return result;
    }

#define DIAGNOSITCS_FUNCTIONS_END    }
