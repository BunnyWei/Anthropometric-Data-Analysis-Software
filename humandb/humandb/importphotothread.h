#ifndef IMPORTPHOTOTHREAD_H
#define IMPORTPHOTOTHREAD_H

#include <math.h>
#include <QSqlQuery>
#include <QThread>
#include <QFileDialog>
#include <QVariant>
#include <QDebug>
#include <cassert>
//导入照片的路径
class ImportPhotoThread : public QThread
{
	Q_OBJECT
signals:
	void completedCount(int);
public:
	ImportPhotoThread(const QString inPath, QObject *parent = 0);

	~ImportPhotoThread();
private:
	QString path;
	QString sql;
	QSqlQuery query;
	QHash<QString, QString> hashJPGFiles;
	int count;

	bool Find_JPG_File(const QString &path);

	void run()
	{
		Find_JPG_File(path);
		QHashIterator<QString, QString> i(hashJPGFiles);
		while (i.hasNext()) 
		{
			i.next();
			QString fileName = i.key();
			QString filePath = i.value();
			sql = "replace into photoinfo values(?, ?)";
			query.prepare(sql);
			query.addBindValue(fileName);
			query.addBindValue(filePath);
			query.exec();
			count++;

			if (count % 10 == 0) 
			{
				emit completedCount(count);
			}
		}
		emit completedCount(count-1);
		if (count<101)
             emit completedCount(100);
	}
};


#endif // IMPORTPHOTOTHREAD_H
