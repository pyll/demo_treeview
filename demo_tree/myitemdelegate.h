#pragma once
#ifndef _MY_DELEGATE_H_
#define _MY_DELEGATE_H_

#include <QtWidgets/QStyledItemDelegate>

class MyItemDelegate : public QStyledItemDelegate
{
public:
	MyItemDelegate(QObject *parent = Q_NULLPTR);
	~MyItemDelegate() {}

	virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;


	virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif