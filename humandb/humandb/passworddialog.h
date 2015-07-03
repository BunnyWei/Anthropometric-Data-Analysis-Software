#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>
#include "ui_passworddialog.h"

class PasswordDialog : public QDialog
{
	Q_OBJECT

public:
	PasswordDialog(QWidget *parent = 0);
	~PasswordDialog();
	bool isPasswordCorrect();
	bool isCancel();

private:
	Ui::PasswordDialogClass ui;

	bool flag;
	bool cancelFlag;

private slots:
	void on_cancelButton_clicked();
	void on_okButton_clicked();
};

#endif // PASSWORDDIALOG_H
