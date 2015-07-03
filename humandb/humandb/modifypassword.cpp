#include "modifypassword.h"

ModifyPassword::ModifyPassword(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QString showCurrentUser = "当前用户为：" + QGlobalVar::currentUser;
	ui.currentUser->setText(showCurrentUser);
}

ModifyPassword::~ModifyPassword()
{

}


void ModifyPassword::on_okBtn_clicked()
{
     QSqlQuery query, updateQuery;
	 QString sql = "select password from user where name = '" + QGlobalVar::currentUser + "'";
	 query.exec(sql);
	 query.next();
	 QString password = query.value(0).toString();
	 QString oldPassword = ui.oldPasswordLineEdit->text();

	 if (oldPassword != password)
	 {
		 QMessageBox::warning(this, "提示", "原密码输入错误！", QMessageBox::Ok);
		 return ;
	 }
	 else
	 {
		 QString newPassword = ui.newPasswordLineEdit->text();
		 QString confirmPassword = ui.confirmLineEdit->text();

		 if (newPassword != confirmPassword)
		 {
			 QMessageBox::warning(this, "提示", "两次输入密码不一致！", QMessageBox::Ok);
		     return ;
		 }
		 else
		 {
             QString updateSql = "update user set password = '" + newPassword + "' where name = '" + QGlobalVar::currentUser + "'";
			 updateQuery.prepare(updateSql);
			 qDebug() << "updateSql：" << updateSql;
			 if (updateQuery.exec())
			 {
				  QMessageBox::warning(this, "提示", "密码修改成功！", QMessageBox::Ok);
				  ui.oldPasswordLineEdit->clear();
				  ui.newPasswordLineEdit->clear();
				  ui.confirmLineEdit->clear();
			 }
			 else
			 {
				  QMessageBox::warning(this, "提示", "密码修改失败！", QMessageBox::Ok);
			 }
		 }
	 }

}