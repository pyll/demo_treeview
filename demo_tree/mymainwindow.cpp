#include <QtWidgets/QDockWidget>
#include <QtWidgets/QTreeView>
#include "mymainwindow.h"
#include "mytreemodel.h"

///mainwindow's width and height
const int k_main_window_minimum_width_and_height = 400;

MyMainWindow::MyMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setMinimumSize(k_main_window_minimum_width_and_height, k_main_window_minimum_width_and_height);

	///create a tree in mainwindow left dockwidget
	QTreeView* left_tree_view = new QTreeView(this);
	left_tree_view->setModel(new MyTreeModel(left_tree_view));
	QDockWidget* left_dock_widget = new QDockWidget(this);
	left_dock_widget->setWidget(left_tree_view);
	addDockWidget(Qt::LeftDockWidgetArea, left_dock_widget);
}
