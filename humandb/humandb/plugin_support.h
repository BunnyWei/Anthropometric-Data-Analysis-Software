/**************************************************************
** �ļ�����
** Copyright (c) 2009 ********* MultiPower
** ������:xiejian 
** �� ��: 2009-07-30

** �޸���: 
** �� ��: 
** �޸�������

** �� ��: ��������Ϣ����(IO����и��������Ӧ���ļ���ʽ)

** �汾��1.0
****************************************************************/
#ifndef __MESHLAB_PLUGIN_SUPPORT_H
#define __MESHLAB_PLUGIN_SUPPORT_H


enum TypeIO{IMPORT,EXPORT};
	
void LoadKnownFilters(std::vector<MeshIOInterface*> meshIOPlugins, QStringList &filters, QHash<QString, int> &allKnownFormats, int type);
 
#endif
