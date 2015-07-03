#include "fit_widget.h"
#include <math.h>
#include <QFileDialog>
#include <QThread>


//导出线程类，所有Excel导出的工作都在这个线程完成，同时更新进度条
class ExportFitThread : public QThread
{
	Q_OBJECT
signals:
	void completedCount(int);
public:
	ExportFitThread(QString &filepath, QList<QString> &outDelInfoList, QObject *parent = 0): QThread(parent)
	{
		this->filepath = filepath;
		mDelInfoList = outDelInfoList;
	};
	~ExportFitThread() 
	{
	}
private:
	QString filepath;
	QList<QString> mDelInfoList;

	void run()
	{
		int count = 1;
		QString number;
		QFile file(filepath);
		if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) 
		{
			return;
		}
		QTextStream out(&file);
		out.setCodec("GBK");
        
		out << QString("人员编号\t测量值\t偏离程度\n");

		QList<QString>::const_iterator ci;
		for(ci=mDelInfoList.constBegin(); ci!=mDelInfoList.constEnd(); ++ci)
		{
			QString number = ci->split("\t")[0];
			QString value = ci->split("\t")[1];
			QString deviation = ci->split("\t")[2];
			out << number << "\t" << value << "\t" <<deviation << endl;
			count++;
			if (count % 10 == 0) 
			{
				emit completedCount(count);
			}
		}
		
		emit completedCount(count-1);
		if (count<101)
             emit completedCount(100);
		file.close();
	}
};
