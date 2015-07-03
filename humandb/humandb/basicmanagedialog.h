#ifndef BASICMANAGEDIALOG_H
#define BASICMANAGEDIALOG_H

#include <QWidget>
#include "ui_basicmanagedialog.h"
#include "basic_manage_thread.h"

class BasicManageDialog : public QWidget
{
	Q_OBJECT

public:
	BasicManageDialog(QWidget *parent = 0);
	~BasicManageDialog();

private:
	Ui::BasicManageDialogClass ui;

private slots:
	void workDone();
	void on_pushButton_clicked();
};

#endif // BASICMANAGEDIALOG_H
