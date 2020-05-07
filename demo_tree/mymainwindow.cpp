#include <QtWidgets/QDockWidget>
#include "mymainwindow.h"
#include "mytreeview.h"

///mainwindow's width and height
const int k_main_window_minimum_width_and_height = 400;

MyMainWindow::MyMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setMinimumSize(k_main_window_minimum_width_and_height, k_main_window_minimum_width_and_height);

	///create a tree in mainwindow left dockwidget
	QDockWidget* left_dock_widget = new QDockWidget(this);
	left_dock_widget->setWidget(new MyTreeView(left_dock_widget));
	addDockWidget(Qt::LeftDockWidgetArea, left_dock_widget);
}
