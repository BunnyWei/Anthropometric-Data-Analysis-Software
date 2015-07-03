/**************************************************************
** �ļ�����
** Copyright (c) 2009 ********* MultiPower
** ������:�����
** �� ��: 2009-08-03

** �޸���: 
** �� ��: 
** �޸�������

** �� ��: ʵ��loginWindow.h��login dialog�еķ�����ui�����slots����

** �汾��1.0
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
	//��ʼ������
	userNameLabel=new QLabel(tr("�û���"));
	passwordLabel=new QLabel(tr("����  "));

	rememberCheckBox=new QCheckBox(tr("��ס����"));

	errorLabel=new QLabel();
	QPalette pa;
	pa.setColor(QPalette::WindowText,Qt::red);
	errorLabel->setPalette(pa);

	userNameEdit=new QLineEdit();
	passwordEdit=new QLineEdit();
	passwordEdit->setEchoMode(QLineEdit::Password);


	loginButton=new QPushButton(tr("��½"));
	cancelButton=new QPushButton(tr("ȡ��"));

	//����
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

    setWindowTitle(tr("��½"));
	resize(200,100);

	//�����ס����Ļ�,�������ļ�ֻ�����±����һ��
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

	//��ס���룬��Ҫ����password�ļ�
	QFile file("password");
	if(!file.open(QFile::ReadWrite))
		return;

	QTextStream out(&file);
	QTextStream in(&file);

	//���ݻ�ȡ���û�������û����������ѯ���ݿ�
	QSqlQuery query;
	query.prepare("select * from user where username = ?");
	query.bindValue(0,userName);
	query.exec();


	if(!query.size())
	{
		errorLabel->setText("�û�������");
	}

	while(query.next())
	{
		QString u=query.value(0).toString();
		QString p=query.value(1).toString();
		if(u==userName&&p==password)
		{
			//ֻ�е�½��֤ͨ���˲ű�������
			if(rememberCheckBox->checkState()==2)
			{
				//�Ը��ǵķ�ʽ�����ļ����������½��ļ�
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
			close();//��½�ɹ���ر�
			MainWindow *m=new MainWindow;
			m->showMaximized();
			m->setWindowIcon(QIcon("./images/humanbody.png"));
			
		}
		else
		{
			errorLabel->setText("�������");
		}
	
	}
}

void  CDlgLogin::cancel()
{
	close();
}

//�������ݿ�
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