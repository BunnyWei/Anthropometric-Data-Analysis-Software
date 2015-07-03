#include "usermanage.h"

UserManage::UserManage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.authorityComboBox->addItem("��ͨ�û�", "3");
	ui.authorityComboBox->addItem("�߼��û�", "2");
	ui.authorityComboBox->addItem("�����û�", "1");

	ui.authorComBox->addItem("��ͨ�û�", "3");
	ui.authorComBox->addItem("�߼��û�", "2");
	ui.authorComBox->addItem("�����û�", "1");

	ui.tableWidget->setColumnCount(2);
	ui.tableWidget->setRowCount(20);
	for (int i = 1; i < 2; i++) {
		ui.tableWidget->setColumnWidth(i, 110);
	}
	for (int i = 0; i < 20; i++) {
		ui.tableWidget->setRowHeight(i, 30);
	}

	tableHeader.append("�û���"); 
	tableHeader.append("Ȩ  ��"); 
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader); 

}

UserManage::~UserManage()
{

}


void UserManage::on_addUserBtn_clicked()
{
	QString userName = ui.userNameLineEdit->text();
	
	if (isThisUserExist(userName))
	{//�û�������
		QMessageBox::warning(this, "��ʾ", "���û����Ѵ��ڣ�", QMessageBox::Ok);
		return;
	}
	else
	{//�û���������
		QString newPwd = ui.newPwdLiEt->text();
		QString confirmPwd = ui.confirmPwdLiEt->text();
		if (newPwd == confirmPwd)
		{//����һ��
			QString authority = ui.authorityComboBox->itemData(ui.authorityComboBox->currentIndex()).toString();
			QSqlQuery insertQuery;
			QString sql = "insert into user(name, password, priviledge) values(?, ?, ?)";
			insertQuery.prepare(sql);
			insertQuery.addBindValue(userName);
			insertQuery.addBindValue(newPwd);
			insertQuery.addBindValue(authority);
			if (insertQuery.exec())
			{
				QMessageBox::warning(this, "��ʾ", "����û��ɹ���", QMessageBox::Ok);
				//����
				ui.userNameLineEdit->clear();
				ui.newPwdLiEt->clear();
				ui.confirmPwdLiEt->clear();
			}
			else
			{
				QMessageBox::warning(this, "��ʾ", "����û�ʧ�ܣ�", QMessageBox::Ok);
			}
		}
		else
		{//���벻һ��
			QMessageBox::warning(this, "��ʾ", "���벻һ�£�", QMessageBox::Ok);
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
	{//�û���������
		QMessageBox::warning(this, "��ʾ", "���û��������ڣ�", QMessageBox::Ok);
		return;
	}
	QString authority = ui.authorComBox->itemData(ui.authorComBox->currentIndex()).toString();
	if (userName == QGlobalVar::currentUser)
	{
		QMessageBox::warning(this, "��ʾ", "���û�Ϊ��ǰ�û���\n�޷��޸ģ�", QMessageBox::Ok);
		return;
	}
	else
	{
		QSqlQuery updateQuery;
		QString sql = "update user set priviledge = '" + authority + "' where name = '" + userName + "'";
		if (updateQuery.exec(sql))
		{
			 QMessageBox::warning(this, "��ʾ", "Ȩ���޸���ɣ�", QMessageBox::Ok);
			 ui.userLineEdit->clear();
		}
		else
		{
			 QMessageBox::warning(this, "��ʾ", "Ȩ���޸�ʧ�ܣ�", QMessageBox::Ok);
		}
	}
	
}

void UserManage::on_delUserBtn_clicked()
{
	QString userName = ui.userLineEdit->text();
	if (!isThisUserExist(userName))
	{//�û���������
		QMessageBox::warning(this, "��ʾ", "���û��������ڣ�", QMessageBox::Ok);
		return;
	}
	if (userName == QGlobalVar::currentUser)
	{
		QMessageBox::warning(this, "��ʾ", "���û�Ϊ��ǰ�û���\n�޷�ɾ����", QMessageBox::Ok);
		return;
	}
	else
	{
		QSqlQuery delQuery;
		QString sql = "delete from user where name = '" + userName + "'";
		if (delQuery.exec(sql))
		{
			QMessageBox::warning(this, "��ʾ", "�û�ɾ����ɣ�", QMessageBox::Ok);
			ui.userLineEdit->clear();
		}
		else
		{
			QMessageBox::warning(this, "��ʾ", "�û�ɾ��ʧ�ܣ�", QMessageBox::Ok);
		}
	}

}



void UserManage::on_showAllUsersBtn_clicked()
{
	ui.tableWidget->clear();
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader); //����б���
	QSqlQuery query("select name, priviledge from user");
	int index = 0;
	while (query.next())
	{
	 QString userName = query.value(0).toString();
	 QString priviledge = query.value(1).toString();
	 QString author;
	 if (priviledge == "1")
	 {
		 author = "�����û�";
	 }
	 else if (priviledge == "2")
	 {
		 author = "�߼��û�";
	 }
	 else if (priviledge == "3")
	 {
		 author = "��ͨ�û�";
	 }
	 ui.tableWidget->setItem(index, 0, new QTableWidgetItem(userName));
	 ui.tableWidget->setItem(index, 1, new QTableWidgetItem(author));
	 index++;
	}
}