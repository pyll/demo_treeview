#pragma once
#ifndef _MY_TREE_VIEW_H
#define _MY_TREE_VIEW_H

#include <QtWidgets/QTreeView>

class MyTreeView : public QTreeView 
{
public:
	MyTreeView(QWidget* parent = Q_NULLPTR);
	~MyTreeView() {}

};

#endif