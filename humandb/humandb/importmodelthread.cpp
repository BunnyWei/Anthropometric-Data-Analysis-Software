#include "importmodelthread.h"

ImportModelThread::ImportModelThread(const QString &inPath, QObject *parent)
	: QThread(parent)
{
	path = inPath;
	count = 1;
}

ImportModelThread::~ImportModelThread()
{

}
bool ImportModelThread::Find_STL_File(const QString &path)
{
	QDir dir(path);
    if (!dir.exists())
        return false;
    dir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
    dir.setSorting(QDir::DirsFirst);

    QFileInfoList list = dir.entryInfoList();//, QDir::Dirs|QDir::Files);
	if (list.size() < 1 ) 
	{  
        return -1;  
    }  
    int i = 0;
    do
	{
        QFileInfo fileInfo=list.at(i);
        bool bisDir=fileInfo.isDir();
		//qDebug() << fileInfo.fileName();
        if(bisDir)
        {
            Find_STL_File(fileInfo.filePath());
        }
        else
        {
			bool isSTL = fileInfo.fileName().toLower().endsWith(".stl");
			if (isSTL)
			{
				parseFileInfo(fileInfo);
			}
        }
        i++;
		count++;
		//if (count%10 == 0)
		{
			emit completedCount(count/200);
		}
    }while(i < list.size());

	return true;
}

void ImportModelThread::parseFileInfo(const QFileInfo &fileInfo)
{
	QString baseName = fileInfo.baseName();
	QString filePath = fileInfo.filePath();
	if ("sitting" == baseName.toLower() || "standard" == baseName.toLower() || "standing" == baseName.toLower()
		|| "lf" == baseName.toLower() || "rf" == baseName.toLower())
	{
		QStringList pathList = filePath.split("/");
		QString number = pathList.at( pathList.size() - 2 );
		Model *pModel = new Model(number, baseName, filePath);
		modelList << pModel;
	}
	else if (fileInfo.fileName().endsWith("H.stl"))
	{
		int length = baseName.size();
		QString number = baseName.left(length - 1);
		Model *pModel = new Model(number, "hand", filePath);
		modelList << pModel;
	}
	else
	{
		Model *pModel = new Model(baseName, "head", filePath);
		modelList << pModel;
	}
}