#include "mytreeview.h"
#include "mytreemodel.h"
#include "myitemdelegate.h"

MyTreeView::MyTreeView(QWidget* parent /*= Q_NULLPTR*/) : QTreeView(parent)
{
	setModel(new MyTreeModel(this));
	setItemDelegate(new MyItemDelegate(this));
}
