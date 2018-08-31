#ifndef TST_MFFORMULA_H
#define TST_MFFORMULA_H

#include <QObject>
#include <QTest>

#define private public
#include <Model/Math/mfformula.h>

class tst_mfformula : public QObject
{
    Q_OBJECT
public:
    explicit tst_mfformula(QObject *parent = nullptr);

signals:

private slots:
    void checkSimplify();
};

#endif // TST_MFFORMULA_H
