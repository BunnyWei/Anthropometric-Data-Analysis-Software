/**************************************************************
** �ļ�����
** Copyright (c) 2009 ********* MultiPower
** ������:�����
** �� ��: 2009-08-03

** �޸���: 
** �� ��: 
** �޸�������

** �� ��: ͷ�ļ�������login dialog�еķ�����ui�����slots����,���ڵ�½��

** �汾��1.0
****************************************************************/

#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QString>
#include <QSqlQuery>

class QAction;
class QPushButton;
class QLineEdit;
class QLabel;
class QCheckBox;

class CDlgLogin: public QDialog
{
	Q_OBJECT
public:
	CDlgLogin(QWidget *parent = 0);
	~CDlgLogin(){};
	void createInterface();//��������
	void createAction();//����signal-slotӳ�䣬������MFC�е���Ϣӳ��
	bool createConnection();//���������ݿ������

private slots: //����signal��slot������������MFC���¼�����ص�����
	void login(); //��¼
	void cancel(); //ȡ����¼

private:

	/************GUI**********/
	//�û���
	QLabel *userNameLabel;
	QLineEdit *userNameEdit;

	//����
	QLabel *passwordLabel;
	QLineEdit *passwordEdit;
	
	//��ס����
	QCheckBox *rememberCheckBox;

	//��ʾ������Ϣ
	QLabel *errorLabel;

	//��¼��ȡ��button
	QPushButton *loginButton;
	QPushButton *cancelButton;

	QSqlDatabase db;

};

#endif 