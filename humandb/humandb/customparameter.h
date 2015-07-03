#ifndef CUSTOMPARAMETER_H
#define CUSTOMPARAMETER_H

#include <QWidget>
#include <QSqlQuery>
#include <QRadioButton>
#include <QMessageBox>
#include <cassert>
#include <QDebug>
#include "ui_customparameter.h"
#include "customparameterthread.h"

class CustomParameter : public QWidget
{
	Q_OBJECT

public:
	CustomParameter(QWidget *parent = 0);
	~CustomParameter();

private:
	Ui::CustomParameterClass ui;

	QString dbName1;//用户选择的参数1对应的字段
	QString dbName2;//用户选择的参数2对应的字段
	QString dbName3;//用户选择的参数3对应的字段
	QString table1;//参数1对应的表
	QString table2;//参数2对应的表
	QString table3;//参数3对应的表

	void getSelectedDBName();//得到用户选择字段
	inline QString getTable(QString  attribute);
	QString defItemNumber(QString table);



private slots:
	void on_addBtn_clicked();
	void on_paraCountComboBox_currentIndexChanged(int);
	void on_paraComboBox3_currentIndexChanged(int);
	void on_paraComboBox2_currentIndexChanged(int);
	void on_paraComboBox1_currentIndexChanged(int);
	void on_groupComboBox_currentIndexChanged(int);
	void addParameterDone();
};

#endif // CUSTOMPARAMETER_H
