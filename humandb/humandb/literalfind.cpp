#include "literalfind.h"
#include "mainwindow.h"
#include <QDebug>

LiteralFind::LiteralFind(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
    
	ui.bodyComboBox->addItem("头颈部");
	ui.bodyComboBox->addItem("上肢部+肩关节");
	ui.bodyComboBox->addItem("手部+腕部");
	ui.bodyComboBox->addItem("躯干部");
	ui.bodyComboBox->addItem("下肢部");
	ui.bodyComboBox->addItem("足部+踝关节");
	ui.bodyComboBox->addItem("全身段");
	this->setWindowIcon(QIcon("Resources/参数搜索.png"));
	//ui.cancelBtn->setVisible(false);
}

LiteralFind::~LiteralFind()
{

}

void LiteralFind::on_findBtn_clicked()
{
	/*MainWindow wm;
	wm.staDialog->ui.listWidget->clear();*/
#if 1
	if ((ui.nameCheckBox->checkState() == Qt::Unchecked) &&
		(ui.defCheckBox->checkState() == Qt::Unchecked) &&
		(ui.methodCheckBox->checkState() == Qt::Unchecked) &&
		(ui.meaPointCheckBox->checkState() == Qt::Unchecked) &&
		(ui.bodyCheckBox->checkState() == Qt::Unchecked) 
		)
	{
		this->setWindowIcon(QIcon("Resources/参数搜索.png"));
		QMessageBox::warning(this, "警告", "请选择查找类型!", QMessageBox::Ok);
		return;
	}

	MainWindow* win = MainWindow::instance();
	//win->staDialog->ui.listWidget->clear();
	win->controlDock->staDialog->ui.listWidget->clear();
	win->controlDock->setVisible(true);

	QString paraName = ui.nameLineEdit->text();
	QString paraDefinition = ui.defLineEdit->text();
	QString paraMethod = ui.methodLineEdit->text();
	QString paraPoint = ui.meaPointLineEdit->text();
	QString paraBody = ui.bodyComboBox->currentText();

	
	int count = 0;
	QSqlQuery query;
	QString sql = "select itemname, itemnumber from item ";
	if ((ui.nameCheckBox->checkState() == Qt::Checked) ||
		(ui.defCheckBox->checkState() == Qt::Checked) ||
		(ui.methodCheckBox->checkState() == Qt::Checked) ||
		(ui.meaPointCheckBox->checkState() == Qt::Checked) ||
		(ui.bodyCheckBox->checkState() == Qt::Checked) 
		)
	{
		sql += " where ";
	}
	if (ui.nameCheckBox->checkState() == Qt::Checked)
	{
		if (count > 0)
		{
			sql += " and itemname like '%" + paraName + "%'";
		}
		else
		{
            sql += " itemname like '%" + paraName + "%'";
		}
		count++;
	}
	if (ui.defCheckBox->checkState() == Qt::Checked)
	{
		if (count > 0)
		{
			sql += " and itemdefinition like '%" + paraDefinition + "%'";
		}
		else
		{
            sql += " itemdefinition like '%" + paraDefinition + "%'";
		}
		count++;
	}
	if (ui.methodCheckBox->checkState() == Qt::Checked)
	{
		if (count > 0)
		{
			sql += " and itemmeasure like '%" + paraMethod + "%'";
		}
		else
		{
            sql += " itemmeasure like '%" + paraMethod + "%'";
		}
		count++;
	}
	if (ui.meaPointCheckBox->checkState() == Qt::Checked)
	{
		if (count > 0)
		{
			sql += " and measurepoint like '%" + paraPoint + "%'";
		}
		else
		{
            sql += " measurepoint like '%" + paraPoint + "%'";
		}
		count++;
	}
	if (ui.bodyCheckBox->checkState() == Qt::Checked)
	{
		if (count > 0)
		{
			sql += " and measurebody like '%" + paraBody + "%'";
		}
		else
		{
            sql += " measurebody like '%" + paraBody + "%'";
		}
		count++;
	}

	
	qDebug() << sql << endl;
	query.exec(sql);
	while (query.next()) 
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem(itemname);
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		win->controlDock->staDialog->ui.listWidget->addItem(item);
	}
	win->controlDock->stackedWidget->setCurrentIndex(0);
#endif
}

void LiteralFind::on_cancelBtn_clicked()
{
  #if 1
	if ((ui.nameCheckBox->checkState() == Qt::Unchecked) &&
		(ui.defCheckBox->checkState() == Qt::Unchecked) &&
		(ui.methodCheckBox->checkState() == Qt::Unchecked) &&
		(ui.meaPointCheckBox->checkState() == Qt::Unchecked) &&
		(ui.bodyCheckBox->checkState() == Qt::Unchecked) 
		)
	{
		QMessageBox::warning(this, "警告", "请选择查找类型!", QMessageBox::Ok);
		return;
	}

	MainWindow* win = MainWindow::instance();
	//win->staDialog->ui.listWidget->clear();
	win->controlDock->statWidget->ui.listWidget->clear();
	win->controlDock->setVisible(true);

	QString paraName = ui.nameLineEdit->text();
	QString paraDefinition = ui.defLineEdit->text();
	QString paraMethod = ui.methodLineEdit->text();
	QString paraPoint = ui.meaPointLineEdit->text();
	QString paraBody = ui.bodyComboBox->currentText();

	
	int count = 0;
	QSqlQuery query;
	QString sql = "select itemname, itemnumber from item ";
	if ((ui.nameCheckBox->checkState() == Qt::Checked) ||
		(ui.defCheckBox->checkState() == Qt::Checked) ||
		(ui.methodCheckBox->checkState() == Qt::Checked) ||
		(ui.meaPointCheckBox->checkState() == Qt::Checked) ||
		(ui.bodyCheckBox->checkState() == Qt::Checked) 
		)
	{
		sql += " where ";
	}
	if (ui.nameCheckBox->checkState() == Qt::Checked)
	{
		if (count > 0)
		{
			sql += " and itemname like '%" + paraName + "%'";
		}
		else
		{
            sql += " itemname like '%" + paraName + "%'";
		}
		count++;
	}
	if (ui.defCheckBox->checkState() == Qt::Checked)
	{
		if (count > 0)
		{
			sql += " and itemdefinition like '%" + paraDefinition + "%'";
		}
		else
		{
            sql += " itemdefinition like '%" + paraDefinition + "%'";
		}
		count++;
	}
	if (ui.methodCheckBox->checkState() == Qt::Checked)
	{
		if (count > 0)
		{
			sql += " and itemmeasure like '%" + paraMethod + "%'";
		}
		else
		{
            sql += " itemmeasure like '%" + paraMethod + "%'";
		}
		count++;
	}
	if (ui.meaPointCheckBox->checkState() == Qt::Checked)
	{
		if (count > 0)
		{
			sql += " and measurepoint like '%" + paraPoint + "%'";
		}
		else
		{
            sql += " measurepoint like '%" + paraPoint + "%'";
		}
		count++;
	}
	if (ui.bodyCheckBox->checkState() == Qt::Checked)
	{
		if (count > 0)
		{
			sql += " and measurebody like '%" + paraBody + "%'";
		}
		else
		{
            sql += " measurebody like '%" + paraBody + "%'";
		}
		count++;
	}

	
	qDebug() << sql << endl;
	query.exec(sql);
	while (query.next()) 
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem(itemname);
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		win->controlDock->statWidget->ui.listWidget->addItem(item);//ui.listWidget->addItem(item);
	}
	win->controlDock->stackedWidget->setCurrentIndex(2);
#endif
}