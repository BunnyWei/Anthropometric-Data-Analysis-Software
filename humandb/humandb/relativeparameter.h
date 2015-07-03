#ifndef RELATIVEPARAMETER_H
#define RELATIVEPARAMETER_H

#include <QWidget>
#include <QSqlQuery>
#include <cassert>
#include "ui_relativeparameter.h"


class QPrecise;

class RelativeParameter : public QWidget
{
	Q_OBJECT

public:
	RelativeParameter(QWidget *parent = 0);
	~RelativeParameter();

private:
	Ui::RelativeParameterClass ui;

	QStringList tableHeader;
	const QString D2S(double data,QString item, enum enum_staType type);
	int searchType;
	QPrecise * pQPrecise;

private slots:
	void on_typeComboBox_textChanged(const QString &);
	void on_listWidget_clicked(const QModelIndex &);
	void on_staBtn_clicked();
	void on_tableComboBox_currentIndexChanged(int);
	void on_typeComboBox_currentIndexChanged(int);
	void on_groupComboBox_currentIndexChanged(int);
};

#endif // RELATIVEPARAMETER_H
