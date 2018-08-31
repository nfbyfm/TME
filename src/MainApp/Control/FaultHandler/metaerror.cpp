#include "metaerror.h"

QStringList *MetaError::getErrorList() const
{
    return errorList;
}

void MetaError::setErrorList(QStringList *value)
{
    errorList = value;
}

MetaError::MetaError(QObject *parent, QStringList *errorlist) : QObject(parent)
{
    if(errorlist != nullptr)
    {
        this->errorList = errorlist;
    }
}
