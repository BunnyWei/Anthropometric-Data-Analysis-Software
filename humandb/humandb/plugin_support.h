/**************************************************************
** 文件名：
** Copyright (c) 2009 ********* MultiPower
** 创建人:xiejian 
** 日 期: 2009-07-30

** 修改人: 
** 日 期: 
** 修改描述：

** 描 述: 定义插件信息加载(IO插件中各个插件对应的文件格式)

** 版本：1.0
****************************************************************/
#ifndef __MESHLAB_PLUGIN_SUPPORT_H
#define __MESHLAB_PLUGIN_SUPPORT_H


enum TypeIO{IMPORT,EXPORT};
	
void LoadKnownFilters(std::vector<MeshIOInterface*> meshIOPlugins, QStringList &filters, QHash<QString, int> &allKnownFormats, int type);
 
#endif
