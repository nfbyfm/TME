#include "tst_mathsolver.h"

tst_MathSolver::tst_MathSolver(QObject *parent) : QObject(parent)
{

}

void tst_MathSolver::checkWholeMathAlgorithm()
{
    //create Lexer, Parser and Solver, setup formulas as QStringList and connect results
    //check variable-values

    Lexer *mLexer = new Lexer();
    Parser *mParser = new Parser();
    MSolver *mSolver = new MSolver();
    MathEngine *mEngine = new MathEngine();

    QStringList *formulaList = new QStringList;
    formulaList->append("1*x+2.5*y-7*z=-12");
    formulaList->append("10*x-3*z=0");
    formulaList->append("-5*x+5*y+10*z=10");

    //
    QList< QList<MToken *> > tokenList;
    QList <MFormula *> f_List;
    QList <MVariable *> v_List;

    f_List.clear();
    v_List.clear();
    tokenList.clear();

    QVERIFY(tokenList.isEmpty());

    tokenList = mLexer->lexing(formulaList);
    QVERIFY(tokenList.count()==3);

    QList <MFFormula *> * mfflist = mParser->startParsing(tokenList, f_List, v_List);

    QVERIFY(mfflist->count()==3);
    QVERIFY(f_List.count()==3);
    QVERIFY(v_List.count()==3);

    mEngine->simplifyEquations(mfflist);
    QVERIFY(mfflist->count()==3);

    bool retVal = false;
    retVal = mSolver->startSolving(mfflist);

    QVERIFY(retVal==true);

    /*
    qDebug()<<"xValue = " << v_List.at(0)->getNumericValue();
    qDebug()<<"yValue = " << v_List.at(1)->getNumericValue();
    qDebug()<<"zValue = " << v_List.at(2)->getNumericValue();
    */

    QVERIFY((v_List.at(0)->getNumericValue() - 0.465753) < 0.001);
    QVERIFY((v_List.at(1)->getNumericValue() + 0.639269) < 0.001);
    QVERIFY((v_List.at(2)->getNumericValue() - 1.55251) < 0.001);
}
