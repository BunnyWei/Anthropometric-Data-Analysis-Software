#include "usermanage.h"

UserManage::UserManage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.authorityComboBox->addItem("普通用户", "3");
	ui.authorityComboBox->addItem("高级用户", "2");
	ui.authorityComboBox->addItem("超级用户", "1");

	ui.authorComBox->addItem("普通用户", "3");
	ui.authorComBox->addItem("高级用户", "2");
	ui.authorComBox->addItem("超级用户", "1");

	ui.tableWidget->setColumnCount(2);
	ui.tableWidget->setRowCount(20);
	for (int i = 1; i < 2; i++) {
		ui.tableWidget->setColumnWidth(i, 110);
	}
	for (int i = 0; i < 20; i++) {
		ui.tableWidget->setRowHeight(i, 30);
	}

	tableHeader.append("用户名"); 
	tableHeader.append("权  限"); 
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader); 

}

UserManage::~UserManage()
{

}


void UserManage::on_addUserBtn_clicked()
{
	QString userName = ui.userNameLineEdit->text();
	
	if (isThisUserExist(userName))
	{//用户名存在
		QMessageBox::warning(this, "提示", "该用户名已存在！", QMessageBox::Ok);
		return;
	}
	else
	{//用户名不存在
		QString newPwd = ui.newPwdLiEt->text();
		QString confirmPwd = ui.confirmPwdLiEt->text();
		if (newPwd == confirmPwd)
		{//密码一致
			QString authority = ui.authorityComboBox->itemData(ui.authorityComboBox->currentIndex()).toString();
			QSqlQuery insertQuery;
			QString sql = "insert into user(name, password, priviledge) values(?, ?, ?)";
			insertQuery.prepare(sql);
			insertQuery.addBindValue(userName);
			insertQuery.addBindValue(newPwd);
			insertQuery.addBindValue(authority);
			if (insertQuery.exec())
			{
				QMessageBox::warning(this, "提示", "添加用户成功！", QMessageBox::Ok);
				//重置
				ui.userNameLineEdit->clear();
				ui.newPwdLiEt->clear();
				ui.confirmPwdLiEt->clear();
			}
			else
			{
				QMessageBox::warning(this, "提示", "添加用户失败！", QMessageBox::Ok);
			}
		}
		else
		{//密码不一致
			QMessageBox::warning(this, "提示", "密码不一致！", QMessageBox::Ok);
			return;
		}
	}
}

bool UserManage::isThisUserExist(QString &userName)
{
	QSqlQuery query;
	QString sql = "select name from user where name = '" + userName + "'";
	query.exec(sql);
	return query.next();
}

bool UserManage::isThisUserExist(QString &userName, QString &password)
{
	QSqlQuery query;
	QString sql = "select name from user where name = '" + userName + "' and password = '" + password + "'";
	query.exec(sql);
	return query.next();
}

void UserManage::on_modifyAuthorBtn_clicked()
{
	//QString userName = ui.userComBox->itemData(ui.userComBox->currentIndex()).toString();
	QString userName = ui.userLineEdit->text();
	if (!isThisUserExist(userName))
	{//用户名不存在
		QMessageBox::warning(this, "提示", "该用户名不存在！", QMessageBox::Ok);
		return;
	}
	QString authority = ui.authorComBox->itemData(ui.authorComBox->currentIndex()).toString();
	if (userName == QGlobalVar::currentUser)
	{
		QMessageBox::warning(this, "提示", "该用户为当前用户，\n无法修改！", QMessageBox::Ok);
		return;
	}
	else
	{
		QSqlQuery updateQuery;
		QString sql = "update user set priviledge = '" + authority + "' where name = '" + userName + "'";
		if (updateQuery.exec(sql))
		{
			 QMessageBox::warning(this, "提示", "权限修改完成！", QMessageBox::Ok);
			 ui.userLineEdit->clear();
		}
		else
		{
			 QMessageBox::warning(this, "提示", "权限修改失败！", QMessageBox::Ok);
		}
	}
	
}

void UserManage::on_delUserBtn_clicked()
{
	QString userName = ui.userLineEdit->text();
	if (!isThisUserExist(userName))
	{//用户名不存在
		QMessageBox::warning(this, "提示", "该用户名不存在！", QMessageBox::Ok);
		return;
	}
	if (userName == QGlobalVar::currentUser)
	{
		QMessageBox::warning(this, "提示", "该用户为当前用户，\n无法删除！", QMessageBox::Ok);
		return;
	}
	else
	{
		QSqlQuery delQuery;
		QString sql = "delete from user where name = '" + userName + "'";
		if (delQuery.exec(sql))
		{
			QMessageBox::warning(this, "提示", "用户删除完成！", QMessageBox::Ok);
			ui.userLineEdit->clear();
		}
		else
		{
			QMessageBox::warning(this, "提示", "用户删除失败！", QMessageBox::Ok);
		}
	}

}



void UserManage::on_showAllUsersBtn_clicked()
{
	ui.tableWidget->clear();
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader); //添加列标题
	QSqlQuery query("select name, priviledge from user");
	int index = 0;
	while (query.next())
	{
	 QString userName = query.value(0).toString();
	 QString priviledge = query.value(1).toString();
	 QString author;
	 if (priviledge == "1")
	 {
		 author = "超级用户";
	 }
	 else if (priviledge == "2")
	 {
		 author = "高级用户";
	 }
	 else if (priviledge == "3")
	 {
		 author = "普通用户";
	 }
	 ui.tableWidget->setItem(index, 0, new QTableWidgetItem(userName));
	 ui.tableWidget->setItem(index, 1, new QTableWidgetItem(author));
	 index++;
	}
}