#include <QtGui/QPixmap>
#include <QtGui/QBitmap>
#include <QSqlQuery>
#include "toolbutton.h"
#include "shutdown.h"
#include "form.h"

Form::Form(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
  
	this->setWindowModality(Qt::WindowModal);

	QPalette p = palette();
  QPixmap img("welcome.png");
   //QPixmap img("ic.png");
 QBitmap mask("welcome_mask.png");
  // QBitmap mask("ic.png");
    p.setBrush(QPalette::Window, QBrush(img));
    setPalette(p);
    setMask(mask);
    setWindowFlags(Qt::FramelessWindowHint);
    resize(800, 600);
   
	typeLabel = new QLabel(this);
	typeLabel->move(450, 150);
	typeLabel->setText("��¼���ͣ�");
	logonType = new QComboBox(this);
	logonType->move(550, 150);
	
	logonType->addItem("��ͨ�û�", "3");
	logonType->addItem("�߼��û�", "2");
	logonType->addItem("�����û�", "1");

    nameLabel = new QLabel(this);
	nameLabel->move(450, 200);
	nameLabel->setText("�� �� ����");
	userLineEdit = new QLineEdit(this);
	userLineEdit->setFixedSize(100,20);
	userLineEdit->move(550, 200);

	passwordLabel = new QLabel(this);
	passwordLabel->move(450, 250);
	passwordLabel->setText("��    �룺");
	passwordLineEdit = new QLineEdit(this);
	passwordLineEdit->setFixedSize(100,20);
	passwordLineEdit->setEchoMode(QLineEdit::Password);
	passwordLineEdit->move(550, 250);

	ToolButton *button = new ToolButton(this);
    button->move(450, 350);
	Shutdown *sdButton = new Shutdown(this);
	sdButton->move(580, 350);

	enterFlag=false;
	shutdownFlag=false;

	connect(button,SIGNAL(clicked()),this,SLOT(enterButtonClicked()));
	connect(sdButton,SIGNAL(clicked()),this,SLOT(shutdownButtonClicked()));
	connect(userLineEdit,SIGNAL(returnPressed()), this, SLOT(enterButtonClicked()) );
	connect(passwordLineEdit,SIGNAL(returnPressed()), this, SLOT(enterButtonClicked()) );
}

Form::~Form()
{

}

void Form::enterButtonClicked()
{
	QString logonTypeStr = logonType->itemData( logonType->currentIndex() ).toString();
	QString userNameStr = userLineEdit->text();
	QString pwdStr = passwordLineEdit->text();
	QSqlQuery query;
	QString sql = "select name, password, priviledge from user where name = '";
	sql += userNameStr + "' and priviledge = '" + logonTypeStr + "' and password = '" + pwdStr + "'";
	qDebug() << "SQL:" << sql <<endl;
	query.exec(sql);
	if ( query.next() )
	{
        if ( logonTypeStr == "1" )
		{
			QGlobalVar::userType = 1;	//�û�����Ϊ�����û�
			QGlobalVar::currentUser = query.value(0).toString();	//��ǰ�û���
			this->close();
	        enterFlag=true;
		}
		else if ( logonTypeStr == "2" )
		{
            QGlobalVar::userType = 2;    //�û�����Ϊ�߼��û�
			QGlobalVar::currentUser = query.value(0).toString(); //��ǰ�û���
			this->close();
	        enterFlag=true;
		}
		else
		{
			QGlobalVar::userType = 3;    //�û�����Ϊ��ͨ�û�
			QGlobalVar::currentUser = query.value(0).toString(); //��ǰ�û���
			this->close();
	        enterFlag=true;
		}
	}
	else
	{
		QMessageBox::warning(this, "��ʾ", "�û������������", QMessageBox::Ok);
		return;
	}
	
}
void Form::shutdownButtonClicked()
{
	shutdownFlag=true;
	exit(1);
}

void Form::test()
{
}