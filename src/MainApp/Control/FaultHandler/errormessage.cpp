#include "errormessage.h"



ErrorMessage::ErrorMessage(QObject *parent, ERROR_ID eID, QObject *metaInfo) : QObject(parent)
{
    this->errID = eID;
    this->metaInfoObject = metaInfo;
}


void ErrorMessage::setProperties(QString errMessage, ErrorViewMedium errViewMedium, ErrorType errType)
{
    this->meassage = errMessage;
    this->eMedium = errViewMedium;
    this->eType = errType;
}


//if the metaInfoObject is a formula -> get the Number
QString ErrorMessage::getFormulaNumber()
{
    QString retVal ="";

    MFormula  * formula = qobject_cast<MFormula*>(metaInfoObject);
    if(formula != nullptr)
    {
        retVal = formula->getID();
    }

    return retVal;
}

//if the metaInfoObject is a formula -> get the Formula
QString ErrorMessage::getFormula()
{
    QString retVal ="";

    MFormula  * formula = qobject_cast<MFormula*>(metaInfoObject);
    if(formula != nullptr)
    {
        retVal = formula->toString();
    }


    return retVal;
}

//if the metaInfoObject is a formula -> get whether the equation can be solved or not
void ErrorMessage::getSolvable(bool &value, QString &strValue)
{
    value = false;
    strValue = tr("no");

    MFormula  * formula = qobject_cast<MFormula*>(metaInfoObject);
    if(formula != nullptr)
    {
        value = formula->getSolvable();

        if(value == true)
            strValue = tr("yes");
    }

}


ERROR_ID ErrorMessage::getErrID() const
{
    return errID;
}

QObject *ErrorMessage::getMetaInfoObject() const
{
    return metaInfoObject;
}

QString ErrorMessage::getMeassage() const
{
    return meassage;
}

ErrorViewMedium ErrorMessage::getEMedium() const
{
    return eMedium;
}

ErrorType ErrorMessage::getEType() const
{
    return eType;
}
