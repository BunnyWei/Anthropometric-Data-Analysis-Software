#include "qglobalvar.h"

int QGlobalVar::userType = 1;//�˴���ʱ��Ϊ1
QString QGlobalVar::currentUser = "root";

QGlobalVar::QGlobalVar(QObject *parent)
	: QObject(parent)
{

}

QGlobalVar::~QGlobalVar()
{

}
