#ifndef TST_LEXER_H
#define TST_LEXER_H

#include <QObject>
#include <QTest>
#include <QDebug>

#define private public      // eeevil
#include <Control/MathEngine/lexer.h>

class tst_Lexer : public QObject
{
    Q_OBJECT
public:
    tst_Lexer(QObject *parent = nullptr);

signals:

private slots:
    void checkBrackets();
    void checkStartFunction();
    void checkLexing();
    void checkGetType();
};

#endif // TST_LEXER_H
