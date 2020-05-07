#pragma once
#ifndef _MY_MAIN_WINDOW_H_
#define _MY_MAIN_WINDOW_H_

#include <QtWidgets/QMainWindow>

class MyMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MyMainWindow(QWidget *parent = Q_NULLPTR);
};

#endif
