#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QWidget>
#include <QHash>
#include <QDomElement>
#include <QDomNode>
#include <QDomElement>
#include <QSqlQuery>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDateTime>
#include <QFile>
#include <QSet>
#include <QTextStream>
#include <QDebug>
#include "ui_usermanage.h"
#include "QGlobalVar.h"

class UserManage : public QWidget
{
	Q_OBJECT

public:
	UserManage(QWidget *parent = 0);
	~UserManage();

private:
	Ui::UserManageClass ui;

	QStringList tableHeader;
protected:
	bool isThisUserExist(QString &userName);
	bool isThisUserExist(QString &userName, QString &password);

private slots:
	void on_showAllUsersBtn_clicked();
	void on_delUserBtn_clicked();
	void on_modifyAuthorBtn_clicked();
	void on_addUserBtn_clicked();
};

#endif // USERMANAGE_H
