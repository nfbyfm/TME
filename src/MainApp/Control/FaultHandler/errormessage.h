#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include <QObject>
#include <Control/FaultHandler/error_enums.h>
#include <Control/FaultHandler/metaerror.h>
#include <Model/Math/mformula.h>

/**
 * @brief Class to describe Errormessages. Besides the message herself, the type (Popup or Statusbar (see Enum)) has to be defined as well.
 *
 * Next step: use Error-Codes and Resource-file (xml-file / list of Errormessages). Also: Errorlevel/priority (needed for the next iteration of the Faulthandler).
 *
 */
class ErrorMessage : public QObject
{
    Q_OBJECT

private:
    ERROR_ID errID;
    QObject *metaInfoObject;

    QString meassage;
    ErrorViewMedium eMedium;
    ErrorType eType;

public:
    /**
     * @brief Constructor of the Errormessage. For the message to show at least the ERROR_ID has to be set.
     *
     */
    explicit ErrorMessage(QObject *parent = nullptr, ERROR_ID eID = ERROR_ID::UNDEFINED, QObject *metaInfo = nullptr);

    /**
     * @brief Getters and Setters
     * @{
     */
    ERROR_ID getErrID() const;

    QObject *getMetaInfoObject() const;

    QString getMeassage() const;

    QString getFormulaNumber();

    QString getFormula();

    void getSolvable(bool &value, QString &strValue);

    ErrorViewMedium getEMedium() const;

    ErrorType getEType() const;

    /** @}*/

    /**
     * @brief function that gets called by the faulthandler.
     *
     */
    void setProperties(QString errMessage, ErrorViewMedium errViewMedium, ErrorType errType);

signals:

public slots:
};

#endif // ERRORMESSAGE_H
