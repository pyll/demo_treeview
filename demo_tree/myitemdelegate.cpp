#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtGui/QPainter>
#include "myitemdelegate.h"

MyItemDelegate::MyItemDelegate(QObject *parent /*= Q_NULLPTR*/) : QStyledItemDelegate(parent)
, _push_button(new QPushButton())
{
	_push_button->setStyleSheet("QPushButton{border:none;}");
}

void MyItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if (index.column() == 0)
	{
		QStyleOptionButton button;

		int button_width = (option.rect.width() / 2) > _button_width ? _button_width : option.rect.width() / 2;

		button.rect = QRect(option.rect.left() + option.rect.width() - button_width,
			option.rect.top(), button_width, option.rect.height());
		button.state |= QStyle::State_Enabled;
		button.icon = QIcon("D:/01.jpg");
		//button.iconSize = QSize(32, 16);

		//QScopedPointer<QPushButton> pushButton(new QPushButton);
		//pushButton->setStyleSheet("border:none");

		QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter, _push_button);

		QStyleOptionViewItem opt(option);
		opt.rect = option.rect.adjusted(0, 0, -button.rect.width(), 0);
		QStyledItemDelegate::paint(painter, opt, index);
	}
	else
		QStyledItemDelegate::paint(painter, option, index);
}

QSize MyItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	return QStyledItemDelegate::sizeHint(option, index);
}
