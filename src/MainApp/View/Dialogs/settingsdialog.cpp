#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect(ui->checkBoxAutosave, &QCheckBox::toggled, ui->doubleSpinBoxAutosaveMinutes, &QDoubleSpinBox::setEnabled);
    ui->checkBoxAutosave->setChecked(true);
    ui->checkBoxAutosave->setChecked(false);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

QString SettingsDialog::getSelectedLanguage()
{
    return ui->comboBox_Language->currentText();
}


QString SettingsDialog::getSelectedStyle()
{
    return ui->comboBoxStyle->currentText();
}

bool SettingsDialog::getMathSolverShowErrorDialog()
{
    return ui->checkBox_Show_ErrorListDialog->isChecked();
}

bool SettingsDialog::getAutoSaveEnabled()
{
    return ui->checkBoxAutosave->isChecked();
}

double SettingsDialog::getAutoSaveTimeout()
{
    return ui->doubleSpinBoxAutosaveMinutes->value();
}

bool SettingsDialog::getShowPdfAfterExport()
{
    return ui->checkBoxShowPdfAfterExport->isChecked();
}












void SettingsDialog::setShowPdfAfterExport(bool showPdf)
{
    ui->checkBoxShowPdfAfterExport->setChecked(showPdf);
}


void SettingsDialog::setStyleSheetEntries(QStringList entries)
{
    ui->comboBoxStyle->clear();
    ui->comboBoxStyle->addItems(entries);
}

void SettingsDialog::setCurrentLanguage(QString language)
{
    ui->comboBox_Language->setCurrentText(language);
}

void SettingsDialog::setCurrentStyleSheetName(QString styleSheetName)
{
    ui->comboBoxStyle->setCurrentText(styleSheetName);
}

void SettingsDialog::setCurrentMathSolverShowErrorList(bool show)
{
    ui->checkBox_Show_ErrorListDialog->setChecked(show);
}


void SettingsDialog::setAutoSaveEnabled(bool enabled)
{
    ui->checkBoxAutosave->setChecked(enabled);
}

void SettingsDialog::setAutoSaveTimeout(double value)
{
    ui->doubleSpinBoxAutosaveMinutes->setValue(value);
}



