#ifndef METAERROR_H
#define METAERROR_H

#include <QObject>

/**
 * @brief Helperclass for passing additional arguments of the error message
 *
 */

class MetaError : public QObject
{
    Q_OBJECT
private:
    /**
     * @brief list of Errorarguments. As of the first release three arguments can get passed to the faulthandler.
     *
     */
    QStringList *errorList;

public:
    explicit MetaError(QObject *parent = nullptr, QStringList *errorlist = nullptr);

    /**
     * @brief getters and setters
     * @{
     */
    QStringList *getErrorList() const;
    void setErrorList(QStringList *value);
    /** @}*/
signals:

public slots:
};

#endif // METAERROR_H
