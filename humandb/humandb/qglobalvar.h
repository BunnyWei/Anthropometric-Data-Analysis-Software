#ifndef QGLOBALVAR_H
#define QGLOBALVAR_H

#include <QObject>

class QGlobalVar : public QObject
{
	Q_OBJECT

public:
	QGlobalVar(QObject *parent);
	~QGlobalVar();
	static int  userType; //用户类型
	static QString currentUser;	//当前用户

private:
	
};

#endif // QGLOBALVAR_H
