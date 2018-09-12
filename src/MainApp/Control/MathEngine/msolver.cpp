#include "msolver.h"

MSolver::MSolver(QObject *parent) : QObject(parent)
{

}

bool MSolver::startSolving(QList <MFFormula*> *formulaList)
{
    bool retVal = false;

    if(formulaList !=nullptr)
    {
        //create Matrix A and the vectors x and b out of the formulaList

        QList <MVariable* > *variableList = new QList <MVariable *>(); //list of Variables ->  x-Vector

        QList<QPair<double,MVariable*> *> *coeficientList = nullptr;

        //create VariableList (to get size of Matrix)
        for(int i = 0; i<formulaList->count();i++)
        {
            //formulaList->at(i)->getPairList();
            coeficientList = formulaList->at(i)->getCoeficientList();

            //for each pair: add Variable to list if not already in there
            if(coeficientList!=nullptr)
            {
                for(int u =0; u < coeficientList->count(); u++)
                {
                    QPair<double,MVariable*> *tmpVal = coeficientList->at(u);

                    if(tmpVal->second !=nullptr)
                    {
                        bool variableFoundInList = false;

                        for(int k=0; k<variableList->count();k++)
                        {
                            if(tmpVal->second == variableList->at(k))
                            {
                                //already in List
                                variableFoundInList=true;
                                break;
                            }
                        }

                        if(variableFoundInList==false)
                        {
                            //add to List
                            variableList->append(tmpVal->second);
                            //setcoeficient
                        }
                    }
                }
            }
        }

        //check if enought equation for number of variables
        int numberOfVariables = variableList->count();
        int numberOfEquations = formulaList->count();

        qDebug()<<"MathSolver: number of Equations: " << numberOfEquations << "  number of variables: " << numberOfVariables;

        if(numberOfEquations<numberOfVariables)
        {
             emit sendError(new ErrorMessage(this,ERROR_ID::MATHSOLVER_NotEnoughEquations,nullptr));
        }
        else if (numberOfEquations>numberOfVariables)
        {
             emit sendError(new ErrorMessage(this,ERROR_ID::MATHSOLVER_TooManyEquations,nullptr));
        }
        else
        {
            //right amount of equations for number of variables -> create Matrix

            //setup Matrix and vectors
            int iN = numberOfVariables;
            aMatrix.setlength(iN, iN);
            bVector.setlength(iN);
            xVector.setlength(iN);

            //zero the matrix and the vectors
            for(int x = 0; x<iN; x++)
            {
                for(int y =0; y<iN;y++)
                {
                    aMatrix(x,y) = 0;
                }
                bVector(x)=0;
                xVector(x)=0;
            }



            //fill matrix and bVector

            for(int row =0; row < numberOfEquations; row++)
            {
                //formulaList->at(i)->getPairList();
                coeficientList = formulaList->at(row)->getCoeficientList();

                //for each pair: add Variable to list if not already in there
                if(coeficientList!=nullptr)
                {
                    for(int u =0; u < coeficientList->count(); u++)
                    {
                        QPair<double,MVariable*> *tmpVal = coeficientList->at(u);

                        if(tmpVal->second !=nullptr)
                        {
                            bool variableFoundInList = false;

                            for(int k=0; k<variableList->count();k++)
                            {
                                if(tmpVal->second == variableList->at(k))
                                {
                                    //already in List
                                    variableFoundInList=true;
                                    //set coeficient in matrix
                                    aMatrix(row,k) = tmpVal->first;
                                    break;
                                }
                            }

                            if(variableFoundInList==false)
                            {
                                //add to List
                                variableList->append(tmpVal->second);
                                aMatrix(row,variableList->count()-1) = tmpVal->first;
                                //setcoeficient
                                qDebug()<<"MathSolver: Variable "<< tmpVal->second->getTextValue() << "not in List yet. Should not be possible!!!";
                            }
                        }
                        else
                        {
                            //add double-value to bVector
                            bVector(row) = (-1)*tmpVal->first;
                        }
                    }
                }
            }

            /*
            qDebug()<<"MathSolver: Ax = b is to be solved:";
            qDebug()<<"A = " << QString::fromStdString(aMatrix.tostring(1));
            qDebug()<<"b = " << QString::fromStdString(bVector.tostring(1));
            qDebug()<<"x = " << QString::fromStdString(xVector.tostring(2));
            */

            alglib::ae_int_t info;
            alglib::densesolverreport report;

            //run the solver
            alglib::rmatrixsolve(aMatrix,iN,bVector,info,report,xVector,alglib::xdefault);

            /*
            qDebug()<<"\nsMathSolver: Ax = b has been solved.";
            qDebug()<<"A = " << QString::fromStdString(aMatrix.tostring(1));
            qDebug()<<"b = " << QString::fromStdString(bVector.tostring(1));
            qDebug()<<"x = " << QString::fromStdString(xVector.tostring(2));
            */

            // reunite Solution with Variables
            qDebug()<<"MathSolver: write Values into Variables. Length of x-Vector: " << xVector.length();
            for(int row = 0; row < xVector.length(); row++)
            {
                variableList->at(row)->setNumericValue(xVector(row));
                variableList->at(row)->setSolved(true);

                qDebug()<<"Variable " << variableList->at(row)->getTextValue() << " = " << variableList->at(row)->getNumericValue();
            }
            retVal = true;
        }
    }


    return retVal;

}
