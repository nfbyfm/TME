#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
//#include <QTextDocument>
#include "Model/Math/mathmodel.h"


/**
 * @brief Class which contains all document-Elements and the Math-Model
 * (not used in the first release of the software)
 */
class MainModel : public QObject
{
    Q_OBJECT

private:

    QString fileName;

    MathModel *mMathModel;
    //QTextDocument *tDocument;

    bool isUntitled;

    //Pagesize

    //Footer

    //Header

    //language


    void connect();


public:
    explicit MainModel(QObject *parent = nullptr);



    //QTextDocument *getTDocument();
    //void setTDocument(QTextDocument *value);

    QString getFileName() const;
    void setFileName(const QString &value);

    //QString getHTMLFormulaAppendix();


    bool getIsUntitled() const;

    MathModel *getMathModel() const;

signals:
    void sendMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList);

public slots:
    //void recieveTokenizedFormulas();
    void recieveMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList);
};

#endif // MAINMODEL_H
