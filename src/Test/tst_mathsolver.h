#ifndef TST_MATHSOLVER_H
#define TST_MATHSOLVER_H

#include <QObject>
#include <QTest>

#define private public
#include <Control/MathEngine/lexer.h>
#include <Control/MathEngine/parser.h>
#include <Control/MathEngine/msolver.h>
#include <Control/MathEngine/mathengine.h>

class tst_MathSolver : public QObject
{
    Q_OBJECT
public:
    explicit tst_MathSolver(QObject *parent = nullptr);

signals:

private slots:
    void checkWholeMathAlgorithm();
};

#endif // TST_MATHSOLVER_H
