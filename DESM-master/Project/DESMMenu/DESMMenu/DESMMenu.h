#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DESMMenu.h"

class DESMMenu : public QMainWindow
{
	Q_OBJECT

public:
	DESMMenu(QWidget *parent = Q_NULLPTR);

private:
	Ui::DESMMenuClass ui;
};
