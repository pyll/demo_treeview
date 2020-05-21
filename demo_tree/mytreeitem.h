#pragma once
#ifndef _MY_TREE_ITEM_H_
#define _MY_TREE_ITEM_H_

#include <QtCore/QList>

/** item data in tree model
 */
class MyTreeItem
{
public:
	MyTreeItem(const QString& name);
	~MyTreeItem();

	inline void setName(const QString& name) { _name = name; }
	inline const QString& name() const { return _name; }

	inline void setChecked(bool checked) { _checked = checked; }
	inline bool checked() const { return _checked; }

	inline MyTreeItem* child(int row) { return row < 0 || row >= childCount() ? nullptr : _child_list[row]; }
	inline const MyTreeItem* child(int row) const { return row < 0 || row >= childCount() ? nullptr : _child_list[row]; }

	int row() const;
	inline int childCount() const { return _child_list.size(); }
	void appendChild(MyTreeItem* item);
	void insertChild(MyTreeItem* item, int row);

	inline void setParent(MyTreeItem* parent) { _parent = parent; }
	inline const MyTreeItem* parent() const { return _parent; }
	inline MyTreeItem* parent() { return _parent; }

private:

	///item display name
	QString _name;

	///checked
	bool _checked = true;

	///item's parent
	MyTreeItem* _parent = nullptr;

	///item's child
	QList<MyTreeItem*> _child_list;
};

#endif