#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QDialog>
#include "ui_chartwidget.h"

class ChartWidget : public QDialog
{
	Q_OBJECT

public:
	ChartWidget(QWidget *parent = 0);
	~ChartWidget();

private:
	Ui::ChartWidgetClass ui;
};

#endif // CHARTWIDGET_H
