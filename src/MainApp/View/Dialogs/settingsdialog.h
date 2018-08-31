#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>


namespace Ui {
class SettingsDialog;
}

/**
 * @brief dialog for showing the application settings
 *
 */
class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    /**
     * @brief setter-function
     *
     */
    void setStyleSheetEntries(QStringList entries);

    /**
     * @brief setter-function
     *
     */
    void setCurrentLanguage(QString language);

    /**
     * @brief setter-function
     *
     */
    void setCurrentStyleSheetName(QString styleSheetName);

    /**
     * @brief setter-function
     *
     */
    void setCurrentMathSolverShowErrorList(bool show);

    /**
     * @brief setter-function
     *
     */
    void setAutoSaveEnabled(bool enabled);

    /**
     * @brief setter-function
     *
     */
    void setAutoSaveTimeout(double value);

    /**
     * @brief getter-function
     *
     */
    QString getSelectedLanguage();

    /**
     * @brief getter-function
     *
     */
    QString getSelectedStyle();

    /**
     * @brief getter-function
     *
     */
    bool getMathSolverShowErrorDialog();

    /**
     * @brief getter-function
     *
     */
    bool getAutoSaveEnabled();

    /**
     * @brief getter-function
     *
     */
    double getAutoSaveTimeout();

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
