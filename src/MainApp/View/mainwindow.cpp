/*
 * Class for Mainview
 * All Icons from: https://sourceforge.net/projects/openiconlibrary/, last viewed: 20.08.2018
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"


#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#include <QPrinter>
#if QT_CONFIG(printpreviewdialog)
#include <QPrintPreviewDialog>
#endif
#endif
#endif


/*
 * 0) Testing
 * 1) update Doxygen-Documentation
 *
 * 5) Welcome-Document:   kurzes How-To-Dokument erstellen
 *
 *
 *
 *
 *
 *
 * 1) Text:             Spellchecking:      http://wiki.qt.io/Spell-Checking-with-Hunspell
 *                                          https://github.com/manisandro/qtspell
 *                                          http://www.qtcentre.org/threads/38227-QTextEdit-with-hunspell-spell-checker-and-syntax-highlighter
 *                                          http://hunspell.github.io/
 *
 * 2) Document:         Properties:         Dialog
 *                                          struct for properties, -> use for Signals / Slots
 *                                          set-Functions for/from documentHandler
 *                                          default-Settings when creating new document
 *
 * 3) Edit:             search-function
 *                      search- & replace-function
 * 4) Images:           when using relative paths: what if the document hasn't been saved yet? Problems when printing!! -> Don't get rendered!
 *
 * 5) rendern von Mathematik-Formeln -> als Bild in html-Dokument einfügen?
 * 6) Setting:          show pdf after export
 * 7) Deploy:           https://github.com/daviddrell/visualsc/wiki/How-to-Deploy-a-Qt-5-Application-for-Windows
 * 8) use of Ribbon

fünf wichtige Punkte:
    - Dokument
    - Darstellung (Dokument & Mathematik)
    - Mathematik-Engine
    - Testing
    - Dokumentation

weitere wichtige Punkte:
    - Deployment
    - übersetzung der App
    - Zielsetzung erreicht
 */

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),  ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //non-essential functions / not needed / wanted for first Version
    /*
    ui->menu_Document->setEnabled(false);
    ui->menu_Document->setVisible(false);
    ui->action_properties->setEnabled(false);
    ui->action_properties->setVisible(false);
    */

    ui->actionsearch->setEnabled(false);
    ui->actionsearch->setVisible(false);
    ui->actionsearch_and_replace->setEnabled(false);
    ui->actionsearch_and_replace->setVisible(false);

    pageEdit = new PagesTextEdit(this);
    QTextDocument* doc = new QTextDocument;
    doc->setDefaultFont(QFont("Arial", 12));
    pageEdit->setDocument(doc);

    pageEdit->setPageFormat(QPageSize::A4);
    pageEdit->setPageMargins(QMarginsF(15, 15, 15, 15));
    pageEdit->setUsePageMode(true);
    pageEdit->setShowPageNumbers(false);
    //pageEdit->setPageNumbersAlignment(Qt::AlignBottom | Qt::AlignRight);

    setupWidgets();
    setupActions();
    setupTextToolBar();
    setupShortcuts();
    connectTextEdit();
    setupTextEdits();


}

MainWindow::~MainWindow()
{
    delete ui;
}

#define FILE_FUNCTIONS_EMITTER_START {


    void MainWindow::emitNewFile()
    {
        emit newFile(mathForm->getListofCurrentFormulas());
    }

    void MainWindow::emitOpenFile()
    {
        emit openFile(mathForm->getListofCurrentFormulas());
    }

    void MainWindow::emitSaveFile()
    {
        emit saveFile(mathForm->getListofCurrentFormulas());
    }

    void MainWindow::emitSaveAsFile()
    {
        emit saveFileAs(mathForm->getListofCurrentFormulas());
    }

    void MainWindow::emitCloseApp()
    {
        qDebug()<<"Closing application: check if unsaved changes are to be saved (handled by documenthandler).";
        emit exitApplication(mathForm->getListofCurrentFormulas());
    }

    void MainWindow::createNewFile()
    {
        emitNewFile();
    }


    void MainWindow::emitprintFile()
    {
        //QList <QPair<QString, QString> *> *searchReplaceList;
        emit printFile(mathForm->getListofCurrentFormulas());//searchReplaceList);
    }

    void MainWindow::emitshowPrintPreview()
    {
        emit showPrintPreview(mathForm->getListofCurrentFormulas());
    }

    void MainWindow::emitprintPDF()
    {
        emit printPDF(mathForm->getListofCurrentFormulas());
    }


#define FILE_FUNCTIONS_EMITTER_END }


#define SETUP_FUNCTIONS_START {

    void MainWindow::setupTextEdits()
    {
        //set default Font
        QFont textFont("Arial");
        textFont.setStyleHint(QFont::SansSerif);
        pageEdit->setFont(textFont);
        fontChanged(pageEdit->font());
        alignmentChanged(pageEdit->alignment());

        pageEdit->setFocus();

    }

    void MainWindow::setupWidgets()
    {
        this->setCentralWidget(pageEdit);

        ui->dockWidget_3->setWidget(ui->tabWidgetTools);

        imgForm = new Imageform(ui->tab_Images);
        QGridLayout * glayout = new QGridLayout(ui->tab_Images);
        glayout->setSpacing(0);
        glayout->setContentsMargins(0,0,0,0);
        glayout->addWidget(imgForm);
        ui->tab_Images->setLayout(glayout);
        imgForm->setEnabled(false);

        mathForm = new MathForm(ui->math_tab);
        QGridLayout *mlayout = new QGridLayout(ui->math_tab);
        mlayout->setSpacing(0);
        mlayout->setContentsMargins(0,0,0,0);
        mlayout->addWidget(mathForm);
        ui->math_tab->setLayout(mlayout);

        connect(mathForm,&MathForm::sendError, this, &MainWindow::recieveErrorMessage);
        connect(mathForm, &MathForm::addTextToDocument, pageEdit, &PagesTextEdit::insertText);
    }

    void MainWindow::setupActions()
    {

    //Actions from File-Menu
        connect(ui->action_New, &QAction::triggered, this, &MainWindow::emitNewFile);
        connect(ui->action_Open, &QAction::triggered, this, &MainWindow::emitOpenFile);
        connect(ui->action_Save, &QAction::triggered, this, &MainWindow::emitSaveFile);
        connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::emitSaveAsFile);

        /*
        connect(ui->action_Print, &QAction::triggered, this, &MainWindow::printFile);
        connect(ui->actionPrin_t_Preview, &QAction::triggered, this, &MainWindow::showPrintPreview);
        connect(ui->action_Export_pdf, &QAction::triggered, this, &MainWindow::printPDF);
        */

        connect(ui->action_Print, &QAction::triggered, this, &MainWindow::emitprintFile);
        connect(ui->actionPrin_t_Preview, &QAction::triggered, this, &MainWindow::emitshowPrintPreview);
        connect(ui->action_Export_pdf, &QAction::triggered, this, &MainWindow::emitprintPDF);

        connect(ui->action_Close, &QAction::triggered, this, &MainWindow::closeCurrentDocument);
        connect(ui->action_Exit, &QAction::triggered, this, &MainWindow::emitCloseApp);


    //search and replace-Actions
        connect(ui->actionsearch, &QAction::triggered, this, &MainWindow::searchText);
        connect(ui->actionsearch_and_replace, &QAction::triggered, this, &MainWindow::searchAndReplaceText);

    //edit-Actions
        #ifndef QT_NO_CLIPBOARD
            ui->action_cut->setEnabled(false);
            ui->action_copy->setEnabled(false);

            connect(QApplication::clipboard(), &QClipboard::dataChanged, this, &MainWindow::clipboardDataChanged);

            if (const QMimeData *md = QApplication::clipboard()->mimeData())
                ui->action_paste->setEnabled(md->hasText());
        #endif


    //Document-Actions
        //connect(ui->action_properties, &QAction::triggered, this, &MainWindow::editDocumentProperties);
        connect(mathForm, &MathForm::valuesChanged, this, &MainWindow::documentHasChanged);

    //Text-Font-Actions
        connect(ui->actionBold, &QAction::triggered, this, &MainWindow::textBold);
        connect(ui->actionItalic, &QAction::triggered, this, &MainWindow::textItalic);
        connect(ui->actionUnderline, &QAction::triggered, this, &MainWindow::textUnderline);
        connect(ui->actionOverline, &QAction::triggered, this, &MainWindow::textOverline);
        connect(ui->actionStrike, &QAction::triggered, this, &MainWindow::textStrikeOut);
        connect(ui->actionTextcolor, &QAction::triggered, this, &MainWindow::textColor);
        connect(ui->actionText_Background_Color, &QAction::triggered, this, &MainWindow::textBackgroundColor);
        connect(ui->action_font, &QAction::triggered, this, &MainWindow::textShowFontDialog);
        connect(ui->actionSubscript, &QAction::triggered, this, &MainWindow::textSubscript);
        connect(ui->actionSuperscript, &QAction::triggered, this, &MainWindow::textSuperscript);

    //Actions for Listing Text
        connect(ui->actionList_Standard, &QAction::triggered, this, &MainWindow::textList_Standard);
        connect(ui->actionList_Bullet_Disc, &QAction::triggered, this, &MainWindow::textList_Bullet_Disc);
        connect(ui->actionList_Bullet_Circle, &QAction::triggered, this, &MainWindow::textList_Bullet_Circle);
        connect(ui->actionList_Bullet_Square, &QAction::triggered, this, &MainWindow::textList_Bullet_Square);
        connect(ui->actionList_Ordered_List_Decimal, &QAction::triggered, this, &MainWindow::textList_Ordered_Decimal);
        connect(ui->actionList_Ordered_List_Alpha_lower, &QAction::triggered, this, &MainWindow::textList_Ordered_AlphaLower);
        connect(ui->actionList_Ordered_List_Alpha_upper, &QAction::triggered, this, &MainWindow::textList_Ordered_AlphaUpper);
        connect(ui->actionList_Ordered_List_Roman_lower, &QAction::triggered, this, &MainWindow::textList_Ordered_RomanLower);
        connect(ui->actionList_Ordered_List_Roman_upper, &QAction::triggered, this, &MainWindow::textList_Ordered_RomanUpper);


    //Image-Actions
        connect(ui->action_add_Image, &QAction::triggered, this, &MainWindow::insertImage);
        connect(ui->actionresize, &QAction::triggered, this, &MainWindow::showImageForm);
        connect(imgForm, &Imageform::resizeImage, this, &MainWindow::changeImage);

    //Table-Actions
        connect(ui->action_add_Table, &QAction::triggered, this, &MainWindow::insertTable);



    //Actions from Extra-Menu
        connect(ui->action_help, &QAction::triggered, this, &MainWindow::showHelpDialog);
        connect(ui->action_about, &QAction::triggered, this, &MainWindow::showAboutDialog);
        connect(ui->action_settings, &QAction::triggered, this, &MainWindow::showSettingsDialog);
    }

    void MainWindow::connectTextEdit()
    {
        connect(pageEdit, &QTextEdit::currentCharFormatChanged, this, &MainWindow::currentCharFormatChanged);
        connect(pageEdit, &QTextEdit::cursorPositionChanged, this, &MainWindow::cursorPositionChanged);
        connect(pageEdit->document(), &QTextDocument::modificationChanged, this, &QWidget::setWindowModified);

        connect(pageEdit->document(), &QTextDocument::modificationChanged, ui->action_Save, &QAction::setEnabled);

        connect(pageEdit->document(), &QTextDocument::undoAvailable, ui->action_undo, &QAction::setEnabled);
        connect(pageEdit->document(), &QTextDocument::redoAvailable, ui->action_redo, &QAction::setEnabled);

        connect(pageEdit, &QTextEdit::selectionChanged, this, &MainWindow::textSelectionChanged);


        ui->action_Save->setEnabled(pageEdit->document()->isModified());
        ui->action_undo->setEnabled(pageEdit->document()->isUndoAvailable());
        ui->action_redo->setEnabled(pageEdit->document()->isRedoAvailable());


        connect(ui->action_copy, &QAction::triggered, pageEdit, &QTextEdit::copy);
        connect(ui->action_cut, &QAction::triggered, pageEdit, &QTextEdit::cut);
        connect(ui->action_paste, &QAction::triggered, pageEdit, &QTextEdit::paste);
        connect(ui->action_undo, &QAction::triggered, pageEdit, &QTextEdit::undo);
        connect(ui->action_redo, &QAction::triggered, pageEdit, &QTextEdit::redo);


    }

    void MainWindow::setupShortcuts()
    {
        //set default Shortcuts
        ui->action_New->setShortcut(QKeySequence::New);
        ui->action_Open->setShortcut(QKeySequence::Open);
        ui->action_Save->setShortcut(QKeySequence::Save);
        ui->action_Print->setShortcut(QKeySequence::Print);

        ui->action_undo->setShortcut(QKeySequence::Undo);
        ui->action_redo->setShortcut(QKeySequence::Redo);
        ui->action_cut->setShortcut(QKeySequence::Cut);
        ui->action_copy->setShortcut(QKeySequence::Copy);
        ui->action_paste->setShortcut(QKeySequence::Paste);

        ui->actionBold->setShortcut(Qt::CTRL + Qt::Key_B);
        ui->actionItalic->setShortcut(Qt::CTRL + Qt::Key_I);
        ui->actionUnderline->setShortcut(Qt::CTRL + Qt::Key_U);

        ui->actionAlign_left->setShortcut(Qt::CTRL + Qt::Key_L);
        ui->actionAlign_center->setShortcut(Qt::CTRL + Qt::Key_E);
        ui->actionAlign_right->setShortcut(Qt::CTRL + Qt::Key_R);
        ui->actionAlign_justified->setShortcut(Qt::CTRL + Qt::Key_J);

        //ui->actionSave_As->setShortcut(QKeySequence::SaveAs);
        //ui->action_Close->setShortcut(QKeySequence::Close);
        //ui->action_Exit->setShortcut(QKeySequence::Close);

        //just for looks
        QFont italic;
        italic.setItalic(true);
        ui->actionItalic->setFont(italic);

        QFont bold;
        bold.setBold(true);
        ui->actionBold->setFont(bold);

        QFont underline;
        underline.setUnderline(true);
        ui->actionUnderline->setFont(underline);

    }

    void MainWindow::setupTextToolBar()
    {
        //create the Toolbar for Textmanipulation

        QToolBar *tb = addToolBar(tr("Format Actions"));
        tb->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
        addToolBarBreak(Qt::TopToolBarArea);
        addToolBar(tb);

        comboStyle = new QComboBox(tb);
        tb->addWidget(comboStyle);
        comboStyle->addItem(tr("Standard"));
        comboStyle->addItem(tr("Bullet List (Disc)"));
        comboStyle->addItem(tr("Bullet List (Circle)"));
        comboStyle->addItem(tr("Bullet List (Square)"));
        comboStyle->addItem(tr("Ordered List (Decimal)"));
        comboStyle->addItem(tr("Ordered List (Alpha lower)"));
        comboStyle->addItem(tr("Ordered List (Alpha upper)"));
        comboStyle->addItem(tr("Ordered List (Roman lower)"));
        comboStyle->addItem(tr("Ordered List (Roman upper)"));

        connect(comboStyle, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::textStyle);

        comboFont = new QFontComboBox(tb);
        tb->addWidget(comboFont);
        connect(comboFont, QOverload<const QString &>::of(&QComboBox::activated), this, &MainWindow::textFamily);

        comboSize = new QComboBox(tb);
        comboSize->setObjectName("comboSize");
        tb->addWidget(comboSize);
        comboSize->setEditable(true);

        const QList<int> standardSizes = QFontDatabase::standardSizes();
        foreach (int size, standardSizes)
            comboSize->addItem(QString::number(size));
        comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));

        connect(comboSize, QOverload<const QString &>::of(&QComboBox::activated), this, &MainWindow::textSize);

        tb->addAction(ui->actionBold);
        tb->addAction(ui->actionItalic);
        tb->addAction(ui->actionUnderline);
        tb->addAction(ui->actionStrike);
        tb->addAction(ui->actionOverline);
        tb->addAction(ui->actionSubscript);
        tb->addAction(ui->actionSuperscript);
        tb->addSeparator();

        // Make sure the alignLeft is always left of the alignRight
        QActionGroup *alignGroup = new QActionGroup(this);
        connect(alignGroup, &QActionGroup::triggered, this, &MainWindow::textAlign);

        if (QApplication::isLeftToRight())
        {
            alignGroup->addAction(ui->actionAlign_left);
            alignGroup->addAction(ui->actionAlign_center);
            alignGroup->addAction(ui->actionAlign_right);
        }
        else
        {
            alignGroup->addAction(ui->actionAlign_right);
            alignGroup->addAction(ui->actionAlign_center);
            alignGroup->addAction(ui->actionAlign_left);
        }
        alignGroup->addAction(ui->actionAlign_justified);

        tb->addActions(alignGroup->actions());
        tb->addSeparator();
        tb->addAction(ui->actionTextcolor);
        tb->addAction(ui->actionText_Background_Color);
        tb->addSeparator();
        tb->addAction(ui->action_font);
    }

#define SETUP_FUNCTIONS_END }


#define WINDOW_FUNCTIONS_START {

    void MainWindow::setMainWindowTitle(QString fileName, bool changesSaved)
    {

        QString newWindowTitle = QCoreApplication::applicationName();


        //show filename in title if the given is not empty or null
        if(!fileName.isNull())
        {
            if(!fileName.isEmpty())
            {
                QFileInfo fInfo(fileName);
                newWindowTitle += " - " + fInfo.baseName() + " [*]";
            }
            else
            {
                newWindowTitle += " [*]";
                qDebug()<<"Mainwindow: setMainWindowTitle: fileName is empty.";
            }
        }
        else
        {
            newWindowTitle += " [*]";
            qDebug()<<"Mainwindow: setMainWindowTitle: fileName is null.";
        }


        this->setWindowTitle(newWindowTitle);

        if(changesSaved)
            pageEdit->document()->setModified(false); //file has been loaded or similar scenario (load file or created new file)

        setWindowModified(pageEdit->document()->isModified());

    }

    void MainWindow::showStatusMessage(QString message, int timeoutMS)
    {
        this->statusBar()->showMessage(message, timeoutMS);
    }

    void MainWindow::changeStyleSheet(QString &style)
    {
        this->setStyleSheet(style);
    }


#define WINDOW_FUNCTIONS_END }


#define LANGUAGE_FUNCTIONS_START {

    //slot for changing the UI-Language (loaded from settings or triggered by other functions)
    void MainWindow::changeLanguage(QString language)
    {

        //search for fitting qm-file, switchtranslator
        QStringList qmFiles = findQmFiles();


        for (int i = 0; i < qmFiles.size(); ++i)
        {
            if (languageMatch(language, qmFiles[i]))
            {
                switchbaseTranslator(language);
                switchTranslator(m_translator, qmFiles[i]);
            }
        }

    }

    QStringList MainWindow::findQmFiles()
    {
        QString m_langPath = QApplication::applicationDirPath();
        m_langPath.append("/Resources/translations");
        QDir dir(m_langPath);
        QStringList fileNames = dir.entryList(QStringList("*.qm"), QDir::Files, QDir::Name);
        QMutableStringListIterator i(fileNames);

        while (i.hasNext())
        {
            i.next();
            i.setValue(dir.filePath(i.value()));
        }
        return fileNames;
    }

    QString MainWindow::languageName(const QString &qmFile)
    {
        QTranslator translator;
        translator.load(qmFile);

        return translator.translate("MainWindow", "English");
    }

    bool MainWindow::languageMatch(const QString& lang, const QString& qmFile)
    {
        //qmFile: i18n_xx.qm
        const QString prefix = "i18n_";
        const int langTokenLength = 2;
        return qmFile.midRef(qmFile.indexOf(prefix) + prefix.length(), langTokenLength) == lang.leftRef(langTokenLength);
    }

    void MainWindow::switchbaseTranslator(QString language)
    {
        qApp->removeTranslator(&m_baseTranslator);

        if(m_baseTranslator.load("qt_" + language, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        {
            qApp->installTranslator(&m_baseTranslator);
            this->ui->retranslateUi(this);
            mathForm->retranslateUI();
            imgForm->retranslateUI();
        }
        else
        {
            qDebug()<<"Could not change base-Translator to " << language;
        }
    }

    void MainWindow::switchTranslator(QTranslator &translator, const QString &filename)
    {
        // remove the old translator
        qApp->removeTranslator(&translator);

        // load the new translator
        if(translator.load(filename))
        {
            qApp->installTranslator(&translator);
            this->ui->retranslateUi(this);
            mathForm->retranslateUI();
            imgForm->retranslateUI();
        }
    }


    void MainWindow::changeEvent(QEvent* event)
    {
        if(event != nullptr) {
            switch(event->type())
            {
                // this event is send if a translator is loaded
                case QEvent::LanguageChange:
                    this->ui->retranslateUi(this);
                    break;

                    // this event is send, if the system, language changes
                case QEvent::LocaleChange:
                    {
                        QString defaultLang = QLocale::system().name();
                        changeLanguage(defaultLang);
                    }
                    break;
                default:
                    break;
            }
        }
        QMainWindow::changeEvent(event);
    }

    void MainWindow::dragEnterEvent(QDragEnterEvent *e)
    {
        if (e->mimeData()->hasUrls()) {
            e->acceptProposedAction();
        }
    }

    void MainWindow::dropEvent(QDropEvent *e)
    {
        foreach (const QUrl &url, e->mimeData()->urls())
        {
            QString fileName = url.toLocalFile();
            if(fileName.toLower().contains(".xml") || fileName.toLower().contains(".txt") || fileName.toLower().contains(".tex"))
            {
                //open file
                //open_File(fileName);
                return;
            }


        }
        this->ui->statusBar->showMessage(tr("Unable to open file."), 2000);
    }

#define LANGUAGE_FUNCTIONS_END }


#define TEXTMENU_FUNCTIONS_START {

    void MainWindow::alignmentChanged(Qt::Alignment a)
    {
        if (a & Qt::AlignLeft)
            ui->actionAlign_left->setChecked(true);
        else if (a & Qt::AlignHCenter)
            ui->actionAlign_center->setChecked(true);
        else if (a & Qt::AlignRight)
            ui->actionAlign_right->setChecked(true);
        else if (a & Qt::AlignJustify)
            ui->actionAlign_justified->setChecked(true);
        else if (a & QTextCharFormat::AlignSuperScript)
            ui->actionSuperscript->setChecked(true);
    }

    void MainWindow::fontChanged(const QFont &f)
    {
        comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
        comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
        ui->actionBold->setChecked(f.bold());
        ui->actionItalic->setChecked(f.italic());
        ui->actionUnderline->setChecked(f.underline());
        ui->actionOverline->setChecked(f.overline());
        ui->actionStrike->setChecked(f.strikeOut());
    }

    void MainWindow::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
    {
        QTextCursor cursor = pageEdit->textCursor();
        if (!cursor.hasSelection())
            cursor.select(QTextCursor::WordUnderCursor);
        cursor.mergeCharFormat(format);
        pageEdit->mergeCurrentCharFormat(format);
    }

    void MainWindow::clipboardDataChanged()
    {
    #ifndef QT_NO_CLIPBOARD
        if (const QMimeData *md = QApplication::clipboard()->mimeData())
            ui->action_paste->setEnabled(md->hasText());
    #endif
    }

    void MainWindow::cursorPositionChanged()
    {
        alignmentChanged(pageEdit->alignment());
        showImageForm();
    }

    void MainWindow::currentCharFormatChanged(const QTextCharFormat &format)
    {
        fontChanged(format.font());

        ui->actionSubscript->setChecked((format.verticalAlignment() == QTextCharFormat::AlignSubScript));
        ui->actionSuperscript->setChecked((format.verticalAlignment() == QTextCharFormat::AlignSuperScript));

    }

    void MainWindow::textAlign(QAction *a)
    {
        if (a == ui->actionAlign_left)
            pageEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
        else if (a == ui->actionAlign_center)
            pageEdit->setAlignment(Qt::AlignHCenter);
        else if (a == ui->actionAlign_right)
            pageEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
        else if (a == ui->actionAlign_justified)
            pageEdit->setAlignment(Qt::AlignJustify);
    }

    void MainWindow::textColor()
    {
        QColor col = QColorDialog::getColor(pageEdit->textColor(), this);
        if (!col.isValid())
            return;
        QTextCharFormat fmt;
        fmt.setForeground(col);
        mergeFormatOnWordOrSelection(fmt);
    }

    void MainWindow::textBackgroundColor()
    {
        QColor col = QColorDialog::getColor(pageEdit->textBackgroundColor(), this);
        if (!col.isValid())
            return;
        QTextCharFormat fmt;
        fmt.setBackground(col);
        mergeFormatOnWordOrSelection(fmt);
    }

    void MainWindow::textSubscript()
    {
        QTextCharFormat fmt;
        if(ui->actionSubscript->isChecked())
        {
            fmt.setVerticalAlignment(QTextCharFormat::AlignSubScript);
        }
        else
        {
            fmt.setVerticalAlignment(QTextCharFormat::AlignNormal);
        }

        mergeFormatOnWordOrSelection(fmt);
    }

    void MainWindow::textSuperscript()
    {
        QTextCharFormat fmt;
        if(ui->actionSuperscript->isChecked())
        {
            fmt.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
        }
        else
        {
            fmt.setVerticalAlignment(QTextCharFormat::AlignNormal);
        }

        mergeFormatOnWordOrSelection(fmt);
    }

    void MainWindow::textStyle(int styleIndex)
    {
        QTextCursor cursor = pageEdit->textCursor();

        if (styleIndex != 0)
        {
            QTextListFormat::Style style = QTextListFormat::ListDisc;

            switch (styleIndex)
            {
                default:
                case 1:
                    style = QTextListFormat::ListDisc;
                    break;
                case 2:
                    style = QTextListFormat::ListCircle;
                    break;
                case 3:
                    style = QTextListFormat::ListSquare;
                    break;
                case 4:
                    style = QTextListFormat::ListDecimal;
                    break;
                case 5:
                    style = QTextListFormat::ListLowerAlpha;
                    break;
                case 6:
                    style = QTextListFormat::ListUpperAlpha;
                    break;
                case 7:
                    style = QTextListFormat::ListLowerRoman;
                    break;
                case 8:
                    style = QTextListFormat::ListUpperRoman;
                    break;
            }

            cursor.beginEditBlock();

            QTextBlockFormat blockFmt = cursor.blockFormat();

            QTextListFormat listFmt;

            if (cursor.currentList())
            {
                listFmt = cursor.currentList()->format();
            }
            else
            {
                listFmt.setIndent(blockFmt.indent() + 1);
                blockFmt.setIndent(0);
                cursor.setBlockFormat(blockFmt);
            }

            listFmt.setStyle(style);

            cursor.createList(listFmt);

            cursor.endEditBlock();
        }
        else
        {
            //no List
            QTextBlockFormat bfmt;
            bfmt.setObjectIndex(0);
            cursor.mergeBlockFormat(bfmt);
        }
    }

    void MainWindow::textSize(const QString &p)
    {
        qreal pointSize = p.toDouble();
        if (p.toFloat() > 0) {
            QTextCharFormat fmt;
            fmt.setFontPointSize(pointSize);
            mergeFormatOnWordOrSelection(fmt);
        }
    }

    void MainWindow::textBold()
    {
        QTextCharFormat fmt;
        fmt.setFontWeight(ui->actionBold->isChecked() ? QFont::Bold : QFont::Normal);
        mergeFormatOnWordOrSelection(fmt);
    }

    void MainWindow::textUnderline()
    {
        QTextCharFormat fmt;
        fmt.setFontUnderline(ui->actionUnderline->isChecked());
        mergeFormatOnWordOrSelection(fmt);
    }

    void MainWindow::textItalic()
    {
        QTextCharFormat fmt;
        fmt.setFontItalic(ui->actionItalic->isChecked());
        mergeFormatOnWordOrSelection(fmt);
    }

    void MainWindow::textOverline()
    {
        QTextCharFormat fmt;
        fmt.setFontOverline(ui->actionOverline->isChecked());
        mergeFormatOnWordOrSelection(fmt);
    }

    void MainWindow::textStrikeOut()
    {
        QTextCharFormat fmt;
        fmt.setFontStrikeOut(ui->actionStrike->isChecked());
        mergeFormatOnWordOrSelection(fmt);
    }

    void MainWindow::textFamily(const QString &f)
    {
        QTextCharFormat fmt;
        fmt.setFontFamily(f);
        mergeFormatOnWordOrSelection(fmt);
    }

    void MainWindow::textShowFontDialog()
    {
        bool ok;
        QFont font = QFontDialog::getFont(&ok,this);
        if (ok)
        {
            //font is set to the font the user selected
            this->fontChanged(font);
            QTextCharFormat fmt;
            fmt.setFont(font);
            mergeFormatOnWordOrSelection(fmt);
        }
        else
        {
            //user canceled -> don't change or use the application-font QApplication::font();
        }
    }

    void MainWindow::textSelectionChanged()
    {
        bool selectionNotNull = (!pageEdit->textCursor().selection().isEmpty());

        ui->action_cut->setEnabled(selectionNotNull);
        ui->action_copy->setEnabled(selectionNotNull);
    }

    void MainWindow::showImageForm()
    {
        bool selectionNotNull = (!pageEdit->textCursor().selection().isEmpty());
        if(selectionNotNull)
        {
            QTextBlock currentBlock = pageEdit->textCursor().block();
            QTextBlock::iterator it;

            for (it = currentBlock.begin(); !(it.atEnd()); ++it)
            {
                QTextFragment fragment = it.fragment();

                if (fragment.isValid() && fragment.charFormat().isImageFormat())
                {
                    ui->tabWidgetTools->setCurrentIndex(1);
                    QTextImageFormat newImageFormat = fragment.charFormat().toImageFormat();
                    imgForm->setImageProperties(&newImageFormat);
                    break;
                 }
                 else
                 {
                     //disable / reset Image-Toolbox-Control
                     imgForm->setEnabled(false);
                 }
             }
        }
        else
           imgForm->setEnabled(false);
    }



#define TEXTMENU_FUNCTIONS_END }


#define TEXTLISTING_FUNCTIONS_START {
    void MainWindow::textList_Standard() {  textStyle(0); }
    void MainWindow::textList_Bullet_Disc() {   textStyle(1); }
    void MainWindow::textList_Bullet_Circle() {  textStyle(2); }
    void MainWindow::textList_Bullet_Square() {  textStyle(3); }
    void MainWindow::textList_Ordered_Decimal() {  textStyle(4); }
    void MainWindow::textList_Ordered_AlphaLower() {  textStyle(5); }
    void MainWindow::textList_Ordered_AlphaUpper() {  textStyle(6); }
    void MainWindow::textList_Ordered_RomanLower() {  textStyle(7); }
    void MainWindow::textList_Ordered_RomanUpper() {  textStyle(8); }
#define TEXTLISTING_FUNCTIONS_END    }


#define FILE_FUNCTIONS_START {

    void MainWindow::setDocument(QTextDocument *document)
    {
        pageEdit->setDocument(document);
        mathForm->resetTables();
    }

    void MainWindow::documentHasChanged()
    {
        pageEdit->document()->setModified(true);
    }

#define FILE_FUNCTIONS_END }


#define MISC_MENUFUNCTIONS_START {


    void MainWindow::insertImage()
    {
        QString file = QFileDialog::getOpenFileName(this, tr("Select an image"),".", tr("JPEG (*.jpg *jpeg)\n" "PNG (*.png)\n" "Bitmap Files (*.bmp)\n" "GIF (*.gif)\n" ));
        QUrl url("file:///" + file);
        QImage image = QImageReader ( file ).read();

        pageEdit->insertImage(url,image,0,0);
    }

    void MainWindow::insertTable()
    {
        //show Dialog. If successfull, give command to pageEdit.

        TableDialog *tDialog = new TableDialog(this);
        tDialog->setWindowTitle(tr("create new table"));

        if(tDialog->exec()==QDialog::Accepted)
        {
            pageEdit->insertTable(tDialog->getNumberOfColumns(),tDialog->getNumberOfRows(), tDialog->getColumnWidth(), tDialog->getAlignment());
        }

    }

    void MainWindow::changeImage(double width, double height, QString newFilename, bool useNewFile)
    {
        //resize currently selected Image according to user input or replace the whole image
        if(useNewFile)
        {
            //remove current file and add image (with width- and heigt- values)

            QTextCursor cursor = pageEdit->textCursor();
            cursor.select(QTextCursor::LineUnderCursor);
            cursor.removeSelectedText();


            QUrl url("file:///" + newFilename);
            QImage image = QImageReader ( newFilename ).read();

            pageEdit->insertImage(url,image, width,height);
            //qDebug()<<"new filename: " << newFilename << "    url:"<< url;
        }
        else
        {
            //simply resize the currently selected image
            QTextBlock currentBlock = pageEdit->textCursor().block();
            QTextBlock::iterator it;

            for (it = currentBlock.begin(); !(it.atEnd()); ++it)
            {
                QTextFragment fragment = it.fragment();

                 if (fragment.isValid())
                 {

                     if(fragment.charFormat().isImageFormat ())
                     {
                          QTextImageFormat newImageFormat = fragment.charFormat().toImageFormat();

                          newImageFormat.setWidth(width);
                          newImageFormat.setHeight(height);

                          if (newImageFormat.isValid())
                          {
                              QTextCursor helper = pageEdit->textCursor();

                              helper.setPosition(fragment.position());
                              helper.setPosition(fragment.position() + fragment.length(), QTextCursor::KeepAnchor);
                              helper.setCharFormat(newImageFormat);
                              break;
                          }


                      }
                  }
               }
        }

    }

    void MainWindow::searchText()
    {
        FindDialog *fdia = new FindDialog(this, true);
        fdia->setWindowTitle(tr("Search"));
        //show modal -> can't click / use other View-Components (Dialogs / Mainwindow)
        fdia->exec();
    }

    void MainWindow::searchAndReplaceText()
    {
        FindDialog *fdia = new FindDialog(this, false);
        fdia->setWindowTitle(tr("Search and replace"));
        //non-Modal (can click on other Dialogs / Mainwindow)
        fdia->show();
    }


    void MainWindow::editDocumentProperties()
    {
        TextDocumentPropertyDialog *pDialog = new TextDocumentPropertyDialog(this);
        pDialog->setWindowTitle(tr("Documentproperties"));
        pDialog->show();
    }

    void  MainWindow::recieveErrorMessage(ErrorMessage *msg)
    {
        emit sendErrorMessage(msg);
    }

#define MISC_MENUFUNCTIONS_END }


#define MATH_FUNCTIONS_START {

    void MainWindow::on_action_solve_triggered()
    {
        //check if there are formulas in the math-Form. If not, inform the user.
        if(mathForm->numberOfFormulas() <= 0)
        {
            showStatusMessage(tr("There are no formulas in the list to solve."), 2000);
        }
        else
        {
            emit solveMath(mathForm->getListofCurrentFormulas());
        }
        ui->tabWidgetTools->setCurrentIndex(0);
    }

    void MainWindow::on_actiondetect_formulas_triggered()
    {
        //check if there are formulas in the math-Form. Ask if they should be overwritten or the list should be appended
        //already defined variables will be compared with formulas. unused / varaibles not tied to formulas will be left alone (marked as unsolved)

        if(pageEdit->document()->toPlainText().isEmpty())
        {
            showStatusMessage(tr("There are no formulas in the text to solve."), 2000);
        }
        else
        {

            if(mathForm->numberOfFormulas() > 0)
            {
                //show Dialog
                const QMessageBox::StandardButton ret = QMessageBox::question(this, QCoreApplication::applicationName(), tr("There are already formulas defined.\nDo you want to overwrite them?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

                if (ret == QMessageBox::Yes)
                {
                    ui->tabWidgetTools->setCurrentIndex(0);
                    emit solveMath(pageEdit->toPlainText(), true, mathForm->getListofCurrentFormulas());
                }
                else if (ret == QMessageBox::No)
                {
                    ui->tabWidgetTools->setCurrentIndex(0);
                    emit solveMath(pageEdit->toPlainText(), false, mathForm->getListofCurrentFormulas());
                }
            }
            else
            {
                ui->tabWidgetTools->setCurrentIndex(0);
                emit solveMath(pageEdit->toPlainText(), true, mathForm->getListofCurrentFormulas());
            }
        }
    }


    void MainWindow::resetMathData()
    {
        mathForm->resetTables();
    }


    void  MainWindow::updateMathData(QList<MFormula*> formulaList, QList<MVariable*> variableList)
    {
        mathForm->setMathData(formulaList,variableList);
    }
#define MATH_FUNCTIONS_END }


