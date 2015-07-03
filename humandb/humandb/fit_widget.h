#ifndef FIT_WIDGET_H
#define FIT_WIDGET_H

#include <QWidget>
#include <QDomElement>
#include <QDomNode>
#include <QDomElement>
#include <QSqlQuery>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <chartdir.h>
#include <QPixmap>
#include <QImage>
#include <QGraphicsScene>
#include <QTextCodec>
#include <QHash>
#include <windows.h>
#include <cassert>
#include "ui_fit_widget.h"

class FitWidget : public QWidget
{
	Q_OBJECT

public:
	FitWidget(QWidget *parent = 0);
	~FitWidget();

private:
	Ui::FitWidgetClass ui;
	QString dbX;
	QString dbY;
	QListWidgetItem *currentItem;
	QHash<QString , double> peopleView;
	QHash<QString , double> regionView;
	QHash<QString , double> jiguanView;
	QHash<QString , double> bingzhongView;
	QHash<QString , double> junxianView;
	QHash<QString , double> wenhuaView;

	QList<QString> deviationList;
private slots:
	void on_exportButton_clicked();
	void on_selectButton_clicked();
	void on_deleteButton_clicked();
	void on_xTableComboBox_currentIndexChanged(int);
	void on_yTableComboBox_currentIndexChanged(int);
	void onXItemChanged(QListWidgetItem *it);
	void onYItemChanged(QListWidgetItem *it);
};

#endif // FIT_WIDGET_H
