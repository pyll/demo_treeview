#include <QtGui/QIcon>
#include "mytreemodel.h"
#include "mytreeitem.h"

MyTreeModel::MyTreeModel(QObject* parent /*= Q_NULLPTR*/) : QAbstractItemModel(parent)
	, _root_item(new MyTreeItem("root"))
{
	///make some item
	MyTreeItem* first_item = new MyTreeItem("first");
	first_item->appendChild(new MyTreeItem("f_1"));
	first_item->appendChild(new MyTreeItem("f_2"));
	first_item->appendChild(new MyTreeItem("f_3"));
	MyTreeItem* secend_item = new MyTreeItem("second");
	secend_item->appendChild(new MyTreeItem("s_1"));
	MyTreeItem* third_item = new MyTreeItem("third");
	third_item->appendChild(new MyTreeItem("t_1"));
	third_item->appendChild(new MyTreeItem("t_2"));
	_root_item->appendChild(first_item);
	_root_item->appendChild(secend_item);
	_root_item->appendChild(third_item);
}

Q_INVOKABLE QModelIndex MyTreeModel::index(int row, int column, const QModelIndex &parent /*= QModelIndex()*/) const
{
	if (!hasIndex(row, column, parent)) return QModelIndex();

	MyTreeItem* parent_item = parent.isValid() ? static_cast<MyTreeItem*>(parent.internalPointer()) : _root_item;
	MyTreeItem* child_item = parent_item->child(row);
	if (child_item) return createIndex(row, column, child_item);

	return QModelIndex();
}

Q_INVOKABLE QModelIndex MyTreeModel::parent(const QModelIndex &child) const
{
	if (!child.isValid()) return QModelIndex();
	
	MyTreeItem* child_item = static_cast<MyTreeItem*>(child.internalPointer());
	if (child_item->parent() == _root_item) return QModelIndex();

	return createIndex(child_item->row(), 0, child_item->parent());
}

Q_INVOKABLE int MyTreeModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	MyTreeItem* parent_item = parent.isValid() ? static_cast<MyTreeItem*>(parent.internalPointer()) : _root_item;
	return parent_item->childCount();
}

Q_INVOKABLE int MyTreeModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return 1;
}

Q_INVOKABLE QVariant MyTreeModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
	if (!index.isValid()) return QVariant();

	switch (role)
	{
	case Qt::DisplayRole:
	case Qt::EditRole:
	{
		MyTreeItem* item = static_cast<MyTreeItem*>(index.internalPointer());
		return item->name();
	}
	case Qt::DecorationRole:
		return QIcon("D:/logo.png");
	}
	return QVariant();
}
