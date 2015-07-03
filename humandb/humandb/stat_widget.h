#ifndef STAT_WIDGET_H
#define STAT_WIDGET_H

#include <QWidget>
#include <QDomElement>
#include <QDomNode>
#include <QSqlQuery>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <cassert>
#include "ui_stat_widget.h"
#include "query.h"

class QPrecise;
//统计类型
//enum enum_staType { MAX, MIN, AVG, STD, PER, TYPESIZE};

class StatWidget : public QWidget
{
	Q_OBJECT

public:
	StatWidget(QWidget *parent = 0);
	void getFilter();
	int getcount();
	Ui::StatWidgetClass ui;
private:
	QStringList tableHeader;
	QString filterSql,filter;
	const QString D2S(double data,QString item, enum enum_staType type);
	QPrecise * pQPrecise;
/*public:
    void on_groupComboBox_currentIndexChanged(int index);
    void setCurrentWidget(QWidget *w);*/

private slots:
	void on_groupComboBox_currentIndexChanged(int index);
	void on_selectNoneButton_clicked();
	void on_selectAllButton_clicked();
	void on_okButton_clicked();
	void on_statButton_clicked();
	void on_openPushButton_clicked();
	void on_exportButton_clicked();
};

#endif // STAT_WIDGET_H
