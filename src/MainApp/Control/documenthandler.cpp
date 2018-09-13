#include "documenthandler.h"

//Controller for Models
DocumentHandler::DocumentHandler(QObject *parent) : QObject(parent)
{
    mModel = new MathModel(this);
    tDocument = new QTextDocument(this);
    documentForPrint = new QTextDocument(this);

    fileName = tr("untitled");

    //setup Autosave-Timer
    autoSaveTimer = new QTimer(this);
    autoSaveTimer->setSingleShot(false);
    autoSaveTimer->stop();
    showpdfAfterExport=false;
    connect(autoSaveTimer, &QTimer::timeout, this, &DocumentHandler::autoSave);
}

bool DocumentHandler::documentHasBeenSaved()
{
    return (!tDocument->isModified());
}

//save, new, open-functions
#define DOCUMENT_OPERATION_FUNCTIONS_START {

void DocumentHandler::newDocument(QStringList * formulaList)
{
    //create new, empty document (check if document is still open -> save first?)
    if (maybeSave(formulaList))
    {
        fileName = tr("untitled");
        tDocument = new QTextDocument(this);

        mModel = new MathModel(this);

        emit updateMathModel(mModel);

        connect(tDocument, &QTextDocument::modificationChanged, this, &DocumentHandler::documentChanged);

        emit setTextDocument(tDocument);
        emit updateWindowTitle(fileName, true);
    }
}


//open single document
void DocumentHandler::openDocument(QStringList * formulaList)
{
    if(maybeSave(formulaList)) //first: check if a document is still open -> ask to save first
    {
        QFileDialog fileDialog(nullptr, tr("Open File..."));
        fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
        fileDialog.setFileMode(QFileDialog::ExistingFile);
        fileDialog.setMimeTypeFilters(QStringList() << "text/html" << "text/plain" << "text/xml");

        if (fileDialog.exec() == QDialog::Accepted)
        {
            const QString fn = fileDialog.selectedFiles().first();


            //check if already open
            if(fileName==fn)
            {
                //do nothing / show message that document is already open
                emit sendError(new ErrorMessage(this,ERROR_ID::DOCHANDLER_FileAlreadyOpen,nullptr));
            }
            else if (fn.toLower().contains(".xml"))
            {
                loadProjectFile(fn);
            }
            else
            {
                loadFile(fn);
            }

        }
    }
}

void DocumentHandler::openKnownFile(QFileInfo fileName)
{
    loadFile(fileName.filePath());
}


void DocumentHandler::loadFile(QString fName)
{
    this->fileName = fName;

    if (!QFile::exists(fileName))
    {
        emit sendError(new ErrorMessage(this,ERROR_ID::DOCHANDLER_FileDoesNotExist,new MetaError(this,new QStringList({fileName}))));
        return;
    }

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
    {
        emit sendError(new ErrorMessage(this,ERROR_ID::DOCHANDLER_FileCanNotBeOpened,new MetaError(this,new QStringList({fileName}))));
        return;
    }

    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);

    QString formulas="";

    if (Qt::mightBeRichText(str))
    {
        if (str.contains("</html>"))
        {
            QString tmp = str;
            formulas = str.remove(0, str.lastIndexOf("</html>")+7);
            //qDebug()<<formulas;
            str = tmp;
        }
        tDocument->setHtml(str);
    }
    else
    {
        str = QString::fromLocal8Bit(data);
        tDocument->setPlainText(str);
        formulas = str;
    }

    QFileInfo rFileInfo(fileName);

    //for support of relative paths as well (e.g. <img src="testimages/2107ad_by_f1x_2-dcea2lk.jpg" width="450" height="396.21" />) will be displayed as well
#ifdef Q_WS_WIN
  tDocument->setMetaInformation( QTextDocument::DocumentUrl, rFileInfo.absolutePath() + "/" );
#else
  tDocument->setMetaInformation( QTextDocument::DocumentUrl, "file:" + rFileInfo.absolutePath() + "/");
#endif

    emit updateMathModel(mModel);
    emit setTextDocument(tDocument);
    emit updateWindowTitle(fileName, true);
    emit solveMath(formulas,true, new QStringList());


}

void DocumentHandler::loadProjectFile(QString fName)
{

    QFile file(fName);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        //emit error that file could not be opened
        //qDebug()<<"xml file could not be opened. Permission denied.";
        emit sendError(new ErrorMessage(this,ERROR_ID::DOCHANDLER_FileCanNotBeOpened,new MetaError(this,new QStringList({fName}))));
    }
    else
    {
        QXmlStreamReader xmlReader(&file);

        QString contents="";
        QStringList *possibleFormulas = new QStringList();


        if(xmlReader.readNextStartElement())
        {
            if(xmlReader.name() == QLatin1String("tmeProjectFile") && xmlReader.attributes().value(versionAttribute()) == QLatin1String("1.0"))
            {
                //start reading / parsing

                while(!xmlReader.atEnd())
                {
                    if(xmlReader.isStartElement())
                    {
                        if(xmlReader.name()=="TEXTDOCUMENT")
                        {
                            while(!xmlReader.atEnd())
                            {
                                if(xmlReader.isCharacters())
                                {
                                    xmlReader.readNext();
                                }
                                else if(xmlReader.isEndElement())
                                {
                                    xmlReader.readNext();
                                    break;
                                }
                                else if(xmlReader.name()=="Content")
                                {
                                    //get contents
                                    contents = xmlReader.readElementText();
                                    xmlReader.readNext();
                                    break;
                                }
                                else
                                {
                                    xmlReader.readNext();
                                }
                            }

                        }
                        else if(xmlReader.name()=="MATHDOCUMENT")
                        {
                            while(!xmlReader.atEnd())
                            {
                                if(xmlReader.isCharacters())
                                {
                                    xmlReader.readNext();
                                }
                                else if(xmlReader.isEndElement())
                                {
                                    xmlReader.readNext();
                                    break;
                                }
                                else if(xmlReader.name()=="Formula")
                                {
                                    //get contents
                                    possibleFormulas->append(xmlReader.readElementText());
                                    xmlReader.readNext();
                                    //break;
                                }
                                else
                                {
                                    xmlReader.readNext();
                                }
                            }
                        }
                        else
                        {
                            xmlReader.readNext();
                        }
                    }
                    else
                    {
                        xmlReader.readNext();
                    }
                }

                if(xmlReader.hasError())
                {
                    //qDebug()<<"xml-Reader has Error: " << xmlReader.errorString();
                    emit sendError(new ErrorMessage(this,ERROR_ID::DOCHANDLER_XMLError,new MetaError(this,new QStringList({xmlReader.errorString()}))));
                }
                else if(file.error() != QFile::NoError)
                {
                    //qDebug()<<"File has Error: " << file.errorString();
                    emit sendError(new ErrorMessage(this,ERROR_ID::DOCHANDLER_FileError,new MetaError(this,new QStringList({file.errorString()}))));

                }
                else
                {
                    //qDebug()<<"Projectfile loaded successfully. List of Formulas: " << possibleFormulas->join(", ");
                    //qDebug()<<"Documentcontent: " << contents;

                    tDocument->setHtml(contents);
                    //mModel->recieveListOfFormulas(possibleFormulas);
                    this->fileName = fName;

                    QString formul = possibleFormulas->join(" \n");

                    emit updateMathModel(mModel);
                    emit setTextDocument(tDocument);
                    emit solveMath(formul,true,new QStringList());
                    emit updateWindowTitle(fileName, true);
                }

            }
            else
            {
                //emit error
                //xmlReader.raiseError(QObject::tr("The file is not an TME version 1.0 file."));
                emit sendError(new ErrorMessage(this,ERROR_ID::DOCHANDLER_WrongXMLVersion,new MetaError(this,new QStringList({"1.0"}))));
            }
        }
        file.close();


    }
}



bool DocumentHandler::saveFile(QStringList * formulaList)
{

    if (fileName.isEmpty())
        return saveFileAs(formulaList);
    if (fileName.startsWith(QStringLiteral(":/")) || fileName == tr("untitled"))
        return saveFileAs(formulaList);

    QString formulas = "";



    //find out which type of file shal be saved
    QMimeDatabase mimeDatabase;
    const QFileInfo fi(fileName);
    const QMimeType mimeType = mimeDatabase.mimeTypeForFile(fi);

    if (!mimeType.isValid())
    {
        //show error message, save anyway
        qDebug()<<"DocumentHanlder: SaveFile: unknown Mimetype. Save file as plain text.";
    }


    if(formulaList != nullptr)
    {
        for(int i = 0; i< formulaList->count(); i++)
            formulas += "$" + formulaList->at(i) + "$\n";
    }


    bool success = false;

    if(mimeType.inherits("text/html"))
    {
        success = true;

        QFile file(fileName);

        // Trying to open in WriteOnly and Text mode
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            emit sendError(new ErrorMessage(this,ERROR_ID::DOCHANDLER_CouldNotSaveFile, new MetaError(this,new QStringList({QDir::toNativeSeparators(fileName)}))));
            success = false;
        }
        else
        {

            QString filecontent = tDocument->toHtml() + "\n<!-- \n" + formulas + "\n-->";

            QTextStream out(&file);
            out << filecontent.toUtf8();
            file.flush();
            file.close();
        }
    }
    else if (mimeType.inherits("application/xml"))
    {
        success = saveProjectFile(formulaList);
    }
    else if(mimeType.inherits("application/vnd.oasis.opendocument.text"))
    {
        //save as odt
        QTextDocumentWriter writer(fileName);
        success = writer.write(tDocument);
    }
    else
    {
        //save as plain textfile
        success = true;

        QFile file(fileName);


        // Trying to open in WriteOnly and Text mode
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            emit sendError(new ErrorMessage(this,ERROR_ID::DOCHANDLER_CouldNotSaveFile, new MetaError(this,new QStringList({QDir::toNativeSeparators(fileName)}))));
            success = false;
        }
        else
        {


            QString filecontents = tDocument->toPlainText().toUtf8() + "\n" + formulas;

            QTextStream out(&file);
            out << filecontents;
            file.flush();
            file.close();
        }


    }


    if (success)
    {
       tDocument->setModified(false);
       emit showStatusMessage(tr("File '%1' has been saved.").arg(QDir::toNativeSeparators(fileName)),2000);
       emit updateWindowTitle(fileName, true);
    }
    else
    {
        emit showStatusMessage(tr("Could not write to file '%1'").arg(QDir::toNativeSeparators(fileName)),2000);
        emit updateWindowTitle(fileName, false);
    }
    return success;
}



bool DocumentHandler::saveFileAs(QStringList * formulaList)
{

    QFileDialog fileDialog(nullptr, tr("Save as..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList mimeTypes;
    mimeTypes << "text/html" << "text/plain" << "text/xml" << "application/vnd.oasis.opendocument.text";
    fileDialog.setMimeTypeFilters(mimeTypes);

    fileDialog.setDefaultSuffix("html");

    if (fileDialog.exec() == QDialog::Accepted)
    {
        const QString fn = fileDialog.selectedFiles().first();
        setCurrentFileName(fn);
        return saveFile(formulaList);
    }
    else
        return false;

}

bool DocumentHandler::saveProjectFile(QStringList * formulaList)
{
    //save settings like Pagesize and Margins, Headers / footers
    //relative or absolute paths for images. Relative paths for Images: problem when printing!
    bool success = true;

    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeDTD(QStringLiteral("<!DOCTYPE tme>"));
    xmlWriter.writeStartElement(QStringLiteral("tmeProjectFile"));
    xmlWriter.writeAttribute(versionAttribute(), QStringLiteral("1.0"));

    xmlWriter.writeStartElement("TEXTDOCUMENT");
    xmlWriter.writeTextElement("Content", tDocument->toHtml().toUtf8() );

    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("MATHDOCUMENT");

    for(int i=0; i< formulaList->count(); i++)
        xmlWriter.writeTextElement("Formula", "$ " + formulaList->at(i) + " $");

    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    file.close();

    return success;
}


//true if document has unsaved elements
bool DocumentHandler::maybeSave(QStringList * formulaList)
{
    if (!tDocument->isModified())
        return true;


    const QMessageBox::StandardButton ret = QMessageBox::warning(nullptr, QCoreApplication::applicationName(), tr("The document has been modified.\nDo you want to save your changes?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    if (ret == QMessageBox::Save)
        return saveFile(formulaList);
    else if (ret == QMessageBox::Cancel)
        return false;
    return true;
}

void DocumentHandler::setCurrentFileName(const QString &fiName)
{
    this->fileName = fiName;

    tDocument->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = QFileInfo(fileName).fileName();

    emit updateWindowTitle(fileName, true);
}



#define DOCUMENT_OPERATION_FUNCTIONS_END }


#define FILE_PRINT_FUNCTIONS_START {

    //create another, temporary document and replace all $link()$-Entries with the fitting Math-Values -> export / print that document

    void DocumentHandler::filePrintPdf()
    {
    #ifndef QT_NO_PRINTER
    //! [0]
        QFileDialog fileDialog(nullptr, tr("Export PDF"));
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
        fileDialog.setDefaultSuffix("pdf");

        if (fileDialog.exec() == QDialog::Accepted)
        {

            QString fileName = fileDialog.selectedFiles().first();
            QPrinter printer(QPrinter::HighResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);
            //printer.setResolution(96);
            printer.setPageSize(QPrinter::A4);
            printer.setPageMargins(0, 0, 0, 0, QPrinter::Millimeter);
            //printer.setPageMargins(15, 15, 15, 15, QPrinter::Millimeter);//printer.setPageMargins(12, 16, 12, 20, QPrinter.Millimeter)
            //document.setPageSize(QSizeF(printer.pageRect().size()))
            //print(document.pageSize(), printer.resolution(), printer.pageRect())
            createPrintDocument();
            //documentForPrint->setPageSize(QSizeF(printer.pageRect().size()));
            documentForPrint->setDocumentMargin(0);
            documentForPrint->print(&printer);

            emit showStatusMessage(tr("File '%1' has been exported").arg(QDir::toNativeSeparators(fileName)),2000);

            if(showpdfAfterExport)
            {
                qDebug()<<"show the pdf after the export -> openUrl " << ("file:///" + fileName);
                QDesktopServices::openUrl(QUrl("file:///" + fileName, QUrl::TolerantMode));
            }
        }
    //! [0]
    #endif
    }

    void DocumentHandler::filePrint()
    {
    #if QT_CONFIG(printdialog)
        QPrinter printer(QPrinter::HighResolution);
        QPrintDialog *dlg = new QPrintDialog(&printer, nullptr);
        //if (pageEdit->textCursor().hasSelection())
        //    dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
        dlg->setWindowTitle(tr("Print Document"));

        if (dlg->exec() == QDialog::Accepted)
        {
            createPrintDocument();
            documentForPrint->print(&printer);
        }
        delete dlg;
    #endif
    }

    void DocumentHandler::filePrintPreview()
    {
    #if QT_CONFIG(printpreviewdialog)
        QPrinter printer(QPrinter::HighResolution);
        QPrintPreviewDialog preview(&printer, nullptr);
        connect(&preview, &QPrintPreviewDialog::paintRequested, this, &DocumentHandler::printPreview);
        preview.exec();
    #endif
    }

    void DocumentHandler::printPreview(QPrinter *printer)
    {
    #ifdef QT_NO_PRINTER
        Q_UNUSED(printer);
    #else
        createPrintDocument();
        documentForPrint->print(printer);
    #endif
    }


    /**
     * @brief create documentForPrint / take tDocument and replace all '$link(...,...)$'-Commands in the Text with rendered / solved Equations / Variables
     *
     */
    void DocumentHandler::createPrintDocument()
    {
        int doublePrecision =3;     //<- make this a setting!!!

        QString newHTMLContent = tDocument->toHtml();

        /*
         * replace all $link(..., xxx)$ with appropriate Strings / rendered Formulas
         *
         * Varaibles:  xxx = 'value' or 'name_eq_value'
         * Formulas:   xxx = 'as_is' or 'with_values'
         *
         */

        QList<MFormula *> formulaList = mModel->getLFormulas();
        QList<MVariable *> variableList = mModel->getLVariables();

        QString searchString ="";
        QString replaceString ="";

        //search and replace variable-Links
        for(int i =0; i<variableList.count(); i++)
        {
            searchString = "$link(" + variableList.at(i)->getTextValue() + ",value)$";

            if(variableList.at(i)->getSolved())
                replaceString = doubleToQString(variableList.at(i)->getNumericValue(),doublePrecision);
            else
                replaceString = tr("unknown");

            newHTMLContent.replace(searchString,replaceString,Qt::CaseInsensitive);

            searchString = "$link(" + variableList.at(i)->getTextValue() + ",name_eq_value)$";
            if(variableList.at(i)->getSolved())
                replaceString = variableList.at(i)->getTextValue() + " = " + doubleToQString(variableList.at(i)->getNumericValue(),doublePrecision);
            else
                replaceString = variableList.at(i)->getTextValue() + " = " + tr("unknown");

            newHTMLContent.replace(searchString,replaceString,Qt::CaseInsensitive);
        }

        //search and replace formula-links
        for(int k= 0; k< formulaList.count(); k++)
        {
            searchString = "$link(" + formulaList.at(k)->toString() + ",as_is)$";
            replaceString = formulaList.at(k)->toString().replace("="," = ");

            newHTMLContent.replace(searchString,replaceString,Qt::CaseInsensitive);

            searchString = "$link(" + formulaList.at(k)->toString() + ",with_values)$";
            replaceString =  formulaToStringWithPluggedInValues(formulaList.at(k),doublePrecision).replace("="," = ");

            newHTMLContent.replace(searchString,replaceString,Qt::CaseInsensitive);
        }

        //next step: render those formulas / variables

        documentForPrint->setHtml(newHTMLContent);



    }

    QString DocumentHandler::formulaToStringWithPluggedInValues(MFormula *formula, int precision)
    {
        QString retVal ="";
        for(int i =0; i< formula->getTokenList().count();i++)
        {
            if(formula->getTokenList().at(i)->getType() == MTokenType::VARIABLE)
            {
                MVariable * tempVaria = qobject_cast<MVariable *>(formula->getTokenList().at(i)->getMObject());
                if(tempVaria != nullptr)
                {
                    if(tempVaria->getSolved())
                        retVal += doubleToQString(tempVaria->getNumericValue(),precision);
                    else
                        retVal += tempVaria->getTextValue();
                }
                else
                    retVal += formula->getTokenList().at(i)->getValue();
            }
            else
            {
                retVal += formula->getTokenList().at(i)->getValue();
            }
        }
        return retVal;
    }

    QString DocumentHandler::doubleToQString(double value, int precision)
    {
        QString retVal=QString::number(value);

        double temp;
        if(modf(value, &temp) != 0)
        {
            //Has fractional part.
            double tmp = log10(value);
            int mag = static_cast<int>(tmp);
            //qDebug()<<"fraction detected: " << value << "  replaced by:" << QString::number(value,'g',precision + mag);
            return QString::number(value,'g',precision + mag);
        }
        /*
        else
        {
            //No fractional part.
            //qDebug()<<"no fraction detected: " << value;
            return QString::number(value);
        }*/

        return retVal;
    }

    void DocumentHandler::showPdfAfterExportChanged(bool showPdf)
    {
        this->showpdfAfterExport = showPdf;
        qDebug()<<"Documenthandler: showPdfAfterexport has been set:"<<showPdf;
    }
#define FILE_PRINT_FUNCTIONS_END }



#define FILE_AUTOSAVE_FUNCTIONS_START {

    void DocumentHandler::autosaveChanged(bool enabled, double timeout)
    {
        autoSaveIsEnabled = enabled;

        if(enabled)
        {
            autoSaveTimer->setInterval(static_cast<int>(timeout*60*1000));
            autoSaveTimer->start();
        }
        else
            autoSaveTimer->stop();
    }


    void DocumentHandler::autoSave()
    {
        if(autoSaveIsEnabled)
            emit saveFileViaView();
    }


#define FILE_AUTOSAVE_FUNCTIONS_END }



#define MATH_FUNCTIONS_START {

    /*
void DocumentHandler::recieveMathData(QList<MFormula*> fList, QList<MVariable*> vList)
{
    qDebug()<<"Dochandler: setting Formula- and Variable-List";
    //mModel->recieveMathData(fList,vList);
}
*/
#define MATH_FUNCTIONS_END }



#define MISC_FUNCTIONS_START {

void DocumentHandler::recieveError(ErrorMessage *errmsg)
{
    emit sendError(errmsg);
}

void DocumentHandler::documentChanged()
{
    emit updateWindowTitle(fileName, false);
}

void DocumentHandler::editDocumentProperties()
{
    TextDocumentPropertyDialog *pDialog = new TextDocumentPropertyDialog();
    pDialog->setWindowTitle(tr("Documentproperties"));
    pDialog->show();
}


#define MISC_FUNCTIONS_END }





