/*
 * Source-Code originally from Dimka / github-user dimkanovikov
 * https://github.com/dimkanovikov/PagesTextEdit,  invoked on: 20.08.2018, commit 40298c6
 *
 * revised and extended by F. Münster
 */
#ifndef PAGESTEXTEDIT_H
#define PAGESTEXTEDIT_H

#include <QTextEdit>
#include <QMimeData>
#include <QFileInfo>
#include <QImageReader>
#include <QtWidgets>

#include "PageMetrics.h"



/**
 * @brief customized QTextEdit with WYSIWGY-look.
 */
class PagesTextEdit : public QTextEdit
{
	Q_OBJECT

public:
    explicit PagesTextEdit(QWidget* parent = nullptr);


	void setPageFormat(QPageSize::PageSizeId _pageFormat);
	void setPageMargins(const QMarginsF& _margins);
	bool usePageMode() const;

    bool canInsertFromMimeData(const QMimeData* source) const;
    void insertFromMimeData(const QMimeData* source);




    bool imagesUseAbsolutePath() const;
    void setImagesUseAbsolutePath(bool imagesUseAbsolutePath);

public slots:

    void setUsePageMode(bool _use);

    void setAddSpaceToBottom(bool _addSpace);

    void setShowPageNumbers(bool _show);

	void setPageNumbersAlignment(Qt::Alignment _align);

    void insertImage(const QUrl& url, const QImage& image, double width, double height);

    void insertTable(int wNumColumn, int wNumRow, int wSizeFixed, Qt::AlignmentFlag alignment);

    void insertText(QString text);

protected:

	void paintEvent(QPaintEvent* _event);
	void resizeEvent(QResizeEvent* _event);

private:

    QTextDocument* m_document;


    bool m_usePageMode;
    bool m_addBottomSpace;
    bool m_showPageNumbers;
    Qt::Alignment m_pageNumbersAlignment;
    bool m_imagesUseAbsolutePath;

    PageMetrics m_pageMetrics;

	void updateViewportMargins();
	void updateVerticalScrollRange();
	void paintPagesView();
	void paintPageNumbers();
	void paintPageNumber(QPainter* _painter, const QRectF& _rect, bool _isHeader, int _number);
    void dropTextFile(const QUrl& url);

private slots:

	void aboutVerticalScrollRangeChanged(int _minimum, int _maximum);
	void aboutDocumentChanged();
	void aboutUpdateDocumentGeometry();

};

#endif // PAGESTEXTEDIT_H
