/**************************************************************
** 文件名：
** Copyright (c) 2009 ********* MultiPower
** 创建人:刘青峰
** 日 期: 2009-08-03

** 修改人: 
** 日 期: 
** 修改描述：

** 描 述: 头文件，声明login dialog中的方法，ui组件，slots函数,用于登陆。

** 版本：1.0
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
	void createInterface();//创建界面
	void createAction();//创建signal-slot映射，类似于MFC中的消息映射
	bool createConnection();//创建与数据库的连接

private slots: //处理signal的slot函数，类似于MFC中事件处理回调函数
	void login(); //登录
	void cancel(); //取消登录

private:

	/************GUI**********/
	//用户名
	QLabel *userNameLabel;
	QLineEdit *userNameEdit;

	//密码
	QLabel *passwordLabel;
	QLineEdit *passwordEdit;
	
	//记住密码
	QCheckBox *rememberCheckBox;

	//显示错误信息
	QLabel *errorLabel;

	//登录和取消button
	QPushButton *loginButton;
	QPushButton *cancelButton;

	QSqlDatabase db;

};

#endif 