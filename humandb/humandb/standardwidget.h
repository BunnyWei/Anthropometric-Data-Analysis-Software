#ifndef STANDARDWIDGET_H
#define STANDARDWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QSqlQuery>
#include "ui_standardwidget.h"
//#include "mainwindow.h"

class StandardWidget : public QWidget
{
	Q_OBJECT

public:
	StandardWidget(QWidget *parent = 0);
	~StandardWidget();

private:
	Ui::StandardWidgetClass ui;

private slots:
	void on_searchBtn_clicked();
};

#endif // STANDARDWIDGET_H
