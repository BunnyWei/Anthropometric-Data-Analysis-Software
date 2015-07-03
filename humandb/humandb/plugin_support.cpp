/**************************************************************
** �� ��:ʵ�ֲ����Ϣ����(IO����и��������Ӧ���ļ���ʽ)
****************************************************************/

#include <QtCore>
#include <QString>
#include <QObject>
#include <QApplication>

#include <QtGui>
#include <QHash>
#include <QProgressBar>

#include "meshmodel.h"
#include "interfaces.h"

enum TypeIO{IMPORT,EXPORT};
//��������ļ��ĸ�ʽ������,ʶ��Ϸ��ĸ�ʽ,���뵽filters�б���
void LoadKnownFilters(std::vector<MeshIOInterface*> meshIOPlugins, QStringList &filters, QHash<QString, int> &allKnownFormats, int type)
{
	QString allKnownFormatsFilter = QObject::tr("All known formats ("); 
	std::vector<MeshIOInterface*>::iterator itIOPlugin = meshIOPlugins.begin();
	int i = 0;
	for (int i = 0; itIOPlugin != meshIOPlugins.end(); ++itIOPlugin, ++i)  // cycle among loaded IO plugins
	{
		MeshIOInterface* pMeshIOPlugin = *itIOPlugin;

		QList<MeshIOInterface::Format> currentFormats;// = pMeshIOPlugin->formats();
		switch(type){ 
		  case IMPORT :	currentFormats = pMeshIOPlugin->importFormats(); break;
		  case EXPORT : currentFormats = pMeshIOPlugin->exportFormats(); break;
		  default :assert(0); // unknown filter type
		}

		QList<MeshIOInterface::Format>::iterator itFormat = currentFormats.begin();
		while(itFormat != currentFormats.end())
		{
			MeshIOInterface::Format currentFormat = *itFormat;

			QString currentFilterEntry = currentFormat.description + " (";

			QStringListIterator itExtension(currentFormat.extensions);
			while (itExtension.hasNext())
			{
				QString currentExtension = itExtension.next().toLower();
				if (!allKnownFormats.contains(currentExtension))
				{
					allKnownFormats.insert(currentExtension, i+1);
					allKnownFormatsFilter.append(QObject::tr(" *."));
					allKnownFormatsFilter.append(currentExtension);
				}
				currentFilterEntry.append(QObject::tr(" *."));
				currentFilterEntry.append(currentExtension);
			}
			currentFilterEntry.append(')');
			filters.append(currentFilterEntry);
			qDebug() << "currentFilterEntry:" << currentFilterEntry;

			++itFormat;
		}//while(itFormat != currentFormats.end())
	}
	allKnownFormatsFilter.append(')');
	filters.push_front(allKnownFormatsFilter);

	QHash<QString, int>::iterator it = allKnownFormats.begin();
    while (it != allKnownFormats.end()) 
	{
		qDebug() << "allKnownFormats:" << it.key() << ": " << it.value();
		++it;
    }
}
