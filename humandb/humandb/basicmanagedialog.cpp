#include "basicmanagedialog.h"
#include <math.h>

BasicManageDialog::BasicManageDialog(QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);
}

BasicManageDialog::~BasicManageDialog()
{
}


void BasicManageDialog::on_pushButton_clicked()
{
	QSqlQuery itemQuery;
	itemQuery.exec("select item_id, itemnumber, itemname from item");
	ui.progressBar->setMaximum(itemQuery.size());
	ui.progressBar->setValue(0);

	WorkThread *workThread = new WorkThread(ui.listWidget);
	connect(workThread, SIGNAL(finished()), this, SLOT(workDone()));
	connect(workThread, SIGNAL(complete_count(int)), ui.progressBar, SLOT(setValue(int)));
	workThread->start();
	ui.pushButton->setDisabled(true);
}

void BasicManageDialog::workDone()
{					
	ui.pushButton->setDisabled(false);
	QSqlQuery query;
	query.exec("truncate table statisticmemory");
	query.exec("insert into statisticmemory select * from statistic");
		QListWidgetItem *newItem = new QListWidgetItem;
	ui.listWidget->insertItem(ui.listWidget->count(), newItem);
	newItem->setText(QString("全部计算已完成！"));
}