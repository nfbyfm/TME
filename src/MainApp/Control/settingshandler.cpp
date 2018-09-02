#include "settingshandler.h"


SettingsHandler::SettingsHandler(QObject *parent) : QObject(parent)
{
    sSettingsfilepath  = QApplication::applicationDirPath() + "/Settings/MainSettings.ini";
    //qDebug() << sSettingsfilepath;
    settings = new QSettings(sSettingsfilepath, QSettings::IniFormat);
    initSettingsMap();
}

void SettingsHandler::initSettingsMap()
{
    this->settingsMap = new QMap<SETTINGS_ID,QString>;
    settingsMap->insert(SETTINGS_ID::LANGUAGE,"Language");
    settingsMap->insert(SETTINGS_ID::STYLESHEETNAME,"StyleSheetName");
    settingsMap->insert(SETTINGS_ID::MATHSOLVER_SHOWERRORLIST,"mathSolverShowErrorList");
    settingsMap->insert(SETTINGS_ID::AUTOSAVE_ENABLE,"autoSave_enabled");
    settingsMap->insert(SETTINGS_ID::AUTOSAVE_TIMEOUT,"autoSaveTimeout");
    settingsMap->insert(SETTINGS_ID::SHOW_PDF_AFTER_EXPORT,"showPdfAfterExport");
}

void SettingsHandler::loadSettings()
{
    //Load stylesheets, languages, ...


    //Langugage: search the settings. If empty try the default language of the system
    QString defaultLang;
    bool settingFound=false;
    getSetting(SETTINGS_ID::LANGUAGE,defaultLang, settingFound);
    if (!settingFound)
    {
        defaultLang = QLocale::system().name();
    }
    //qDebug() <<"loaded languge: " << defaultLang;
    emit changeLanguage(defaultLang);


    QString styleSheetFileName = "";
    QString styleSheetContent = "";

    getSetting(SETTINGS_ID::STYLESHEETNAME, styleSheetFileName, settingFound);

    if (settingFound || styleSheetFileName !="" || styleSheetFileName !="default")
    {
        styleSheetContent = getStyleSheetData(styleSheetFileName);
    }
    else
    {
        emit sendError(new ErrorMessage(this,ERROR_ID::SETTINGS_SettingNotFound, new MetaError(this,new QStringList({this->settingsMap->value(SETTINGS_ID::STYLESHEETNAME)}))));
    }

    emit setMainStyleSheet(styleSheetContent);


    //autosave Enabled
    QString settingval="";
    getSetting(SETTINGS_ID::AUTOSAVE_ENABLE, settingval, settingFound);
    bool autosaveIsEnabled=true;

    if(settingFound)
        autosaveIsEnabled = (settingval=="true");



    //autosave Timeout
    getSetting(SETTINGS_ID::AUTOSAVE_TIMEOUT, settingval, settingFound);
    double timeout = 1.0;
    if(settingFound)
        timeout = settingval.toDouble(&settingFound);

    emit autosaveChanged(autosaveIsEnabled, timeout);


    //show pdf after export
    settingval="";
    getSetting(SETTINGS_ID::SHOW_PDF_AFTER_EXPORT, settingval, settingFound);
    bool showpdfAfterExport=false;

    if(settingFound)
        showpdfAfterExport = (settingval=="true");

    emit showPdfAfterExportChanged(showpdfAfterExport);
}


void SettingsHandler::getSetting(QString settingName, QString &value, bool &settingFound)
{
    QString defaultSetting = "def1234";
    QString sText = settings->value(settingName, defaultSetting).toString();

    if(sText==defaultSetting)
    {
        value="";
        settingFound = false;
    }
    else
    {
        value = sText;
        settingFound = true;
    }
}

void SettingsHandler::getSetting(SETTINGS_ID settingID, QString &value, bool &settingFound)
{
    QString defaultSetting = "def1234";
    QString settingName = this->settingsMap->value(settingID);
    //qDebug()<<"getSetting via Enum called. Value: " << settingName;
    QString sText = settings->value(settingName, defaultSetting).toString();

    if(sText==defaultSetting)
    {
        value="";
        settingFound = false;
    }
    else
    {
        value = sText;
        settingFound = true;
    }
}


void SettingsHandler::setSetting(QString settingName, QString value)
{
    settings->setValue(settingName, value);
}

void SettingsHandler::setSetting(SETTINGS_ID settingID, QString value)
{
    //try to find the setting in the QMap for the settings
    QString settingNotFound = "setting_not_found";
    QString settingName = this->settingsMap->value(settingID,settingNotFound);

    if(settingName != settingNotFound)
        settings->setValue(settingName, value);
    else
        qDebug()<<"setSetting: SettingName could not be found in QMap";
}


void SettingsHandler::getStyleSheetList(QStringList &fileNames)
{
    QString m_langPath = QApplication::applicationDirPath();
    m_langPath.append("/Resources/stylesheets");
    QDir dir(m_langPath);

    fileNames = dir.entryList(QStringList("*.stylesheet"), QDir::Files);//, QDir::Name);
    fileNames.append("default");

    /*
    foreach(QString fiNa, fileNames) {
        qDebug() <<"File found:" << fiNa;
    }
    */
}

QString SettingsHandler::getStyleSheetData(QString stylesheetName)
{
    QString data ="";

    if(stylesheetName !="default" && stylesheetName!="")
    {
        QString m_langPath = QApplication::applicationDirPath();
        QString  fileName = m_langPath.append("/Resources/stylesheets/").append(stylesheetName);

        QFile file(fileName);

        if(!file.open(QIODevice::ReadOnly))
        {
            emit sendError(new ErrorMessage(this,ERROR_ID::SETTINGS_StylesheetNotFound, new MetaError(this,new QStringList({stylesheetName}))));
            qDebug()<<"Stylesheetfile could not be found/opened. Filename: " << fileName <<endl;
        }
        else
        {
            data = file.readAll();
        }

        file.close();
    }


    return data;
}



void SettingsHandler::showSettingsDialog(QWidget *parentView)
{
    //create new Dialog (with parentView so style, Icon and so on get automatically inherited)
    //if result equals Accepted: save and realise them new settings

    SettingsDialog *sedi = new SettingsDialog(parentView);

    //set Dialog Title
    sedi->setWindowTitle(tr("Settings"));

    //fill List of possible Stylesheets
    QStringList stylesheets;
    getStyleSheetList(stylesheets);
    sedi->setStyleSheetEntries(stylesheets);

    //set current setting-values
    bool settingFound=false;

    //Langugage: search the settings. If empty try the default language of the system
    QString settingVal = QLocale::system().name();
    getSetting(SETTINGS_ID::LANGUAGE, settingVal, settingFound);
    sedi->setCurrentLanguage(settingVal);

    //Stylesheet
    settingVal = "";
    getSetting(SETTINGS_ID::STYLESHEETNAME, settingVal, settingFound);
    sedi->setCurrentStyleSheetName(settingVal);

    //show Errorlist
    settingVal = "";
    getSetting(SETTINGS_ID::MATHSOLVER_SHOWERRORLIST, settingVal, settingFound);
    if(settingFound)
        sedi->setCurrentMathSolverShowErrorList((settingVal=="true"));
    else
        sedi->setCurrentMathSolverShowErrorList(false);

    //Autosave enabled
    settingVal = "";
    getSetting(SETTINGS_ID::AUTOSAVE_ENABLE, settingVal, settingFound);
    if(settingFound)
        sedi->setAutoSaveEnabled((settingVal=="true"));
    else
        sedi->setAutoSaveEnabled(false);

    //autosave-Timeout
    settingVal = "";
    double settingValue = 1;
    getSetting(SETTINGS_ID::AUTOSAVE_TIMEOUT, settingVal, settingFound);
    settingValue = settingVal.toDouble(&settingFound);
    sedi->setAutoSaveTimeout(settingValue);


    //Autosave enabled
    settingVal = "";
    getSetting(SETTINGS_ID::SHOW_PDF_AFTER_EXPORT, settingVal, settingFound);
    if(settingFound)
        sedi->setShowPdfAfterExport((settingVal=="true"));
    else
        sedi->setShowPdfAfterExport(false);





    //show the Dialog
    int dialogCode = sedi->exec();

    //check if new settings accepted
    if(dialogCode == QDialog::Accepted )
    {
        //get selected values from dialog and save them
        setSetting(SETTINGS_ID::STYLESHEETNAME, sedi->getSelectedStyle());
        setSetting(SETTINGS_ID::LANGUAGE, sedi->getSelectedLanguage());

        if(sedi->getMathSolverShowErrorDialog())
            setSetting(SETTINGS_ID::MATHSOLVER_SHOWERRORLIST, "true");
        else
            setSetting(SETTINGS_ID::MATHSOLVER_SHOWERRORLIST, "false");


        if(sedi->getAutoSaveEnabled())
            setSetting(SETTINGS_ID::AUTOSAVE_ENABLE, "true");
        else
            setSetting(SETTINGS_ID::AUTOSAVE_ENABLE, "false");

        setSetting(SETTINGS_ID::AUTOSAVE_TIMEOUT, QString::number(sedi->getAutoSaveTimeout()));


        if(sedi->getShowPdfAfterExport())
            setSetting(SETTINGS_ID::SHOW_PDF_AFTER_EXPORT, "true");
        else
            setSetting(SETTINGS_ID::SHOW_PDF_AFTER_EXPORT, "false");


        //update gui / whole Application
        loadSettings();
    }
}
