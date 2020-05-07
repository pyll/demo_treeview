#include <QtWidgets/QApplication>
#include <QtGui/QPainter>
#include "myitemdelegate.h"

MyItemDelegate::MyItemDelegate(QObject *parent /*= Q_NULLPTR*/) : QStyledItemDelegate(parent)
{

}

void MyItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyleOptionViewItemV4 opt = option;
	initStyleOption(&opt, index);

	QStyle* style = opt.widget ? opt.widget->style() : QApplication::style();

	painter->save();
	painter->setClipRect(opt.rect);

	// draw the background
	style->proxy()->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter, opt.widget);

	// draw the icon
	QRect iconRect = style->subElementRect(QStyle::SE_ItemViewItemDecoration, &opt, opt.widget);
// 	iconRect.setLeft(3);
// 	iconRect.setRight(19);
	QIcon::Mode mode = QIcon::Normal;
	if (!(opt.state & QStyle::State_Enabled))
		mode = QIcon::Disabled;
	else if (opt.state & QStyle::State_Selected)
		mode = QIcon::Selected;
	QIcon::State state = opt.state & QStyle::State_Open ? QIcon::On : QIcon::Off;
	opt.icon.paint(painter, iconRect, opt.decorationAlignment, mode, state);

	// draw the text
	QRect textRect = style->subElementRect(QStyle::SE_ItemViewItemText, &opt, opt.widget);
	if (!opt.text.isEmpty())
	{
		QPalette::ColorGroup cg = opt.state & QStyle::State_Enabled
			? QPalette::Normal : QPalette::Disabled;
		if (cg == QPalette::Normal && !(opt.state & QStyle::State_Active))
			cg = QPalette::Inactive;

// 		if (opt.state & QStyle::State_Selected)
// 			painter->setPen(opt.palette.color(cg, QPalette::HighlightedText));
// 		else
// 			painter->setPen(opt.palette.color(cg, QPalette::Text));

		if (opt.state & QStyle::State_Editing)
		{
			painter->setPen(opt.palette.color(cg, QPalette::Text));
			painter->drawRect(textRect/*.adjusted(0, 0, -1, -1)*/);
		}

		//const int textMargin = style->pixelMetric(QStyle::PM_FocusFrameHMargin, 0, opt.widget) + 1;
		//textRect = textRect.adjusted(textMargin, 0, -textMargin, 0); // remove width padding

		painter->setFont(opt.font);
		style->drawItemText(painter, textRect, QStyle::visualAlignment(opt.direction, opt.displayAlignment),
			opt.palette, true, opt.text);
	}


	//QStyledItemDelegate::paint(painter, option, index);
}

QSize MyItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	return QStyledItemDelegate::sizeHint(option, index);
}
