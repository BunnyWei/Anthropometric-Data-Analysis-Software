#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QToolButton>
#include "ui_toolbutton.h"

class ToolButton : public QToolButton
{
	Q_OBJECT

public:
	ToolButton(QWidget *parent = 0);
	~ToolButton();

private:
	Ui::ToolButtonClass ui;
};

#endif // TOOLBUTTON_H
