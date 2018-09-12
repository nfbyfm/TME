#-------------------------------------------------
#
# Project created by QtCreator 2018-06-19T21:04:30
#
#-------------------------------------------------

QT       += core gui

#requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TME
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    View/mainwindow.h \
    View/Dialogs/errorlistdialog.h \
    View/Dialogs/settingsdialog.h \
    View/UI-Elements/PageMetrics.h \
    View/UI-Elements/PagesTextEdit.h \
    View/UI-Elements/filewindow.h \
    View/Dialogs/finddialog.h \
    View/UI-Elements/imageform.h \
    View/Dialogs/textdocumentpropertydialog.h \
    View/UI-Elements/mathform.h \
    View/Dialogs/tabledialog.h \
#Controller
    Control/controller.h \
    Control/settingshandler.h \
    Control/FaultHandler/metaerror.h \
    Control/settings_enums.h \
    Control/documenthandler.h \
#Fault-Handler
    Control/FaultHandler/error_enums.h \
    Control/FaultHandler/errormessage.h \
    Control/FaultHandler/faulthandler.h \
#Math-Engine
    Control/MathEngine/mathengine.h \
    Control/MathEngine/lexer.h \
    Control/MathEngine/parser.h \
    Control/MathEngine/msolver.h \ 
    Control/MathEngine/presolver.h \
#Model
    Model/mainmodel.h \
#Math-Model
    Model/Math/mathmodel.h \
    Model/Math/mtoken.h \
    Model/Math/mtokentype.h \
    Model/Math/mformula.h \
    Model/Math/mvariable.h \
    Model/Math/mfpart.h \
    Model/Math/mfformula.h \
    Model/Math/mfparttype.h \
#external Libraries
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
    Libraries/alglib_3_14_0/alglib.h








SOURCES += \
        main.cpp \
#Views
    View/mainwindow.cpp \
    View/Dialogs/errorlistdialog.cpp \
    View/Dialogs/settingsdialog.cpp \
    View/UI-Elements/PageMetrics.cpp \
    View/UI-Elements/PagesTextEdit.cpp \
    View/UI-Elements/filewindow.cpp \
    View/Dialogs/finddialog.cpp \
    View/Dialogs/tabledialog.cpp \
    View/Dialogs/textdocumentpropertydialog.cpp \
    View/UI-Elements/imageform.cpp \
    View/UI-Elements/mathform.cpp \
#Controllers
    Control/controller.cpp \
    Control/settingshandler.cpp \
    Control/FaultHandler/metaerror.cpp \
    Control/documenthandler.cpp \
#Fault-Handler
    Control/FaultHandler/faulthandler.cpp \
    Control/FaultHandler/errormessage.cpp \
#Math-Engine
    Control/MathEngine/mathengine.cpp \
    Control/MathEngine/lexer.cpp \
    Control/MathEngine/parser.cpp \
    Control/MathEngine/msolver.cpp \
    Control/MathEngine/presolver.cpp \
#Model
#Math-Model
    Model/Math/mathmodel.cpp \
    Model/mainmodel.cpp \
    Model/Math/mtoken.cpp \
    Model/Math/mformula.cpp \
    Model/Math/mvariable.cpp \
    Model/Math/mfpart.cpp \
    Model/Math/mfformula.cpp \
#external Libraries
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
    Libraries/alglib_3_14_0/statistics.cpp










FORMS += \
    View/mainwindow.ui \
    View/Dialogs/errorlistdialog.ui \
    View/Dialogs/settingsdialog.ui \
    View/Dialogs/finddialog.ui \
    View/UI-Elements/imageform.ui \
    View/Dialogs/textdocumentpropertydialog.ui \
    View/UI-Elements/mathform.ui \
    View/Dialogs/tabledialog.ui


RESOURCES += \
    Resources/i18n.qrc \
    Resources/icons.qrc \
    Resources/stylesheets.qrc




win32:RC_ICONS += Resources/images_and_icons/mainIcon/icon3a.ico


TRANSLATIONS = Resources/translations/i18n_en.ts  Resources/translations/i18n_de.ts
