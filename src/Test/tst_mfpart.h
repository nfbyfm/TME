#ifndef TST_MFPART_H
#define TST_MFPART_H

#include <QObject>
#include <QTest>

//#define private public
#include <Model/Math/mfpart.h>

class tst_MFPart : public QObject
{
    Q_OBJECT
public:
    explicit tst_MFPart(QObject *parent = nullptr);

signals:

private slots:
    void checkSimplify();
    void checkMultiplicationError();
    void checkDivisionError();
};

#endif // TST_MFPART_H
