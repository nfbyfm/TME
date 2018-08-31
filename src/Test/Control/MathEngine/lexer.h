#ifndef LEXER_H
#define LEXER_H

#include <QObject>
#include <QDebug>
#include <cctype>
#include <Model/Math/mathmodel.h>
#include <Model/Math/mtoken.h>
//#include <Control/FaultHandler/errormessage.h>

/**
 * @brief Enum needed for the first classification of a single char
 *
 */
enum class CType
{
    Letter,
    Digit,
    LeftBracket,
    RightBracket,
    Operator,
    Comparator,
    Dot,
    Space,
    Backslash,
    UnderLine_Apostrophe,
    Symbol //everything else
};

/**
 * @brief main class for tokenization of a formula (QString)
 *
 */
class Lexer : public QObject
{
    Q_OBJECT

private:

//Variables
    //MathModel *mMathModel;
    QMap<QString, MTokenType> keywords;

//Functions
    /**
     * @brief main function. takes List of formulas (QStringList) as an argument and turns each into a List of MToken
     *
     */
    QList<QList<MToken *> > lexing(QStringList *formulasFromText);

    /**
     * @brief helperfunction for getting the type of a single char
     *
     */
    CType getType(QChar alpha);

    /**
     * @brief helper-function for checing number of brackets
     *
     */
    bool checkBrackets(QString checkStr, int & noOfLBrackets, int & noOfRBrackets, int & noOfUnclosedBrakets, bool &underScoreFound);

    /**
     * @brief helper-function for initializing the keyword-Map
     *
     */
    void initKeyWords();


public:
    explicit Lexer(QObject *parent = nullptr);
    ~Lexer();

signals:
    /**
     * @brief when the tokenization of the formulas this signal gets emitted
     *
     */
    void sendTokenizedFormulas(QList< QList<MToken *> > tFList);

    /**
     * @brief i an error occurs during lexing, this signal gets emitted. Connect to FaultHanlder after creation.
     *
     */
    //void sendError(ErrorMessage * errmsg);

public slots:
    /**
     * @brief main entry point for other modules. Use this function to start the lexing-process.
     * checks if the given pointer isn't nullptr and then starts the lexing-function
     */
    bool start(QStringList *formulas);

};


#endif // LEXER_H
