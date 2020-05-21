#pragma once
#ifndef _MY_TREE_MODEL_H_
#define _MY_TREE_MODEL_H_

#include <QtCore/QAbstractItemModel>

class MyTreeItem;

class MyTreeModel : public QAbstractItemModel
{
public:
	MyTreeModel(QObject* parent = Q_NULLPTR);
	~MyTreeModel() {}

	Q_INVOKABLE virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;


	Q_INVOKABLE virtual QModelIndex parent(const QModelIndex &child) const override;


	Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;


	Q_INVOKABLE virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;


	Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


	Q_INVOKABLE virtual Qt::ItemFlags flags(const QModelIndex &index) const override;


	Q_INVOKABLE virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

private:
	MyTreeItem* _root_item = nullptr;
};

#endif