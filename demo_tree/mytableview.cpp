#include <QtWidgets/QPushButton>
#include <QtGui/QtEvents>
#include "mytableview.h"

MyTableView::MyTableView(QWidget* parent /*= Q_NULLPTR*/) : QTableView(parent)
{
	setModel(new MyTableModel(this));

	setMouseTracking(true);

	///make some buttons
	QPushButton* button1 = new QPushButton(this);
	button1->setStyleSheet("QPushButton{image: url(:/demo_tree/Resources/gray_square.png);}QPushButton:hover, QPushButton:selected{image:url(:/demo_tree/Resources/red_square.png);}");
	button1->hide();
	QPushButton* button2 = new QPushButton(this);
	button2->setStyleSheet("QPushButton{image: url(:/demo_tree/Resources/gray_triangle.png);}QPushButton:hover, QPushButton:selected{image:url(:/demo_tree/Resources/blue_triangle.png);}");
	button2->hide();
	QPushButton* button3 = new QPushButton(this);
	button3->setStyleSheet("QPushButton{image: url(:/demo_tree/Resources/gray_circle.png);}QPushButton:hover, QPushButton:selected{image:url(:/demo_tree/Resources/green_circle.png);}");
	button3->hide();
	setItemDelegateForColumn(MyTableModel::kB, new MyTableButtonDelegate(QVector<QPushButton*>{button1, button2, button3}, this));
}

MyTableModel::MyTableModel(QObject* parent /*= Q_NULLPTR*/) : QAbstractTableModel(parent)
{

}

Q_INVOKABLE int MyTableModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	///here, rowCount is fix by me. just for test
	return 3;
}

Q_INVOKABLE int MyTableModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return kAll;
}

Q_INVOKABLE QVariant MyTableModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
	if (index.isValid() == false) return QVariant();

	if (role == Qt::DisplayRole)
	{
		switch (index.column())
		{
		case kA: return index.row() + 1;
		}
	}
	return QVariant();
}

Q_INVOKABLE QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		switch (section)
		{
		case kA: return "A";
		case kB: return "B";
		}
	}
	return QVariant();
}

MyTableButtonDelegate::MyTableButtonDelegate(const QVector<QPushButton*>& push_buttons, QObject* parent) : QStyledItemDelegate(parent)
	, _push_buttons(push_buttons)
{
	for (QPushButton* button : _push_buttons)
	{
		button->setStyleSheet(button->styleSheet() + "QPushButton{border:none;background:transparent;}");
	}
}

void MyTableButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyledItemDelegate::paint(painter, option, index);

	///判断是否可以绘制按钮
	if (canPaint(option) == false) return;

	///创建style button
	createStyleButtonIfNo(index);

	///第i个按钮的rect（开始默认第0个，i=0）
	QRect button_i_rect = QRect(option.rect.left() + 4, option.rect.top() + (option.rect.height() - _push_buttons[0]->iconSize().height()) / 2, _push_buttons[0]->iconSize().width(), _push_buttons[0]->iconSize().height());
	for (int i = 0; i < _style_buttons[index].size(); i++)
	{
		///绘制按钮
		_style_buttons[index][i]->rect = button_i_rect;
		_push_buttons[i]->style()->drawControl(QStyle::CE_PushButton, _style_buttons[index][i], painter, _push_buttons[i]);

		///重置按钮state
		_style_buttons[index][i]->state &= ~QStyle::State_MouseOver;

		///下一个按钮的rect（最后一个按钮不用计算rect）
		if (i < _style_buttons[index].size() - 1)
			button_i_rect.translate(_push_buttons[i]->iconSize().width() + _button_spacing, 0);
	}
}

bool MyTableButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	///does not select this row
	const QTableView* table_view = dynamic_cast<const QTableView*>(option.widget);
	if (_draw_when_selected && !table_view->selectionModel()->isRowSelected(index.row(), index.parent()))
		return false;

	///index's buttons haven't been initialize
	if (!_style_buttons.contains(index))
		return false;

	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* e = (QMouseEvent*)event;
		for (int j = 0; j < _style_buttons[index].size(); j++)
		{
			if (_style_buttons[index][j]->rect.contains(e->x(), e->y()))
			{
				_style_buttons[index][j]->state |= QStyle::State_Sunken;
				return true;
			}
		}
	}
	else if (event->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent* e = (QMouseEvent*)event;
		for (int j = 0; j < _style_buttons[index].size(); j++)
		{
			if (_style_buttons[index][j]->rect.contains(e->x(), e->y()) && _style_buttons[index][j]->state & QStyle::State_Sunken)
				emit buttonClickSignal(j, index.row());
			_style_buttons[index][j]->state &= ~QStyle::State_Sunken;
		}
		emit sizeHintChanged(index);
	}
	else if (event->type() == QEvent::MouseMove)
	{
		QMouseEvent* e = (QMouseEvent*)event;
		for (int j = 0; j < _style_buttons[index].size(); j++)
		{
			if (_style_buttons[index][j]->rect.contains(e->x(), e->y()))
				_style_buttons[index][j]->state |= QStyle::State_MouseOver;
			else
				_style_buttons[index][j]->state &= ~QStyle::State_MouseOver;
		}
		emit sizeHintChanged(index);
	}

	return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void MyTableButtonDelegate::createStyleButtonIfNo(const QModelIndex& index) const
{
	///already initialized
	if (_style_buttons.contains(index)) return;

	for (const QPushButton* button : _push_buttons)
	{
		QStyleOptionButton* style_button = new QStyleOptionButton;
		_style_buttons[index].push_back(style_button);
		style_button->init(button);
		style_button->text = button->text();
		style_button->icon = button->icon();
		style_button->iconSize = _button_size;
	}
}

bool MyTableButtonDelegate::canPaint(const QStyleOptionViewItem &option) const
{
	///under the situation that can draw only when the row selected
	if (_draw_when_selected)
		return option.state & QStyle::State_Selected ? true : false;
	///buttons are always being draw
	return true;
}
