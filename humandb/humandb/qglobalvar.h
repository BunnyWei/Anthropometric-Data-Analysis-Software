#ifndef QGLOBALVAR_H
#define QGLOBALVAR_H

#include <QObject>

class QGlobalVar : public QObject
{
	Q_OBJECT

public:
	QGlobalVar(QObject *parent);
	~QGlobalVar();
	static int  userType; //�û�����
	static QString currentUser;	//��ǰ�û�

private:
	
};

#endif // QGLOBALVAR_H
