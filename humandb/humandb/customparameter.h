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

	QString dbName1;//�û�ѡ��Ĳ���1��Ӧ���ֶ�
	QString dbName2;//�û�ѡ��Ĳ���2��Ӧ���ֶ�
	QString dbName3;//�û�ѡ��Ĳ���3��Ӧ���ֶ�
	QString table1;//����1��Ӧ�ı�
	QString table2;//����2��Ӧ�ı�
	QString table3;//����3��Ӧ�ı�

	void getSelectedDBName();//�õ��û�ѡ���ֶ�
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
