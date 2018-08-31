#include "tst_lexer.h"

tst_Lexer::tst_Lexer(QObject *parent) : QObject(parent)
{

}

void tst_Lexer::checkBrackets()
{

    Lexer *mLexer = new Lexer();
    int noOfLBrackets=0;
    int noOfRBrackets =0;
    int noOfUnclosedBrackets = 0;
    bool underscoreFound = false;

    mLexer->checkBrackets("(()))",noOfLBrackets,noOfRBrackets,noOfUnclosedBrackets, underscoreFound);
    QVERIFY(noOfLBrackets == 2);
    QVERIFY(noOfRBrackets == 3);
    QVERIFY(noOfUnclosedBrackets==1);

    mLexer->checkBrackets(")))((",noOfLBrackets,noOfRBrackets,noOfUnclosedBrackets,underscoreFound);
    QVERIFY(noOfLBrackets == 2);
    QVERIFY(noOfRBrackets == 3);
    QVERIFY(noOfUnclosedBrackets==5);

    mLexer->checkBrackets("(({[]})))",noOfLBrackets,noOfRBrackets,noOfUnclosedBrackets,underscoreFound);
    QVERIFY(noOfLBrackets == 4);
    QVERIFY(noOfRBrackets == 5);
    QVERIFY(noOfUnclosedBrackets==1);

    mLexer->checkBrackets("(({[}]([])})[)})",noOfLBrackets,noOfRBrackets,noOfUnclosedBrackets, underscoreFound);
    QVERIFY(noOfLBrackets == 7);
    QVERIFY(noOfRBrackets == 9);
    QVERIFY(noOfUnclosedBrackets==12);

    mLexer->checkBrackets("(({[qw3f}v3r]g(42r32r[_])})fg24lfr,ölced [)})",noOfLBrackets,noOfRBrackets,noOfUnclosedBrackets,underscoreFound);
    QVERIFY(noOfLBrackets == 7);
    QVERIFY(noOfRBrackets == 9);
    QVERIFY(noOfUnclosedBrackets==12);
    //qDebug()<<"Look mom i'm on TV!";
}

void tst_Lexer::checkStartFunction()
{
    Lexer *mLexer = new Lexer();

    QVERIFY(mLexer->start(nullptr) == false);

    QVERIFY(mLexer->start(new QStringList()) == true);

}

void tst_Lexer::checkLexing()
{
    Lexer *mLexer = new Lexer();

    QStringList *formulas = new QStringList();
    QList< QList<MToken *> > tokenList;
    tokenList.clear();

    QVERIFY(tokenList.isEmpty());

    tokenList = mLexer->lexing(formulas);
    QVERIFY(tokenList.isEmpty());

    formulas->append("(23*x)-2.3=65!");
    tokenList = mLexer->lexing(formulas);
    QVERIFY(!tokenList.isEmpty());

    MToken *tmpToken = tokenList.at(0).at(0);
    QVERIFY(tmpToken != nullptr);
    QVERIFY(tmpToken->getMObject()==nullptr);
    QVERIFY(tmpToken->getType() == MTokenType::PRIORITIZER);
    QVERIFY(tmpToken->getValue()=="(");

    tmpToken = nullptr;
    QVERIFY(tmpToken == nullptr);
    tmpToken = tokenList.at(0).at(1);
    QVERIFY(tmpToken != nullptr);
    QVERIFY(tmpToken->getMObject()==nullptr);
    QVERIFY(tmpToken->getType() == MTokenType::NUMBER);
    QVERIFY(tmpToken->getValue()=="23");


    tmpToken = nullptr;
    QVERIFY(tmpToken == nullptr);
    tmpToken = tokenList.at(0).at(2);
    QVERIFY(tmpToken != nullptr);
    QVERIFY(tmpToken->getMObject()==nullptr);
    QVERIFY(tmpToken->getType() == MTokenType::OPERATOR);
    QVERIFY(tmpToken->getValue()=="*");


    tmpToken = nullptr;
    QVERIFY(tmpToken == nullptr);
    tmpToken = tokenList.at(0).at(3);
    QVERIFY(tmpToken != nullptr);
    QVERIFY(tmpToken->getMObject()==nullptr);
    QVERIFY(tmpToken->getType() == MTokenType::VARIABLE);
    QVERIFY(tmpToken->getValue()=="x");

    tmpToken = nullptr;
    QVERIFY(tmpToken == nullptr);
    tmpToken = tokenList.at(0).at(4);
    QVERIFY(tmpToken != nullptr);
    QVERIFY(tmpToken->getMObject()==nullptr);
    QVERIFY(tmpToken->getType() == MTokenType::PRIORITIZER);
    QVERIFY(tmpToken->getValue()==")");


    tmpToken = nullptr;
    QVERIFY(tmpToken == nullptr);
    tmpToken = tokenList.at(0).at(5);
    QVERIFY(tmpToken != nullptr);
    QVERIFY(tmpToken->getMObject()==nullptr);
    QVERIFY(tmpToken->getType() == MTokenType::OPERATOR);
    QVERIFY(tmpToken->getValue()=="-");

    tmpToken = nullptr;
    QVERIFY(tmpToken == nullptr);
    tmpToken = tokenList.at(0).at(6);
    QVERIFY(tmpToken != nullptr);
    QVERIFY(tmpToken->getMObject()==nullptr);
    QVERIFY(tmpToken->getType() == MTokenType::NUMBER);
    QVERIFY(tmpToken->getValue()=="2.3");

    tmpToken = nullptr;
    QVERIFY(tmpToken == nullptr);
    tmpToken = tokenList.at(0).at(7);
    QVERIFY(tmpToken != nullptr);
    QVERIFY(tmpToken->getMObject()==nullptr);
    QVERIFY(tmpToken->getType() == MTokenType::COMPARATOR);
    QVERIFY(tmpToken->getValue()=="=");


    tmpToken = nullptr;
    QVERIFY(tmpToken == nullptr);
    tmpToken = tokenList.at(0).at(8);
    QVERIFY(tmpToken != nullptr);
    QVERIFY(tmpToken->getMObject()==nullptr);
    QVERIFY(tmpToken->getType() == MTokenType::NUMBER);
    QVERIFY(tmpToken->getValue()=="65");

    tmpToken = nullptr;
    QVERIFY(tmpToken == nullptr);
    tmpToken = tokenList.at(0).at(9);
    QVERIFY(tmpToken != nullptr);
    QVERIFY(tmpToken->getMObject()==nullptr);
    QVERIFY(tmpToken->getType() == MTokenType::COMPARATOR);
    QVERIFY(tmpToken->getValue()=="!");

}

void tst_Lexer::checkGetType()
{
    Lexer *mLexer = new Lexer();
    CType getType;

    getType = mLexer->getType('(');
    QVERIFY(getType == CType::LeftBracket);

    getType = mLexer->getType('[');
    QVERIFY(getType == CType::LeftBracket);

    getType = mLexer->getType('{');
    QVERIFY(getType == CType::LeftBracket);

    getType = mLexer->getType(')');
    QVERIFY(getType == CType::RightBracket);

    getType = mLexer->getType(']');
    QVERIFY(getType == CType::RightBracket);

    getType = mLexer->getType('}');
    QVERIFY(getType == CType::RightBracket);

    getType = mLexer->getType('+');
    QVERIFY(getType == CType::Operator);

    getType = mLexer->getType('-');
    QVERIFY(getType == CType::Operator);

    getType = mLexer->getType('*');
    QVERIFY(getType == CType::Operator);

    getType = mLexer->getType('/');
    QVERIFY(getType == CType::Operator);

    getType = mLexer->getType('^');
    QVERIFY(getType == CType::Operator);

    getType = mLexer->getType('<');
    QVERIFY(getType == CType::Comparator);
    getType = mLexer->getType('>');
    QVERIFY(getType == CType::Comparator);
    getType = mLexer->getType('=');
    QVERIFY(getType == CType::Comparator);
    getType = mLexer->getType('!');
    QVERIFY(getType == CType::Comparator);


    getType = mLexer->getType('.');
    QVERIFY(getType == CType::Dot);
    getType = mLexer->getType(',');
    QVERIFY(getType == CType::Dot);

    getType = mLexer->getType('0');
    QVERIFY(getType == CType::Digit);
    getType = mLexer->getType('1');
    QVERIFY(getType == CType::Digit);
    getType = mLexer->getType('2');
    QVERIFY(getType == CType::Digit);
    getType = mLexer->getType('3');
    QVERIFY(getType == CType::Digit);
    getType = mLexer->getType('4');
    QVERIFY(getType == CType::Digit);
    getType = mLexer->getType('5');
    QVERIFY(getType == CType::Digit);
    getType = mLexer->getType('6');
    QVERIFY(getType == CType::Digit);
    getType = mLexer->getType('7');
    QVERIFY(getType == CType::Digit);
    getType = mLexer->getType('8');
    QVERIFY(getType == CType::Digit);
    getType = mLexer->getType('9');
    QVERIFY(getType == CType::Digit);

    getType = mLexer->getType(' ');
    QVERIFY(getType == CType::Space);

    getType = mLexer->getType('\\');
    QVERIFY(getType == CType::Backslash);

    getType = mLexer->getType('\'');
    QVERIFY(getType == CType::UnderLine_Apostrophe);

    getType = mLexer->getType('_');
    QVERIFY(getType == CType::UnderLine_Apostrophe);

    getType = mLexer->getType('@');
    QVERIFY(getType == CType::Symbol);

    getType = mLexer->getType('#');
    QVERIFY(getType == CType::Symbol);

    getType = mLexer->getType('a');
    QVERIFY(getType == CType::Letter);

    getType = mLexer->getType('A');
    QVERIFY(getType == CType::Letter);

    getType = mLexer->getType('z');
    QVERIFY(getType == CType::Letter);

    getType = mLexer->getType('Z');
    QVERIFY(getType == CType::Letter);
}


