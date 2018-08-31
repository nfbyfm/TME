
#include <QtTest>
#include <tst_lexer.h>
#include <tst_parser.h>
#include <tst_solver.h>
#include <tst_mathsolver.h>
#include <tst_mfformula.h>
#include <tst_mfpart.h>

//main testmethod for unit-tests and integration-test
int main(int argc, char** argv)
{
   int status = 0;
   {
       //Unit-Test for Lexer
       tst_Lexer tc;
       status |= QTest::qExec(&tc, argc, argv);
   }
   {
       //Unit-Test for Parser
       tst_Parser tc;
       status |= QTest::qExec(&tc, argc, argv);
   }
   {
       //Unit-Test for Solver
       tst_Solver tc;
       status |= QTest::qExec(&tc, argc, argv);
   }
   {
       //Test for whole solver-process
       tst_MathSolver tc;
       status |= QTest::qExec(&tc, argc, argv);
   }
   {
       //Test MFFormula-class
       tst_mfformula tc;
       status |= QTest::qExec(&tc, argc, argv);
   }
   {
       //Test MFPart
       tst_MFPart tc;
       status |= QTest::qExec(&tc, argc, argv);
   }
   return status;
}

