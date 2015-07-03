#ifndef MODIFYPASSWORD_H
#define MODIFYPASSWORD_H

#include <QWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVariant>
#include <QDebug>
#include "ui_modifypassword.h"
#include "qglobalvar.h"

class ModifyPassword : public QWidget
{
	Q_OBJECT

public:
	ModifyPassword(QWidget *parent = 0);
	~ModifyPassword();

private:
	Ui::ModifyPasswordClass ui;

private slots:
	void on_okBtn_clicked();
};

#endif // MODIFYPASSWORD_H
