#include "tst_solver.h"

tst_Solver::tst_Solver(QObject *parent) : QObject(parent)
{

}

void tst_Solver::testSolverMethod()
{
    MSolver *mSolver = new MSolver();
    QList <MFFormula *> *formulaList = nullptr;
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
    double a_22 = 8;
    double a_23 = -4;

    double a_31 = -1;
    double a_32 = 8;
    double a_33 = 0;

    double b_1 = -5;
    double b_2 = 10;
    double b_3 = 12;

    //qDebug()<<"staring solving with nullptr";
    QVERIFY( mSolver->startSolving(nullptr) == false);
    formulaList = new QList <MFFormula *>();
    //
    MFFormula *tmpFormula = new MFFormula();

    MFPart *tmpPart = new MFPart();
    QList<MToken *> tokenList1;
    QList<MToken *> tokenList2;
    QList<MToken *> tokenList3;
    QList<MToken *> tokenList4;
    QList<MToken *> tokenList5;
    QList<MToken *> tokenList6;
    QList<MToken *> tokenList7;
    QList<MToken *> tokenList8;
    QList<MToken *> tokenList9;

    QList<MToken *> tokenListb1;
    QList<MToken *> tokenListb2;
    QList<MToken *> tokenListb3;


    //qDebug()<<"equation 1";
    //equation 1
    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tokenList1.append(new MToken(nullptr, QString::number(a_11), MTokenType::NUMBER));
    tokenList1.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "x", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(xVaria);
    tokenList1.append(tmpVariaToken);

    tmpPart->setTokenList(tokenList1);
    tmpFormula->appendList(tmpPart);


    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tokenList2.append(new MToken(nullptr, QString::number(a_12), MTokenType::NUMBER));
    tokenList2.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "y", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(yVaria);
    tokenList2.append(tmpVariaToken);

    tmpPart->setTokenList(tokenList2);
    tmpFormula->appendList(tmpPart);


    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tokenList3.append(new MToken(nullptr, QString::number(a_13), MTokenType::NUMBER));
    tokenList3.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "z", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(zVaria);
    tokenList3.append(tmpVariaToken);

    tmpPart->setTokenList(tokenList3);
    tmpFormula->appendList(tmpPart);


    tokenListb1.append(new MToken(nullptr, QString::number(b_1), MTokenType::NUMBER));
    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC);
    tmpPart->setTokenList(tokenListb1);
    tmpFormula->appendList(tmpPart);


    formulaList->append(tmpFormula);
    tmpFormula = new MFFormula();

    //qDebug()<<"define equation 2";
    //equation 2
    tokenList4.append(new MToken(nullptr, QString::number(a_21), MTokenType::NUMBER));
    tokenList4.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "x", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(xVaria);
    tokenList4.append(tmpVariaToken);

    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tmpPart->setTokenList(tokenList4);
    tmpFormula->appendList(tmpPart);


    tokenList5.append(new MToken(nullptr, QString::number(a_22), MTokenType::NUMBER));
    tokenList5.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "y", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(yVaria);
    tokenList5.append(tmpVariaToken);

    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tmpPart->setTokenList(tokenList5);
    tmpFormula->appendList(tmpPart);


    tokenList6.append(new MToken(nullptr, QString::number(a_23), MTokenType::NUMBER));
    tokenList6.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "z", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(zVaria);
    tokenList6.append(tmpVariaToken);

    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tmpPart->setTokenList(tokenList6);
    tmpFormula->appendList(tmpPart);

    tokenListb2.append(new MToken(nullptr, QString::number(b_2), MTokenType::NUMBER));
    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC);
    tmpPart->setTokenList(tokenListb2);
    tmpFormula->appendList(tmpPart);

    formulaList->append(tmpFormula);
    tmpFormula = new MFFormula();


    //qDebug()<<"define equation 2";
    //equation 3
    tokenList7.append(new MToken(nullptr, QString::number(a_31), MTokenType::NUMBER));
    tokenList7.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "x", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(xVaria);
    tokenList7.append(tmpVariaToken);

    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tmpPart->setTokenList(tokenList7);
    tmpFormula->appendList(tmpPart);


    tokenList8.append(new MToken(nullptr, QString::number(a_32), MTokenType::NUMBER));
    tokenList8.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "y", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(yVaria);
    tokenList8.append(tmpVariaToken);

    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tmpPart->setTokenList(tokenList8);
    tmpFormula->appendList(tmpPart);


    tokenList9.append(new MToken(nullptr, QString::number(a_33), MTokenType::NUMBER));
    tokenList9.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    tmpVariaToken = new MToken(nullptr, "z", MTokenType::VARIABLE);
    tmpVariaToken->setMObject(zVaria);
    tokenList9.append(tmpVariaToken);

    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC_AND_VARIABLE);
    tmpPart->setTokenList(tokenList9);
    tmpFormula->appendList(tmpPart);

    tokenListb3.append(new MToken(nullptr, QString::number(b_3), MTokenType::NUMBER));
    tmpPart = new MFPart();
    tmpPart->setGType(MFPartType::NUMERIC);
    tmpPart->setTokenList(tokenListb3);
    tmpFormula->appendList(tmpPart);

    formulaList->append(tmpFormula);

/*
    for(int i = 0; i< formulaList->count();i++)
        qDebug()<< formulaList->at(i)->getSimplifiedFormulaString();
*/


    bool result = false;
    //qDebug()<<"starting solving";
    result = mSolver->startSolving(formulaList);
    //qDebug()<<"result: "<<result;
    QVERIFY(result==true);
    QVERIFY((xVaria->getNumericValue() - 0.562963) < 0.001);
    QVERIFY((yVaria->getNumericValue() + 1.42963) < 0.001);
    QVERIFY((zVaria->getNumericValue() - 0.203704) < 0.001);
}
