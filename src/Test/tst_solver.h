#ifndef TST_SOLVER_H
#define TST_SOLVER_H

#include <QObject>
#include <QTest>

#define private public
#include <Control/MathEngine/msolver.h>

class tst_Solver : public QObject
{
    Q_OBJECT
public:
    explicit tst_Solver(QObject *parent = nullptr);

signals:

private slots:
    void testSolverMethod();
};

#endif // TST_SOLVER_H
