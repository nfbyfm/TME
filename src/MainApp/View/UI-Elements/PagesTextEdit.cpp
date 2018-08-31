/*
 * Source-Code originally from Dimka / github-user dimkanovikov
 * https://github.com/dimkanovikov/PagesTextEdit,  invoked on: 20.08.2018, commit 40298c6
 *
 * revised and extended by F. Münster
 */



#include "PagesTextEdit.h"

#include <QAbstractTextDocumentLayout>
#include <QPainter>
#include <QScrollBar>
#include <QTextFrame>

PagesTextEdit::PagesTextEdit(QWidget *parent) :
	QTextEdit(parent),
    m_document(nullptr),
	m_usePageMode(false),
	m_addBottomSpace(true),
	m_showPageNumbers(true),
    m_pageNumbersAlignment(Qt::AlignTop | Qt::AlignRight),
    m_imagesUseAbsolutePath(false)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	aboutDocumentChanged();
	connect(this, SIGNAL(textChanged()), this, SLOT(aboutDocumentChanged()));

    connect(verticalScrollBar(), SIGNAL(rangeChanged(int,int)), this, SLOT(aboutVerticalScrollRangeChanged(int,int)));

}

#define PAGESETTING_FUNCTIONS_START {

    void PagesTextEdit::setPageFormat(QPageSize::PageSizeId _pageFormat)
    {
        m_pageMetrics.update(_pageFormat);
        repaint();
    }

    void PagesTextEdit::setPageMargins(const QMarginsF& _margins)
    {
        m_pageMetrics.update(m_pageMetrics.pageFormat(), _margins);
        repaint();
    }

    bool PagesTextEdit::usePageMode() const
    {
        return m_usePageMode;
    }

    void PagesTextEdit::setUsePageMode(bool _use)
    {
        if (m_usePageMode != _use)
        {
            m_usePageMode = _use;
            repaint();
        }
    }

    void PagesTextEdit::setAddSpaceToBottom(bool _addSpace)
    {
        if (m_addBottomSpace != _addSpace) {
            m_addBottomSpace = _addSpace;

            repaint();
        }
    }

    void PagesTextEdit::setShowPageNumbers(bool _show)
    {
        if (m_showPageNumbers != _show) {
            m_showPageNumbers = _show;

            repaint();
        }
    }

    void PagesTextEdit::setPageNumbersAlignment(Qt::Alignment _align)
    {
        if (m_pageNumbersAlignment != _align) {
            m_pageNumbersAlignment = _align;

            repaint();
        }
    }

#define PAGESETTING_FUNCTIONS_END }

#define PAINTEVENTS_START {

    void PagesTextEdit::paintEvent(QPaintEvent* _event)
    {
        updateVerticalScrollRange();

        paintPagesView();

        paintPageNumbers();

        QTextEdit::paintEvent(_event);
    }

    void PagesTextEdit::resizeEvent(QResizeEvent* _event)
    {
        updateViewportMargins();

        updateVerticalScrollRange();

        QTextEdit::resizeEvent(_event);
    }

    bool PagesTextEdit::imagesUseAbsolutePath() const
    {
        return m_imagesUseAbsolutePath;
    }

    void PagesTextEdit::setImagesUseAbsolutePath(bool imagesUseAbsolutePath)
    {
        m_imagesUseAbsolutePath = imagesUseAbsolutePath;
    }

    void PagesTextEdit::updateViewportMargins()
    {

        QMargins viewportMargins;

        if (m_usePageMode)
        {
            int pageWidth = m_pageMetrics.pxPageSize().width();
            int pageHeight = m_pageMetrics.pxPageSize().height();

            const int DEFAULT_TOP_MARGIN = 20;
            const int DEFAULT_BOTTOM_MARGIN = 20;

            int leftMargin = 0;
            int rightMargin = 0;


            if (width() > pageWidth)
            {
                const int BORDERS_WIDTH = 4;
                const int VERTICAL_SCROLLBAR_WIDTH = verticalScrollBar()->isVisible() ? verticalScrollBar()->width() : 0;

                leftMargin = rightMargin = (width() - pageWidth - VERTICAL_SCROLLBAR_WIDTH - BORDERS_WIDTH) / 2;
            }

            int topMargin = DEFAULT_TOP_MARGIN;


            int bottomMargin = DEFAULT_BOTTOM_MARGIN;
            int documentHeight = pageHeight * document()->pageCount();

            if ((height() - documentHeight) > (DEFAULT_TOP_MARGIN + DEFAULT_BOTTOM_MARGIN))
            {
                const int BORDERS_HEIGHT = 2;
                const int HORIZONTAL_SCROLLBAR_HEIGHT = horizontalScrollBar()->isVisible() ? horizontalScrollBar()->height() : 0;
                bottomMargin = height() - documentHeight - HORIZONTAL_SCROLLBAR_HEIGHT - DEFAULT_TOP_MARGIN - BORDERS_HEIGHT;
            }

            viewportMargins = QMargins(leftMargin, topMargin, rightMargin, bottomMargin);

        }

        setViewportMargins(viewportMargins);

        aboutUpdateDocumentGeometry();
    }

    void PagesTextEdit::updateVerticalScrollRange()
    {
        if (m_usePageMode)
        {
            const int pageHeight = m_pageMetrics.pxPageSize().height();
            const int documentHeight = pageHeight * document()->pageCount();
            const int maximumValue = documentHeight - viewport()->height();

            if (verticalScrollBar()->maximum() != maximumValue)
            {
                verticalScrollBar()->setMaximum(maximumValue);
            }
        }
        else
        {
            const int SCROLL_DELTA = 800;
            int maximumValue = document()->size().height() - viewport()->size().height() + (m_addBottomSpace ? SCROLL_DELTA : 0);
            if (verticalScrollBar()->maximum() != maximumValue)
            {
                verticalScrollBar()->setMaximum(maximumValue);
            }
        }
    }

    void PagesTextEdit::paintPagesView()
    {      
        if (m_usePageMode)
        {
            qreal pageWidth = m_pageMetrics.pxPageSize().width();
            qreal pageHeight = m_pageMetrics.pxPageSize().height();

            QPainter p(viewport());
            QPen spacePen(palette().window(), 9);
            QPen borderPen(palette().dark(), 1);

            qreal curHeight = pageHeight - (verticalScrollBar()->value() % (int)pageHeight);

            const int x = pageWidth + (width() % 2 == 0 ? 2 : 1);

            const int horizontalDelta = horizontalScrollBar()->value();

            if (curHeight - pageHeight >= 0)
            {
                p.setPen(borderPen);
                p.drawLine(0, curHeight - pageHeight, x, curHeight - pageHeight);
            }

            while (curHeight <= height())
            {

                p.setPen(spacePen);
                p.drawLine(0, curHeight-4, width(), curHeight-4);

                p.setPen(borderPen);

                p.drawLine(0, curHeight-8, x, curHeight-8);
                p.drawLine(0, curHeight, x, curHeight);
                p.drawLine(0 - horizontalDelta, curHeight - pageHeight, 0 - horizontalDelta, curHeight - 8);
                p.drawLine(x - horizontalDelta, curHeight - pageHeight, x - horizontalDelta, curHeight - 8);

                curHeight += pageHeight;
            }

            if (curHeight >= height())
            {
                p.setPen(borderPen);
                p.drawLine(0 - horizontalDelta, curHeight-pageHeight, 0 - horizontalDelta, height());
                p.drawLine(x - horizontalDelta, curHeight-pageHeight, x - horizontalDelta, height());
            }
        }
    }

    void PagesTextEdit::paintPageNumbers()
    {
        if (m_usePageMode && !m_pageMetrics.pxPageMargins().isNull() && m_showPageNumbers)
        {

            QSizeF pageSize(m_pageMetrics.pxPageSize());
            QMarginsF pageMargins(m_pageMetrics.pxPageMargins());

            QPainter p(viewport());
            p.setFont(document()->defaultFont());
            p.setPen(QPen(palette().text(), 1));

            qreal curHeight = pageSize.height() - (verticalScrollBar()->value() % (int)pageSize.height());

            qreal leftMarginPosition = pageMargins.left() - horizontalScrollBar()->value();
            qreal marginWidth = pageSize.width() - pageMargins.left() - pageMargins.right();
            int pageNumber = verticalScrollBar()->value() / pageSize.height() + 1;

            if (curHeight - pageMargins.top() >= 0)
            {
                QRectF topMarginRect(leftMarginPosition, curHeight - pageSize.height(), marginWidth, pageMargins.top());
                paintPageNumber(&p, topMarginRect, true, pageNumber);
            }

            while (curHeight < height())
            {

                QRect bottomMarginRect(leftMarginPosition, curHeight - pageMargins.bottom(), marginWidth, pageMargins.bottom());
                paintPageNumber(&p, bottomMarginRect, false, pageNumber);

                ++pageNumber;

                QRect topMarginRect(leftMarginPosition, curHeight, marginWidth, pageMargins.top());
                paintPageNumber(&p, topMarginRect, true, pageNumber);

                curHeight += pageSize.height();
            }
        }
    }

    void PagesTextEdit::paintPageNumber(QPainter* _painter, const QRectF& _rect, bool _isHeader, int _number)
    {
        if (_isHeader)
        {
            if (m_pageNumbersAlignment.testFlag(Qt::AlignTop))
            {
                _painter->drawText(_rect, Qt::AlignVCenter | (m_pageNumbersAlignment ^ Qt::AlignTop), tr("Page ") + QString::number(_number));
            }
        }
        else
        {
            if (m_pageNumbersAlignment.testFlag(Qt::AlignBottom))
            {
                _painter->drawText(_rect, Qt::AlignVCenter | (m_pageNumbersAlignment ^ Qt::AlignBottom), tr("Page ") + QString::number(_number));
            }
        }
    }


    void PagesTextEdit::aboutVerticalScrollRangeChanged(int _minimum, int _maximum)
    {
        Q_UNUSED(_minimum);

        updateViewportMargins();

        int scrollValue = verticalScrollBar()->value();

        if (scrollValue > _maximum)
        {
            updateVerticalScrollRange();
        }
    }

    void PagesTextEdit::aboutDocumentChanged()
    {
        if (m_document != document())
        {
            m_document = document();
            connect(document()->documentLayout(), SIGNAL(update()), this, SLOT(aboutUpdateDocumentGeometry()));
        }
    }

    void PagesTextEdit::aboutUpdateDocumentGeometry()
    {
        QSizeF documentSize(width() - verticalScrollBar()->width(), -1);
        if (m_usePageMode)
        {
            int pageWidth = m_pageMetrics.pxPageSize().width();
            int pageHeight = m_pageMetrics.pxPageSize().height();
            documentSize = QSizeF(pageWidth, pageHeight);
        }


        if (document()->pageSize() != documentSize)
        {
            document()->setPageSize(documentSize);
        }


        if (document()->documentMargin() != 0)
        {
            document()->setDocumentMargin(0);
        }

        QMarginsF rootFrameMargins = m_pageMetrics.pxPageMargins();
        QTextFrameFormat rootFrameFormat = document()->rootFrame()->frameFormat();
        if (rootFrameFormat.leftMargin() != rootFrameMargins.left()
            || rootFrameFormat.topMargin() != rootFrameMargins.top()
            || rootFrameFormat.rightMargin() != rootFrameMargins.right()
            || rootFrameFormat.bottomMargin() != rootFrameMargins.bottom())
        {
            rootFrameFormat.setLeftMargin(rootFrameMargins.left());
            rootFrameFormat.setTopMargin(rootFrameMargins.top());
            rootFrameFormat.setRightMargin(rootFrameMargins.right());
            rootFrameFormat.setBottomMargin(rootFrameMargins.bottom());
            document()->rootFrame()->setFrameFormat(rootFrameFormat);
        }
    }


#define PAINTEVENTS_END }

#define PASTE_FUNCTIONS_START {

    bool PagesTextEdit::canInsertFromMimeData(const QMimeData* source) const
    {
            return source->hasImage() || source->hasUrls() || QTextEdit::canInsertFromMimeData(source);
    }

    void PagesTextEdit::insertFromMimeData(const QMimeData* source)
    {
        if (source->hasImage())
        {
            static int i = 1;
            QUrl url(QString("dropped_image_%1").arg(i++));
            insertImage(url, qvariant_cast<QImage>(source->imageData()),0,0);
        }
        else if (source->hasUrls())
        {
            foreach (QUrl url, source->urls())
            {
                QFileInfo info(url.toLocalFile());
                if (QImageReader::supportedImageFormats().contains(info.suffix().toLower().toLatin1()))
                {
                    insertImage(url, QImage(info.filePath()),0,0);
                }
                else
                    dropTextFile(url);
            }
        }
        else
        {
            QTextEdit::insertFromMimeData(source);
        }
    }


    void PagesTextEdit::insertImage(const QUrl& url, const QImage& image, double width, double height)
    {
        if (!image.isNull())
        {
            if(m_imagesUseAbsolutePath)
            {
                //implement!! -> what if document hasn't been saved and relative Path-Setting has been selected?
            }

            document()->addResource(QTextDocument::ImageResource, url, image);

            QTextImageFormat formatImage;
            formatImage.anchorHref() = QTextImageFormat::AlignMiddle;

            if(width<=0 || height <=0)
            {
                formatImage.setWidth(image.width());
                formatImage.setHeight(image.height());
            }
            else
            {
                formatImage.setWidth(width);
                formatImage.setHeight(height);
            }

            formatImage.setName(url.toString());

            textCursor().insertImage(formatImage);
        }
    }

    void PagesTextEdit::dropTextFile(const QUrl& url)
    {
        QFile file(url.toLocalFile());

        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            textCursor().insertText(file.readAll());
    }


    void PagesTextEdit::insertTable(int wNumColumn, int wNumRow,int wSizeFixed, Qt::AlignmentFlag alignment )
    {

        if(wNumColumn > 0 && wNumRow > 0 && wSizeFixed>0 )
        {
            QTextCursor cursor = this->textCursor();
            cursor.insertBlock();

            QTextTableFormat fmt;
            fmt.setColumns(wNumColumn);
            fmt.setAlignment(alignment);

            // add constrains
            QVector<QTextLength> constraints;
            fmt.setWidth((wNumColumn-1)*wSizeFixed);

            for (int i=0;i<wNumColumn;i++)
                constraints.append(QTextLength(QTextLength::FixedLength,wSizeFixed));

            fmt.setColumnWidthConstraints(constraints);
            fmt.setCellSpacing(0);
            cursor.insertTable(wNumRow, wNumColumn, fmt);
        }



    }

    void PagesTextEdit::insertText(QString text)
    {
        textCursor().insertText(text);
    }

#define PASTE_FUNCTIONS_END }


