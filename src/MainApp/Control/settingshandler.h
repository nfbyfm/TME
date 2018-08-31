#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include <QObject>
#include <QSettings>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QMap>
#include <Control/FaultHandler/errormessage.h>
#include <View/Dialogs/settingsdialog.h>
#include <Control/settings_enums.h>

/**
 * @brief class for handling applicationsettings
 *
 */
class SettingsHandler : public QObject
{
    Q_OBJECT

private:
    //variables
    QString sSettingsfilepath;       /**< Path to the Settings-file ( */

    /**
     * @brief Setting-object for loading / saving settings
     *
     */
    QSettings *settings;

    /**
     * @brief Map with the Enums and their QString-Values
     *
     */
    QMap<SETTINGS_ID, QString> *settingsMap;

    //functions
    /**
     * @brief function for getting the stylesheet-setting
     *
     */
    QString getStyleSheetData(QString stylesheetName);

    /**
     * @brief function for getting the list of available stylesheet-files
     *
     */
    void getStyleSheetList(QStringList &fileNames);

    /**
     * @brief function for initializing the Settings-Map
     *
     */
    void initSettingsMap();

public:
    explicit SettingsHandler(QObject *parent = nullptr);

    /**
     * @brief function for loading of available settings
     * gets called by main controller
     */
    void loadSettings();



signals:
    /**
     * @brief functions for relaying settings to other parts of the application
     * @{
     */
    void setMainStyleSheet(QString &style);
    void changeLanguage(QString language);
    void autosaveChanged(bool enabled, double timeout);
    /** @}*/

    /**
     * @brief function for sending errormessages
     *
     */
    void sendError(ErrorMessage *errmsg);


public slots:


    /**
     * @brief function for getting the value of a setting
     *
     * @param settingName Value you're looking for
     * @param value  the value (if the setting could be found)
     * @param settingFound tells wheather the setting could be found or not
     */
    Q_DECL_DEPRECATED void getSetting(QString settingName, QString &value, bool &settingFound);

    /**
     * @brief function for getting a spezific setting
     *
     */
    void getSetting(SETTINGS_ID settingID, QString &value, bool &settingFound);


    Q_DECL_DEPRECATED void setSetting(QString settingName, QString value);

    /**
     * @brief function for setting a settingvalues
     *
     */
    void setSetting(SETTINGS_ID settingID, QString value);


    /**
     * @brief function for showing the settings-dialog
     * gets called by controller
     */
    void showSettingsDialog(QWidget *parentView);
};


#endif // SETTINGSHANDLER_H
