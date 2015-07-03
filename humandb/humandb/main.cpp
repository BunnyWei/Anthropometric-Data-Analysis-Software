#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>
#include <QPlastiqueStyle>
#include <QMotifStyle>
#include <QCDEStyle>
#include <QCleanlooksStyle>
#include <QPluginLoader>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSplashScreen>
/*
** ����ͳ�ƣ�43657
** humandb *.h 18049
** humandb *.cpp 22331
** io_base *.h|*.cpp 435
** edit_pickpoints *.h|*.cpp 2842
*/
void loadDataToMemory();
int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);

	QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap("hello.png"));
	//splash->setPixmap(QPixmap("./Resources/��������.png"));
	splash->show();

	QSqlDatabase db;
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setPort(3306);
    db.setDatabaseName("database3d");
	db.setUserName("root");
	db.setPassword("1234");
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             db.lastError().text());
        return false;
    }
	db.exec("SET NAMES 'GBK'");
	
	//���ñ���
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
	
	//Set the name of the application
	QCoreApplication::setOrganizationName("whu_sklse");
	QCoreApplication::setApplicationName("humandb");
	//�����ݼ��ص���ʱ����
	loadDataToMemory();

	MainWindow *m = new MainWindow;
	m->showMaximized();
    m->setWindowIcon(QIcon("./Resources/windows.png"));
 
	 //������������
	//splash->finish(f);
	delete splash;
	splash = 0;
	//
	//CDlgLogin *l=new CDlgLogin(); //��½����
	//l->setWindowIcon(QIcon("./images/humanbody.png"));
	//l->show();
	//

	//a.setStyle(new QPlastiqueStyle);
	return a.exec();
}

void loadDataToMemory()
{
	QSqlQuery query;
	query.exec("insert into statisticmemory select * from statistic");
}