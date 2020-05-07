#include "mytreeitem.h"

MyTreeItem::MyTreeItem(const QString& name) : _name(name)
{

}

MyTreeItem::~MyTreeItem()
{
	for (int i = childCount() - 1; i >= 0; i--)
	{
		if(_child_list[i])
		{
			delete _child_list[i];
			_child_list[i] = nullptr;
		}
	}
}

int MyTreeItem::row() const
{
	if (!_parent) return -1;
	
	for (int i = 0; i < _parent->childCount(); i++)
		if (_parent->child(i) == this)
			return i;

	return -1;
}

void MyTreeItem::appendChild(MyTreeItem* item)
{
	if (!item) return;

	_child_list.append(item);
	item->setParent(this);
}

void MyTreeItem::insertChild(MyTreeItem* item, int row)
{
	if (!item) return;

	if (row < 0) row = 0;
	else if (row > childCount()) row = childCount();

	_child_list.insert(row, item);
	item->setParent(this);
}
