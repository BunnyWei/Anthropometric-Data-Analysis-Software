#include "modifypassword.h"

ModifyPassword::ModifyPassword(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QString showCurrentUser = "��ǰ�û�Ϊ��" + QGlobalVar::currentUser;
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
		 QMessageBox::warning(this, "��ʾ", "ԭ�����������", QMessageBox::Ok);
		 return ;
	 }
	 else
	 {
		 QString newPassword = ui.newPasswordLineEdit->text();
		 QString confirmPassword = ui.confirmLineEdit->text();

		 if (newPassword != confirmPassword)
		 {
			 QMessageBox::warning(this, "��ʾ", "�����������벻һ�£�", QMessageBox::Ok);
		     return ;
		 }
		 else
		 {
             QString updateSql = "update user set password = '" + newPassword + "' where name = '" + QGlobalVar::currentUser + "'";
			 updateQuery.prepare(updateSql);
			 qDebug() << "updateSql��" << updateSql;
			 if (updateQuery.exec())
			 {
				  QMessageBox::warning(this, "��ʾ", "�����޸ĳɹ���", QMessageBox::Ok);
				  ui.oldPasswordLineEdit->clear();
				  ui.newPasswordLineEdit->clear();
				  ui.confirmLineEdit->clear();
			 }
			 else
			 {
				  QMessageBox::warning(this, "��ʾ", "�����޸�ʧ�ܣ�", QMessageBox::Ok);
			 }
		 }
	 }

}