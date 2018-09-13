#ifndef MATHFORM_H
#define MATHFORM_H

#include <QWidget>
#include <QDebug>

#include <Model/Math/mvariable.h>
#include <Control/FaultHandler/errormessage.h>

/**
 * @brief UI-Element for displaying and editing of math-formulas and -variables
 *
 */
namespace Ui {
class MathForm;
}

class MathForm : public QWidget
{
    Q_OBJECT

public:
    explicit MathForm(QWidget *parent = nullptr);
    ~MathForm();

    /**
     * @brief setter-function
     *
     */
    void setMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList);

    /**
     * @brief function for resetting the fromula and varaible-table
     *
     */
    void resetTables();

    /**
     * @brief getter-function
     *
     */
    int numberOfFormulas();

    /**
     * @brief getter-function
     *
     */
    int numberOfVariables();

    /**
     * @brief getter-function
     *
     */
    QStringList *getListofCurrentFormulas();

    /**
     * @brief getter-function
     *
     */
    QStringList *getListofCurrentVariables();

    /**
     * @brief function for retranslation of the UI-Elements
     *
     */
    void retranslateUI();

    /**
     * @brief setup-function for setting the orientation of the main splitter
     *
     */
    void setupSlitterOrientation(Qt::Orientation orientation);

private:
    Ui::MathForm *ui;

    /**
     * @brief setup-function for the tableWidgets
     *
     */
    void setupTableWidgets();

    /**
     * @brief setup-function for connecting the button signals to privatte slots
     *
     */
    void setupButtons();

    /**
     * @brief setup-function for setting the combobox-items
     *
     */
    void setupComboBoxes();



private slots:
    /**
     * @brief detection of user-input
     *
     */
    void addVaraible();

    /**
     * @brief detection of user-input
     *
     */
    void removeVariable();

    /**
     * @brief detection of user-input
     *
     */
    void addVaraibleToText();


    /**
     * @brief detection of user-input
     *
     */
    void addFormula();

    /**
     * @brief detection of user-input
     *
     */
    void removeFormula();

    /**
     * @brief detection of user-input
     *
     */
    void addFormulaToText();

signals:
    void sendError(ErrorMessage *msg);
    void addTextToDocument(QString text);
    void valuesChanged();                   //signals if a variable/formula has been added or removed -> for marking a document as changed
};

#endif // MATHFORM_H
