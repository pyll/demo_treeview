#include "mytabwidget.h"
#include "mytableview.h"

MyTabWidget::MyTabWidget(QWidget* parent /*= Q_NULLPTR*/) : QTabWidget(parent)
{
	addTab(new MyTableView(this), "table with buttons");
}

