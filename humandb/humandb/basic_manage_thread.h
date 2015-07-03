#include <qDebug>
#include <QThread>
#include <QListWidget>
#include <QListWidgetItem>
#include "query.h"

class WorkThread : public QThread
{
	Q_OBJECT
signals:
	void complete_count(int);
public:
	WorkThread(QListWidget *listWidget, QObject *parent = 0): QThread(parent) 
	{
		this->listWidget = listWidget;
	};
	~WorkThread() 
	{
	}
private:
	QListWidget *listWidget;
	void generate_statistic_data();
	void db_insert_statistic_data(int item_id, QString &social, QString &sql, Stat &stat);
	QString get_insert_sql();
	void run() 
	{
		generate_statistic_data();
	}
};