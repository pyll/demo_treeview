#pragma once
#ifndef _MY_TABLE_VIEW_H_
#define _MY_TABLE_VIEW_H_

#include <QtWidgets/QTableView>
#include <QtWidgets/QStyledItemDelegate>

class QPushButton;

class MyTableView : public QTableView
{
public:
	MyTableView(QWidget* parent = Q_NULLPTR);
};

class MyTableModel : public QAbstractTableModel
{
public:
	///table column index
	enum Column
	{
		kA = 0,
		kB,
		kAll,
	};
public:
	MyTableModel(QObject* parent = Q_NULLPTR);

	Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;


	Q_INVOKABLE virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;


	Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	Q_INVOKABLE virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
};

class MyTableButtonDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	MyTableButtonDelegate(const QVector<QPushButton*>& push_buttons, QObject* parent);

	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;


	virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
	///when click No.button_index button, it will send this signal
	void buttonClickSignal(int button_index, int row);

private:
	///initialize index's style buttons
	void createStyleButtonIfNo(const QModelIndex& index) const;

	///check button can be drew
	bool canPaint(const QStyleOptionViewItem &option) const;

private:
	mutable QMap<QModelIndex, QVector<QStyleOptionButton*>> _style_buttons;
	QVector<QPushButton*> _push_buttons;

	///If false, buttons are always being drew. If true, buttons are drew when the row is being selected
	bool _draw_when_selected = false;

	///buttons spacing
	int _button_spacing = 7;
	///buttons size
	QSize _button_size = QSize(24, 24);
};

#endif