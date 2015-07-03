#include "qglobalvar.h"

int QGlobalVar::userType = 1;//此处暂时改为1
QString QGlobalVar::currentUser = "root";

QGlobalVar::QGlobalVar(QObject *parent)
	: QObject(parent)
{

}

QGlobalVar::~QGlobalVar()
{

}
