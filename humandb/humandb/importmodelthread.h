#ifndef IMPORTMODELTHREAD_H
#define IMPORTMODELTHREAD_H

#include <math.h>
#include <QSqlQuery>
#include <QThread>
#include <QFileDialog>
#include <QVariant>
#include <QDebug>
#include <cassert>
class Model
{
public:
	Model(const QString &number, const QString &type, const QString &filePath)
	{
		this->number = number;
		this->type = type;
		this->filePath = filePath;
	}
	QString getNumber() const
	{
		return number;
	}
	QString getType() const
	{
		return type;
	}
	QString getFilePath() const
	{
		return filePath;
	}
private:
	QString number;
	QString type;
	QString filePath;
};

class ImportModelThread : public QThread
{
	Q_OBJECT

signals:
	void completedCount(int);
public:
	ImportModelThread(const QString &inPath, QObject *parent);
	~ImportModelThread();

private:
	QString path;
	QString sql;
	QSqlQuery query;
	QList<Model *> modelList;
	QHash<QString, QString> hashSTLFiles;
	int count;

	bool Find_STL_File(const QString &path);
	void parseFileInfo(const QFileInfo &fileInfo);

	void run()
	{
		Find_STL_File(path);
		//
		for (int i = 0; i < modelList.size(); i++)
		{
			Model *pModel = modelList.at(i);
			QString number = pModel->getNumber();
			QString type = pModel->getType();
			QString filePath = pModel->getFilePath();
			sql = "replace into " + type + "model values(?, ?)";
			query.prepare(sql);
			query.addBindValue(number);
			query.addBindValue(filePath);
			query.exec();
			delete pModel;
			count++;
			if (count % 10 == 0) 
			{
				emit completedCount(count/200);
			}
		}
		emit completedCount(count-1);
		if ((count/200) <= 100)
             emit completedCount(100);
	}
	
};

#endif // IMPORTMODELTHREAD_H
