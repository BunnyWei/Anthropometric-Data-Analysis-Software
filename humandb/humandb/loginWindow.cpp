/**************************************************************
** 文件名：
** Copyright (c) 2009 ********* MultiPower
** 创建人:刘青峰
** 日 期: 2009-08-03

** 修改人: 
** 日 期: 
** 修改描述：

** 描 述: 实现loginWindow.h中login dialog中的方法，ui组件，slots函数

** 版本：1.0
****************************************************************/

#include <QtGui>
#include <QString>
#include <QStringList>
#include <QPalette>
#include <QFile>
#include "loginWindow.h"
#include "mainwindow.h"


CDlgLogin::CDlgLogin(QWidget *parent)
	: QDialog(parent)
{
	createInterface();
	createAction();
}



void CDlgLogin::createInterface()
{
	//初始化界面
	userNameLabel=new QLabel(tr("用户名"));
	passwordLabel=new QLabel(tr("密码  "));

	rememberCheckBox=new QCheckBox(tr("记住密码"));

	errorLabel=new QLabel();
	QPalette pa;
	pa.setColor(QPalette::WindowText,Qt::red);
	errorLabel->setPalette(pa);

	userNameEdit=new QLineEdit();
	passwordEdit=new QLineEdit();
	passwordEdit->setEchoMode(QLineEdit::Password);


	loginButton=new QPushButton(tr("登陆"));
	cancelButton=new QPushButton(tr("取消"));

	//布局
	QHBoxLayout *topLayout1 = new QHBoxLayout;
	topLayout1->addWidget(userNameLabel);
	topLayout1->addWidget(userNameEdit);

	QHBoxLayout *topLayout2=new QHBoxLayout;
	topLayout2->addWidget(passwordLabel);
	topLayout2->addWidget(passwordEdit);

	QHBoxLayout *midLayout=new QHBoxLayout;
	midLayout->addWidget(rememberCheckBox);
	midLayout->addWidget(errorLabel);

	QHBoxLayout *bottomLayout=new QHBoxLayout;
	bottomLayout->addWidget(loginButton);
	bottomLayout->addWidget(cancelButton);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout1);
	mainLayout->addLayout(topLayout2);
	mainLayout->addLayout(midLayout);
	mainLayout->addLayout(bottomLayout);
	setLayout(mainLayout);

    setWindowTitle(tr("登陆"));
	resize(200,100);

	//如果记住密码的话,而密码文件只有最新保存的一行
	QFile file("password");
	if(!file.open(QFile::ReadWrite))
		return;

	QTextStream in(&file);

	while(!in.atEnd())
	{
		QString line=in.readLine();
		QStringList sl=line.split(",");
		userNameEdit->setText(sl.at(0));
		passwordEdit->setText(sl.at(1));
		rememberCheckBox->setChecked(true);
	}

	
}


void CDlgLogin::createAction()
{
	connect(loginButton, SIGNAL(clicked()), this, SLOT(login()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
	connect(rememberCheckBox,SIGNAL(stateChanged(int)),this,SLOT(remember()));
}

void CDlgLogin::login()
{
	/*createConnection();*/


	QString userName=userNameEdit->text();
	QString password=passwordEdit->text();

	//记住密码，需要操作password文件
	QFile file("password");
	if(!file.open(QFile::ReadWrite))
		return;

	QTextStream out(&file);
	QTextStream in(&file);

	//根据获取的用户输入的用户名和密码查询数据库
	QSqlQuery query;
	query.prepare("select * from user where username = ?");
	query.bindValue(0,userName);
	query.exec();


	if(!query.size())
	{
		errorLabel->setText("用户名错误");
	}

	while(query.next())
	{
		QString u=query.value(0).toString();
		QString p=query.value(1).toString();
		if(u==userName&&p==password)
		{
			//只有登陆验证通过了才保存密码
			if(rememberCheckBox->checkState()==2)
			{
				//以覆盖的方式，打开文件，类似于新建文件
				QFile file("password");
				if(!file.open(QFile::WriteOnly))
					return;

				out<<userName<<","<<password<<"\n";
			}
			else
			{
				QFile file("password");
				if(!file.open(QFile::WriteOnly))
					return;
			}
			close();//登陆成功后关闭
			MainWindow *m=new MainWindow;
			m->showMaximized();
			m->setWindowIcon(QIcon("./images/humanbody.png"));
			
		}
		else
		{
			errorLabel->setText("密码错误");
		}
	
	}
}

void  CDlgLogin::cancel()
{
	close();
}

//连接数据库
bool CDlgLogin::createConnection()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("xiejian");
	db.setPort(3307);
    db.setDatabaseName("humanbody");
	db.setUserName("root");
	db.setPassword("1234");
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             db.lastError().text());
        return false;
    }
	db.exec("SET NAMES 'GBK'");
    return true;
}