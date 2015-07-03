#include "importphotothread.h"

ImportPhotoThread::ImportPhotoThread(const QString inPath, QObject *parent)
	: QThread(parent)
{
	path = inPath;
	//Find_JPG_File(inPath);
	count = 1;
}

ImportPhotoThread::~ImportPhotoThread()
{

}

bool ImportPhotoThread::Find_JPG_File(const QString &path)
{
	QDir dir(path);
    if(!dir.exists())
        return -1;
    dir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
    dir.setSorting(QDir::DirsFirst);

    QFileInfoList list = dir.entryInfoList();//, QDir::Dirs|QDir::Files);
	if(list.size()< 1 ) 
	{  
        return -1;  
    }  
    int i=0;
    do
	{
        QFileInfo fileInfo=list.at(i);
        bool bisDir=fileInfo.isDir();
		//qDebug() << fileInfo.fileName();
        if(bisDir)
        {
            Find_JPG_File(fileInfo.filePath());
        }
        else
        {
			bool isJPG = fileInfo.fileName().toLower().endsWith(".jpg");
			if (isJPG)
			{
				QString baseName = fileInfo.baseName();
				QString filePath = fileInfo.filePath();
				hashJPGFiles.insert(baseName, filePath);
			}
        }
        i++;
		count++;
		if (count % 10 == 0) 
		{
			emit completedCount(count);
		}
    }while(i<list.size());

	return true;
}
