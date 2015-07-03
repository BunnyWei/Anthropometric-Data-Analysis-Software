#ifndef LITERALFIND_H
#define LITERALFIND_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include "ui_literalfind.h"
#include "statistic.h"
#include "ui_statistic.h"

class LiteralFind : public QDialog
{
	Q_OBJECT

public:
	LiteralFind(QWidget *parent = 0);
	~LiteralFind();

private:
	Ui::LiteralFindClass ui;
	
private slots:
	void on_cancelBtn_clicked();
	void on_findBtn_clicked();
};

#endif // LITERALFIND_H
