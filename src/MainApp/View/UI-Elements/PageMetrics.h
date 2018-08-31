/*
 * Source-Code originally from Dimka / github-user dimkanovikov
 * https://github.com/dimkanovikov/PagesTextEdit,  invoked on: 20.08.2018, commit 40298c6
 *
 * revised and extended by F. Münster
 */
#ifndef PAGEMETRICS_H
#define PAGEMETRICS_H

#include <QString>
#include <QSizeF>
#include <QMarginsF>
#include <QPageSize>

class QPaintDevice;

/**
 * @brief helper-class for the PagesTextEdit. Defines Pagesize and Margins
 *
 */
class PageMetrics
{
public:

	static qreal mmToPx(qreal _mm, bool _x = true);
	static QPageSize::PageSizeId pageSizeIdFromString(const QString& _from);
	static QString stringFromPageSizeId(QPageSize::PageSizeId _pageSize);

public:
	PageMetrics(QPageSize::PageSizeId _pageFormat = QPageSize::A4, QMarginsF _mmMargins = QMarginsF());

	void update(QPageSize::PageSizeId _pageFormat, QMarginsF _mmPageMargins = QMarginsF());

	QPageSize::PageSizeId pageFormat() const;
	QSizeF mmPageSize() const;
	QMarginsF mmPageMargins() const;
	QSizeF pxPageSize() const;
	QMarginsF pxPageMargins() const;


private:

	QPageSize::PageSizeId m_pageFormat;

	QSizeF m_mmPageSize;
	QMarginsF m_mmPageMargins;

	QSizeF m_pxPageSize;
	QMarginsF m_pxPageMargins;

};

#endif // PAGEMETRICS_H
