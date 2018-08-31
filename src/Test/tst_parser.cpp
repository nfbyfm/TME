#include "tst_parser.h"

tst_Parser::tst_Parser(QObject *parent) : QObject(parent)
{

}

void tst_Parser::checkpadZeroNumber()
{
    Parser *mParser = new Parser();
    QString result="";

    QVERIFY(result == "");

    result = mParser->padZeroNumber(0);
    QVERIFY(result == "000000");

    result = mParser->padZeroNumber(-1);
    QVERIFY(result == "0000-1");

    result = mParser->padZeroNumber(100);
    QVERIFY(result == "000100");

    result = mParser->padZeroNumber(10009000);
    QVERIFY(result == "10009000");
}

void tst_Parser::checkSolveSimpleEquation()
{
    Parser *mParser = new Parser();
    bool returnValue = false;

    //check null-pointer argument
    QVERIFY(returnValue==false);
    returnValue = mParser->solveSimpleEquation(nullptr);
    QVERIFY(returnValue==false);

    //check if an equation gets solved correctly
    MFormula *tmpFormula = new MFormula();
    QList <MToken *> tokenList;
    tokenList.clear();
    MVariable *tmpVariable = new MVariable(nullptr);
    MToken *tmpVarToken = new MToken(nullptr,"a",MTokenType::VARIABLE);
    tmpVarToken->setMObject(tmpVariable);
    tokenList.append(tmpVarToken);
    tokenList.append(new MToken(nullptr,"=",MTokenType::COMPARATOR));
    tokenList.append(new MToken(nullptr,"3.135",MTokenType::NUMBER));
    tmpFormula->setTokenList(tokenList);

    returnValue = mParser->solveSimpleEquation(tmpFormula);

    QVERIFY(returnValue == true);
    QVERIFY(tmpVariable->getSolved()==true);
    QVERIFY((tmpVariable->getNumericValue() - 3.135) < 0.001);

    //check invalid equation
    tmpFormula = new MFormula();

    tokenList.clear();
    tmpVariable = new MVariable(nullptr);
    tmpVarToken = new MToken(nullptr,"a",MTokenType::VARIABLE);
    tmpVarToken->setMObject(tmpVariable);

    tokenList.append(tmpVarToken);
    tokenList.append(new MToken(nullptr,"=",MTokenType::COMPARATOR));
    tokenList.append(new MToken(nullptr,"3.135",MTokenType::NUMBER));
    tokenList.append(new MToken(nullptr,"+",MTokenType::OPERATOR));
    tokenList.append(new MToken(nullptr,"135",MTokenType::NUMBER));
    tmpFormula->setTokenList(tokenList);

    returnValue = mParser->solveSimpleEquation(tmpFormula);

    QVERIFY(returnValue == false);
    QVERIFY(tmpVariable->getSolved()==false);
    QVERIFY((tmpVariable->getNumericValue() - 0) < 0.001);

}



void tst_Parser::checkConstantTokenToNumeric()
{
    //MToken *constantTokenToNumeric(QString constValue);
    Parser *mParser = new Parser();
    MToken *retVal = nullptr;

    QVERIFY(retVal == nullptr);
    retVal = mParser->constantTokenToNumeric("pi");
    QVERIFY(retVal != nullptr);
    QVERIFY(retVal->getType() == MTokenType::NUMBER);
    QVERIFY(retVal->getValue()==QString::number(M_PI));

    retVal = nullptr;
    QVERIFY(retVal == nullptr);
    retVal = mParser->constantTokenToNumeric("pqwe");
    QVERIFY(retVal != nullptr);
    QVERIFY(retVal->getType() == MTokenType::NUMBER);
    QVERIFY(retVal->getValue()==QString::number(1));

    retVal = nullptr;
    QVERIFY(retVal == nullptr);
    retVal = mParser->constantTokenToNumeric("");
    QVERIFY(retVal != nullptr);
    QVERIFY(retVal->getType() == MTokenType::NUMBER);
    QVERIFY(retVal->getValue()==QString::number(1));

}

void tst_Parser::checkVariableTokenNumeric()
{
    Parser *mParser = new Parser();
    MToken *retVal = nullptr;
    MToken *testToken = nullptr;

    //check nullptr argument
    QVERIFY(retVal == nullptr);
    retVal = mParser->variableTokenNumeric(testToken);
    QVERIFY(retVal == nullptr);

    testToken = new MToken();
    retVal = mParser->variableTokenNumeric(testToken);
    QVERIFY(retVal == testToken);

    MVariable *testVairalbe=nullptr;
    testToken->setMObject(testVairalbe);
    retVal = mParser->variableTokenNumeric(testToken);
    QVERIFY(retVal == testToken);

    testVairalbe = new MVariable();
    testToken->setMObject(testVairalbe);
    testVairalbe->setSolved(true);
    testVairalbe->setOverdetermined(false);
    testVairalbe->setNumericValue(45.87);

    retVal = mParser->variableTokenNumeric(testToken);
    QVERIFY(retVal != testToken);
    QVERIFY(retVal->getType()==MTokenType::NUMBER);
    QVERIFY(retVal->getValue()==QString::number(45.87));

}

void tst_Parser::checkNumberTokenReciproque()
{
    //checks if a division by number is supposed to take place
    //void Parser::numberTokenReciproque(MToken* tokenPointer, MFPart *tmpPart)
    Parser *mParser = new Parser();

    MToken *testToken = nullptr;

    MFPart *tmpPart = nullptr;

    QList <MToken *> tokenList;
    tokenList.clear();

    QVERIFY(testToken == nullptr);
    QVERIFY(tmpPart == nullptr);
    mParser->numberTokenReciproque(testToken, tmpPart);
    QVERIFY(testToken == nullptr);
    QVERIFY(tmpPart == nullptr);

    tmpPart = new MFPart();
    tokenList.append(new MToken(nullptr, "1", MTokenType::NUMBER));
    tokenList.append(new MToken(nullptr, "/", MTokenType::OPERATOR));
    tmpPart->setTokenList(tokenList);


    //check with only one nullptr argument
    QVERIFY(tmpPart->getTokenList().count() == 2);
    mParser->numberTokenReciproque(testToken, tmpPart);
    QVERIFY(tmpPart->getTokenList().count() == 2);



    //check division-function
    testToken = new MToken(nullptr, "2.0", MTokenType::NUMBER);

    mParser->numberTokenReciproque(testToken, tmpPart); //should replace "1/2" with "1*0.5"

    QVERIFY(tmpPart->getTokenList().count() == 3);
    QVERIFY(tmpPart->getTokenList().at(1)->getType()==MTokenType::OPERATOR);
    QVERIFY(tmpPart->getTokenList().at(1)->getValue()=="*");
    QVERIFY(tmpPart->getTokenList().at(2)->getType()==MTokenType::NUMBER);
    QVERIFY(tmpPart->getTokenList().at(2)->getValue()=="0.5");

}

void tst_Parser::checkStartParsing()
{
    //
    Parser *mParser = new Parser();
    QList< QList<MToken *> > tf_list;
    QList <MFormula *> f_List;
    QList <MVariable *> v_List;

    tf_list.clear();
    f_List.clear();
    v_List.clear();

    QList<MToken *> formula1;
    QList<MToken *> formula2;

    formula1.append(new MToken(nullptr, "a", MTokenType::VARIABLE));
    formula1.append(new MToken(nullptr, "=", MTokenType::COMPARATOR));
    formula1.append(new MToken(nullptr, "23.5", MTokenType::NUMBER));
    formula1.append(new MToken(nullptr, "+", MTokenType::OPERATOR));
    formula1.append(new MToken(nullptr, "3", MTokenType::NUMBER));
    formula1.append(new MToken(nullptr, "*", MTokenType::OPERATOR));
    formula1.append(new MToken(nullptr, "b", MTokenType::VARIABLE));

    formula2.append(new MToken(nullptr, "125", MTokenType::NUMBER));
    formula2.append(new MToken(nullptr, "=", MTokenType::COMPARATOR));
    formula2.append(new MToken(nullptr, "3.14", MTokenType::NUMBER));
    formula2.append(new MToken(nullptr, "-", MTokenType::OPERATOR));
    formula2.append(new MToken(nullptr, "a", MTokenType::VARIABLE));
    formula2.append(new MToken(nullptr, "/", MTokenType::OPERATOR));
    formula2.append(new MToken(nullptr, "5", MTokenType::NUMBER));


    tf_list.append(formula1);
    tf_list.append(formula2);

    QList <MFFormula *> * mfflist = mParser->startParsing(tf_list, f_List, v_List);

    /*
    QString formulasRes = "Formulas:   ";
    for(int i = 0; i< f_List.count(); i++)
        formulasRes += " " + f_List.at(i)->toString() + "   ";
    qDebug()<< formulasRes;


    QString variablesRes = "Variables:    ";
    for(int u =0; u< v_List.count();u++)
        variablesRes += " " + v_List.at(u)->getTextValue() + " ; ";
    qDebug()<<variablesRes;

    QString mffValues="MFFValues:    |";
    for(int k =0; k< mfflist->count(); k++)
        mffValues += mfflist->at(k)->getSimplifiedFormulaString() + "|    |";
    qDebug()<<mffValues;
    */

    //
    QVERIFY(mfflist!=nullptr);
    QVERIFY(!f_List.isEmpty());
    QVERIFY(!v_List.isEmpty());

    QVERIFY(mfflist->count()==2);
    QVERIFY(f_List.count()==2);
    QVERIFY(v_List.count()==2);

    QVERIFY(f_List.at(0)->toString() == "a=23.5+3*b");
    QVERIFY(f_List.at(1)->toString() == "125=3.14-a/5");

    QVERIFY(v_List.at(0)->getTextValue()=="a");
    QVERIFY(v_List.at(1)->getTextValue()=="b");

    QVERIFY(mfflist->at(0)->getNumberOfVariables() == 2);
    QVERIFY(mfflist->at(1)->getNumberOfVariables() == 1);

    QVERIFY(mfflist->at(0)->getSimplifiedFormulaString()=="a + -(23.5) + -(3*b)  = 0");
    QVERIFY(mfflist->at(1)->getSimplifiedFormulaString()=="125 + -(3.14) + -(-1*a*0.2)  = 0");


}




