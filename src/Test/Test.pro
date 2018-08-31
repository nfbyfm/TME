QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    Control/MathEngine/lexer.h \
    Control/MathEngine/mathengine.h \
    Control/MathEngine/msolver.h \
    Control/MathEngine/parser.h \
    Libraries/alglib_3_14_0/alglib.h \
    Libraries/alglib_3_14_0/alglibinternal.h \
    Libraries/alglib_3_14_0/alglibmisc.h \
    Libraries/alglib_3_14_0/ap.h \
    Libraries/alglib_3_14_0/dataanalysis.h \
    Libraries/alglib_3_14_0/diffequations.h \
    Libraries/alglib_3_14_0/fasttransforms.h \
    Libraries/alglib_3_14_0/integration.h \
    Libraries/alglib_3_14_0/interpolation.h \
    Libraries/alglib_3_14_0/linalg.h \
    Libraries/alglib_3_14_0/optimization.h \
    Libraries/alglib_3_14_0/solvers.h \
    Libraries/alglib_3_14_0/specialfunctions.h \
    Libraries/alglib_3_14_0/statistics.h \
    Libraries/alglib_3_14_0/stdafx.h \
    Model/Document/mapage.h \
    Model/Document/mpage.h \
    Model/Document/mpagetemplate.h \
    Model/Math/mathmodel.h \
    Model/Math/mfformula.h \
    Model/Math/mformula.h \
    Model/Math/mfpart.h \
    Model/Math/mfparttype.h \
    Model/Math/mtoken.h \
    Model/Math/mtokentype.h \
    Model/Math/mvariable.h \
    Model/mainmodel.h \
    tst_lexer.h \
    tst_parser.h \
    tst_solver.h \
    tst_mathsolver.h \
    tst_mfformula.h \
    tst_mfpart.h

SOURCES += \
    Control/MathEngine/lexer.cpp \
    Control/MathEngine/mathengine.cpp \
    Control/MathEngine/msolver.cpp \
    Control/MathEngine/parser.cpp \
    Libraries/alglib_3_14_0/alglibinternal.cpp \
    Libraries/alglib_3_14_0/alglibmisc.cpp \
    Libraries/alglib_3_14_0/ap.cpp \
    Libraries/alglib_3_14_0/dataanalysis.cpp \
    Libraries/alglib_3_14_0/diffequations.cpp \
    Libraries/alglib_3_14_0/fasttransforms.cpp \
    Libraries/alglib_3_14_0/integration.cpp \
    Libraries/alglib_3_14_0/interpolation.cpp \
    Libraries/alglib_3_14_0/linalg.cpp \
    Libraries/alglib_3_14_0/optimization.cpp \
    Libraries/alglib_3_14_0/solvers.cpp \
    Libraries/alglib_3_14_0/specialfunctions.cpp \
    Libraries/alglib_3_14_0/statistics.cpp \
    Model/Document/mapage.cpp \
    Model/Document/mpage.cpp \
    Model/Document/mpagetemplate.cpp \
    Model/Math/mathmodel.cpp \
    Model/Math/mfformula.cpp \
    Model/Math/mformula.cpp \
    Model/Math/mfpart.cpp \
    Model/Math/mtoken.cpp \
    Model/Math/mvariable.cpp \
    Model/mainmodel.cpp \
    tst_lexer.cpp \
    main.cpp \
    tst_parser.cpp \
    tst_solver.cpp \
    tst_mathsolver.cpp \
    tst_mfformula.cpp \
    tst_mfpart.cpp

SUBDIRS += \
    Test.pro

