#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QtWidgets>
#include <QTextEdit>

/**
 * @brief UI-element for MDI (not used in first release)
 *
 */
class FileWindow : public QTextEdit
{
     Q_OBJECT

public:
    explicit FileWindow(QWidget* parent = nullptr);

//for mdi-Area
    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString userFriendlyCurrentFile();
    QString currentFile() { return curFile; }

    /*
//for Pageination
    void setPageFormat(QPageSize::PageSizeId _pageFormat);

    void setPageMargins(const QMarginsF& _margins);

    bool usePageMode() const;

public slots:
    void setUsePageMode(bool _use);
    void setAddSpaceToBottom(bool _addSpace);
    void setShowPageNumbers(bool _show);
    void setPageNumbersAlignment(Qt::Alignment _align);
*/


protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void documentWasModified();

private:
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QString curFile;
    bool isUntitled;
};

#endif // FILEWINDOW_H
