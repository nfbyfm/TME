#ifndef TST_PARSER_H
#define TST_PARSER_H

#include <QObject>
#include <QTest>

#define private public
#include <Control/MathEngine/parser.h>

class tst_Parser : public QObject
{
    Q_OBJECT
public:
    tst_Parser(QObject *parent = nullptr);

signals:

private slots:
    void checkpadZeroNumber();
    void checkSolveSimpleEquation();
    void checkConstantTokenToNumeric();
    void checkVariableTokenNumeric();
    void checkNumberTokenReciproque();
    void checkStartParsing();
};

#endif // TST_PARSER_H
