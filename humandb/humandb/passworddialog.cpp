#include "passworddialog.h"

PasswordDialog::PasswordDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	flag=false;
	cancelFlag=false;
	this->setWindowIcon(QIcon("Resources/password.png"));
	this->setWindowTitle("ÇëÊäÈë¿ÚÁî");

}

PasswordDialog::~PasswordDialog()
{

}


void PasswordDialog::on_okButton_clicked()
{
	QString pwdStr = ui.pwdLineEdit->text();
	if(pwdStr=="1234")
		flag=true;
	else
		flag=false;
	
}

bool PasswordDialog::isPasswordCorrect()
{
	return flag;
}

void PasswordDialog::on_cancelButton_clicked()
{
     cancelFlag=true;
}
bool PasswordDialog::isCancel()
{
	return cancelFlag;
}