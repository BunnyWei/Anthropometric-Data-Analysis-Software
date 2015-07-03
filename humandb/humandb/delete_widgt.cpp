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
	ui.comboBox->addItem("个人");
	ui.comboBox->addItem("全部");

	ui.fenquComboBox->addItem("全部");
	ui.fenquComboBox->addItem("A");
	ui.fenquComboBox->addItem("B");
	ui.fenquComboBox->addItem("C");
	ui.fenquComboBox->addItem("D");
	ui.fenquComboBox->addItem("E");
	ui.fenquComboBox->addItem("F");
	ui.fenquComboBox->addItem("G");

	//ui.measureComboBox->addItem("头部数据", "head");
	ui.measureComboBox->addItem("基本尺寸", "static");
	//ui.measureComboBox->addItem("手部数据", "hand");
	ui.measureComboBox->addItem("功能数据", "func");
	//ui.measureComboBox->addItem("服装数据", "coat");
	ui.measureComboBox->addItem("关节转角", "joint");
	ui.measureComboBox->addItem("操作力", "operate");
	ui.measureComboBox->addItem("运动生理", "sport");
	ui.measureComboBox->addItem("心理数据", "mental");
	//ui.measureComboBox->addItem("问卷调查", "result");

}

DeleteWidgt::~DeleteWidgt()
{

}


void DeleteWidgt::on_deleteButton_clicked()
{
	/*if ( QGlobalVar::userType == 2 )
	{
		QMessageBox::warning(this, "提示", "操作受限！", QMessageBox::Ok);
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
	//msgBox.setText("确定删除吗?");
	//msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	//msgBox.setDefaultButton(QMessageBox::No);
	//int ret = msgBox.exec();

	//if (ret == QMessageBox::No)  return;

	if (type == "个人") {
		sql = "delete from info where number= '" + number +"'";
	}
	else if(fenqu == "全部")
		sql = "delete from info";
	else 
		sql = "delete from info where number like '"+fenqu+"%'";
	query.prepare(sql);
	if(pwdDialog->isCancel()) return;
	if(pwdDialog->isPasswordCorrect())
	{
		if (query.exec()) {
			this->setWindowIcon(QIcon("Resources/删除.png"));
			QMessageBox::warning(this, "删除", "删除成功！");
		}
		else {
			this->setWindowIcon(QIcon("Resources/删除.png"));
			QMessageBox::warning(this, "删除", "无法删除！");
			return;
		}
	}
	else
	{
		this->setWindowIcon(QIcon("Resources/password.png"));
        QMessageBox::warning(this, "提示", "口令输入错误！");
		return;
	}

	delete pwdDialog;

}

void DeleteWidgt::on_comboBox_currentIndexChanged(int)
{
	QString str = ui.comboBox->currentText();
	if (str == "个人") {
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
				this->setWindowIcon(QIcon("Resources/删除.png"));
				QMessageBox::warning(this, "删除", "删除成功！");
				return;
			}
		}
		else
		{
			sql = "delete from " + table;
			isElse = delQuery.exec(sql);
			if (isElse)
			{
				this->setWindowIcon(QIcon("Resources/删除.png"));
				QMessageBox::warning(this, "删除", "删除成功！");
				return;
			}
		}
		this->setWindowIcon(QIcon("Resources/删除.png"));
		QMessageBox::warning(this, "删除", "无法删除！");
		return;
	}
	else
	{
		this->setWindowIcon(QIcon("Resources/password.png"));
        QMessageBox::warning(this, "提示", "口令输入错误！");
		return;
	}

}

