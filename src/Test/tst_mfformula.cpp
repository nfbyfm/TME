#include "tst_mfformula.h"

tst_mfformula::tst_mfformula(QObject *parent) : QObject(parent)
{

}


void tst_mfformula::checkSimplify()
{
    MFFormula *testFormula = new MFFormula;

    testFormula->simplify();
    QVERIFY(testFormula->getFormulaParts()->count() ==0);



    //create Formula
    MToken *tmpVariaToken = new MToken();

    MVariable *xVaria = new MVariable();        //x
    MVariable *yVaria = new MVariable();        //y
    MVariable *zVaria = new MVariable();        //z

    xVaria->setTextValue("x");
    yVaria->setTextValue("y");
    zVaria->setTextValue("z");

    double a_11 = 2;
    double a_12 = -1;
    double a_13 = 12;
    double a_21 = 4;

    double b_1 = -5;
    double b_2 = 10;

    MFPart *tmpPart = new MFPart();
    QList<MToken *> tokenList1;
    QList<MToken *> tokenList2;
    QList<MToken *> tokenList3;
    QList<MToken *> tokenList4;

    QList<MToken *> tokenListb1;
    QList<MToken *> tokenListb2;



    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tokenList1.append(new MToken(nullptr, QString::number(a_11), MTokenType::NUMBER));
    tokenList1.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "x", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(xVaria);
    tokenList1.append(tmpVariaToken);

    tmpPart->setTokenList(tokenList1);
    testFormula->appendList(tmpPart);


    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tokenList2.append(new MToken(nullptr, QString::number(a_12), MTokenType::NUMBER));
    tokenList2.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "y", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(yVaria);
    tokenList2.append(tmpVariaToken);

    tmpPart->setTokenList(tokenList2);
    testFormula->appendList(tmpPart);


    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tokenList3.append(new MToken(nullptr, QString::number(a_13), MTokenType::NUMBER));
    tokenList3.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "z", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(zVaria);
    tokenList3.append(tmpVariaToken);

    tmpPart->setTokenList(tokenList3);
    testFormula->appendList(tmpPart);

    tokenListb1.append(new MToken(nullptr, QString::number(b_1), MTokenType::NUMBER));
    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC);
    tmpPart->setTokenList(tokenListb1);
    testFormula->appendList(tmpPart);

    tokenListb2.append(new MToken(nullptr, QString::number(b_2), MTokenType::NUMBER));
    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC);
    tmpPart->setTokenList(tokenListb2);
    testFormula->appendList(tmpPart);

    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tokenList4.append(new MToken(nullptr, QString::number(a_21), MTokenType::NUMBER));
    tokenList4.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "x", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(xVaria);
    tokenList4.append(tmpVariaToken);

    tmpPart->setTokenList(tokenList4);
    testFormula->appendList(tmpPart);




    //test formula

    //qDebug()<<"before: " << testFormula->getSimplifiedFormulaString();
    QVERIFY(testFormula->getSimplifiedFormulaString()=="2*x + -1*y + 12*z + -5 + 10 + 4*x  = 0");

    testFormula->simplify();

    //qDebug()<<"simplified: " << testFormula->getSimplifiedFormulaString();
    QVERIFY(testFormula->getSimplifiedFormulaString()=="6*x + -1*y + 12*z + 5  = 0");
}
