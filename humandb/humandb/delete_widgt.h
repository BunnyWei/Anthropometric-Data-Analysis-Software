#ifndef DELETE_WIDGT_H
#define DELETE_WIDGT_H

#include <QWidget>
#include "ui_delete_widgt.h"
#include "passworddialog.h"

class DeleteWidgt : public QWidget
{
	Q_OBJECT

public:
	DeleteWidgt(QWidget *parent = 0);
	~DeleteWidgt();

	PasswordDialog *pwdDialog;

private:
	Ui::DeleteWidgtClass ui;


private slots:
	void on_measureDelButton_clicked();
	void on_comboBox_currentIndexChanged(int);
	void on_deleteButton_clicked();
};

#endif // DELETE_WIDGT_H
