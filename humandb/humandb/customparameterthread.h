#include <math.h>
#include <QWidget>
#include <QSqlQuery>
#include <QThread>
#include <QVariant>
#include <QDebug>
#include <cassert>


//添加新的测量参数
class CustomParameterThread : public QThread
{
	Q_OBJECT
signals:
	void completedCount(int);
public:
	CustomParameterThread(QString inTable, QString inSql, QString inItemNumber, QObject *parent = 0): QThread(parent)
	{
		this->sql = inSql;
		this->table = inTable;
		this->itemNumber = inItemNumber;
	};
	~CustomParameterThread() 
	{
	}
private:
	QString sql;
	QString table;
	QString itemNumber;
	QSqlQuery query;
	QSqlQuery updateQuery;

	void run()
	{
		int count = 1;
		QString number;
		float customValue;
		//query.exec(sql);
        bool b = query.exec(sql);
		//当为除法时，无法读取数据？？？？
	   /* bool bnext = query.next();
		qDebug() << "bnext" << bnext;*/
		while (query.next())
		{
			number = query.value(0).toString();
			customValue = query.value(1).toString().toFloat();
			QString updateSql = "update " + table + " set " + itemNumber + " = " + QString("%1").arg(customValue);
			updateSql += " where number = '" + number + "'";
			qDebug() << "updateSql" << updateSql;
			updateQuery.prepare(updateSql);
			updateQuery.exec();
			count++;
			if (count % 10 ==0) 
			{
				emit completedCount(count);
			}
		}
		
		emit completedCount(count-1);
		if (count<101)
             emit completedCount(100);
	}
};
