#include "tst_mfpart.h"

tst_MFPart::tst_MFPart(QObject *parent) : QObject(parent)
{

}
void tst_MFPart::checkSimplify()
{
    MFPart *testPart = new MFPart();

    testPart->simplifyList();
    QVERIFY(testPart->getTokenList().count()==0);



    MToken *tmpVariaToken = new MToken();

    MVariable *xVaria = new MVariable();        //x
    xVaria->setTextValue("x");

    double a_11 = 2;
    double a_12 = -1;


    QList<MToken *> tokenList1;

    testPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tokenList1.append(new MToken(nullptr, QString::number(a_11), MTokenType::NUMBER));
    tokenList1.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "x", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(xVaria);
    tokenList1.append(tmpVariaToken);
    tokenList1.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tokenList1.append(new MToken(nullptr, QString::number(a_12), MTokenType::NUMBER));

    testPart->setTokenList(tokenList1);

    //qDebug()<<"Part before simplification: "  << testPart->tokenListToString();

    QVERIFY(testPart->tokenListToString()=="2*x*-1");
    testPart->simplifyList();

    //qDebug()<<"Part after simplification: "  << testPart->tokenListToString();
    QVERIFY(testPart->tokenListToString()=="-2*x");
}

void tst_MFPart::checkMultiplicationError()
{
    MFPart *testPart = new MFPart();
    bool retVal = false;

    retVal = testPart->multiplError();
    QVERIFY(retVal == false);

    MToken *tmpVariaToken = new MToken();

    MVariable *xVaria = new MVariable();        //x
    MVariable *yVaria = new MVariable();        //y

    xVaria->setTextValue("x");
    yVaria->setTextValue("y");

    double a_11 = 2;


    QList<MToken *> tokenList1;

    testPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tokenList1.append(new MToken(nullptr, QString::number(a_11), MTokenType::NUMBER));
    tokenList1.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "x", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(xVaria);
    tokenList1.append(tmpVariaToken);
    tokenList1.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "y", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(yVaria);
    tokenList1.append(tmpVariaToken);

    testPart->setTokenList(tokenList1);


    QVERIFY(testPart->tokenListToString()=="2*x*y");

    retVal = testPart->multiplError();
    QVERIFY(retVal == true);
    //qDebug()<<"Part contains multiplication of multiple varaibles: "  << retVal;

}

void tst_MFPart::checkDivisionError()
{
    MFPart *testPart = new MFPart();
    bool retVal = false;

    retVal = testPart->divisionError();
    QVERIFY(retVal == false);

    MToken *tmpVariaToken = new MToken();

    MVariable *xVaria = new MVariable();        //x
    MVariable *yVaria = new MVariable();        //y

    xVaria->setTextValue("x");
    yVaria->setTextValue("y");

    double a_11 = 2;


    QList<MToken *> tokenList1;

    testPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tokenList1.append(new MToken(nullptr, QString::number(a_11), MTokenType::NUMBER));
    tokenList1.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "x", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(xVaria);
    tokenList1.append(tmpVariaToken);
    tokenList1.append(new MToken(nullptr, "/", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "y", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(yVaria);
    tokenList1.append(tmpVariaToken);

    testPart->setTokenList(tokenList1);


    QVERIFY(testPart->tokenListToString()=="2*x/y");

    retVal = testPart->divisionError();
    QVERIFY(retVal == true);
    //qDebug()<<"Part contains division with a varaible in the denominator: "  << retVal;

}
