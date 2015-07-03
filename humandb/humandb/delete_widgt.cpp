#include "delete_widgt.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QList>
#include <QThread>
#include <QFileDialog>
#include <QDomElement>
#include <QMessageBox>
#include "QGlobalVar.h"


DeleteWidgt::DeleteWidgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.comboBox->addItem("����");
	ui.comboBox->addItem("ȫ��");

	ui.fenquComboBox->addItem("ȫ��");
	ui.fenquComboBox->addItem("A");
	ui.fenquComboBox->addItem("B");
	ui.fenquComboBox->addItem("C");
	ui.fenquComboBox->addItem("D");
	ui.fenquComboBox->addItem("E");
	ui.fenquComboBox->addItem("F");
	ui.fenquComboBox->addItem("G");

	//ui.measureComboBox->addItem("ͷ������", "head");
	ui.measureComboBox->addItem("�����ߴ�", "static");
	//ui.measureComboBox->addItem("�ֲ�����", "hand");
	ui.measureComboBox->addItem("��������", "func");
	//ui.measureComboBox->addItem("��װ����", "coat");
	ui.measureComboBox->addItem("�ؽ�ת��", "joint");
	ui.measureComboBox->addItem("������", "operate");
	ui.measureComboBox->addItem("�˶�����", "sport");
	ui.measureComboBox->addItem("��������", "mental");
	//ui.measureComboBox->addItem("�ʾ����", "result");

}

DeleteWidgt::~DeleteWidgt()
{

}


void DeleteWidgt::on_deleteButton_clicked()
{
	/*if ( QGlobalVar::userType == 2 )
	{
		QMessageBox::warning(this, "��ʾ", "�������ޣ�", QMessageBox::Ok);
		return;
	}*/
	QString type = ui.comboBox->currentText();
	QString number = ui.numberLineEdit->text();
	QString fenqu = ui.fenquComboBox->currentText();
	QSqlQuery query;
	QString sql;
	pwdDialog = new PasswordDialog;
	pwdDialog->exec();
	

	QMessageBox msgBox;
	//msgBox.setText("ȷ��ɾ����?");
	//msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	//msgBox.setDefaultButton(QMessageBox::No);
	//int ret = msgBox.exec();

	//if (ret == QMessageBox::No)  return;

	if (type == "����") {
		sql = "delete from info where number= '" + number +"'";
	}
	else if(fenqu == "ȫ��")
		sql = "delete from info";
	else 
		sql = "delete from info where number like '"+fenqu+"%'";
	query.prepare(sql);
	if(pwdDialog->isCancel()) return;
	if(pwdDialog->isPasswordCorrect())
	{
		if (query.exec()) {
			this->setWindowIcon(QIcon("Resources/ɾ��.png"));
			QMessageBox::warning(this, "ɾ��", "ɾ���ɹ���");
		}
		else {
			this->setWindowIcon(QIcon("Resources/ɾ��.png"));
			QMessageBox::warning(this, "ɾ��", "�޷�ɾ����");
			return;
		}
	}
	else
	{
		this->setWindowIcon(QIcon("Resources/password.png"));
        QMessageBox::warning(this, "��ʾ", "�����������");
		return;
	}

	delete pwdDialog;

}

void DeleteWidgt::on_comboBox_currentIndexChanged(int)
{
	QString str = ui.comboBox->currentText();
	if (str == "����") {
		ui.label_2->setVisible(true);
		ui.numberLineEdit->setVisible(true);
		ui.label_2->setStyleSheet("color: red");
		ui.numberLineEdit->setDisabled(false);
		ui.fenquLabel->setVisible(false);
		ui.fenquComboBox->setVisible(false);
	}
	else {
		ui.label_2->setStyleSheet("color: white");
		ui.numberLineEdit->setDisabled(true);
		ui.label_2->setVisible(false);
		ui.numberLineEdit->setVisible(false);
		ui.fenquLabel->setVisible(true);
		ui.fenquComboBox->setVisible(true);
	}
}





void DeleteWidgt::on_measureDelButton_clicked()
{
	QString table = ui.measureComboBox->itemData( ui.measureComboBox->currentIndex() ).toString();
	QSqlQuery delQuery;
	QString sql;
	//if (pwdDialog)
		//delete pwdDialog;
	pwdDialog = new PasswordDialog;
	pwdDialog->exec();  
	
	if(pwdDialog->isCancel()) 
	{
		delete pwdDialog;
		return;
	}
	if(pwdDialog->isPasswordCorrect())
	{
		delete pwdDialog;
		bool isHead, isHand, isStatic, isElse;
		if (table == "static")
		{
			isHead = delQuery.exec("delete from head");
			isHand = delQuery.exec("delete from hand");
			isStatic = delQuery.exec("delete from static");

			if (isHead && isHand && isStatic) 
			{
				this->setWindowIcon(QIcon("Resources/ɾ��.png"));
				QMessageBox::warning(this, "ɾ��", "ɾ���ɹ���");
				return;
			}
		}
		else
		{
			sql = "delete from " + table;
			isElse = delQuery.exec(sql);
			if (isElse)
			{
				this->setWindowIcon(QIcon("Resources/ɾ��.png"));
				QMessageBox::warning(this, "ɾ��", "ɾ���ɹ���");
				return;
			}
		}
		this->setWindowIcon(QIcon("Resources/ɾ��.png"));
		QMessageBox::warning(this, "ɾ��", "�޷�ɾ����");
		return;
	}
	else
	{
		this->setWindowIcon(QIcon("Resources/password.png"));
        QMessageBox::warning(this, "��ʾ", "�����������");
		return;
	}

}

