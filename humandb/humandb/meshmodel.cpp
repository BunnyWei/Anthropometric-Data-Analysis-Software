/**************************************************************
** 文件名：
** Copyright (c) 2009 ********* MultiPower
** 创建人:xiejian 
** 日 期: 2009-07-30

** 修改人: 
** 日 期: 
** 修改描述：

** 描 述: 实现程序中操纵的meshModel类以及Model对应的点、线和面

** 版本：1.0
****************************************************************/

#include <QString>
#include <QtGlobal>
#include <QFileInfo>
#include <wrap/gl/math.h>
#include "meshmodel.h"

using namespace vcg;
//根据文件名获取对应的mesh
MeshModel *MeshDocument::getMesh(const char *name)
{
	foreach(MeshModel *mmp, meshList)
			{
				QString shortName( QFileInfo(mmp->fileName.c_str()).fileName() );
				if(shortName == name) return mmp;
			}
	assert(0);
	return 0;
}
//设置当前激活的mesh
void MeshDocument::setCurrentMesh(unsigned int i)
{
  assert(i < (unsigned int)meshList.size());
	currentMesh=meshList.at(i);
	emit currentMeshChanged(i);
}
//新建mesh
MeshModel *MeshDocument::addNewMesh(const char *meshName,MeshModel *newMesh)
{
	QString newName=meshName;
//遍历meshlist中的mesh,如果已存在与要新建的mesh重名的mesh,则在新建的mesh名称后面加上"_copy"
	for(QList<MeshModel*>::iterator mmi=meshList.begin();mmi!=meshList.end();++mmi)
	{
		QString shortName( (*mmi)->fileName.c_str() );
		if(shortName == newName)
			newName = newName+"_copy";
	}

	if(newMesh==0)
		newMesh=new MeshModel(qPrintable(newName));
	else
		newMesh->fileName = qPrintable(newName);

	meshList.push_back(newMesh);
	currentMesh=meshList.back();
	emit currentMeshChanged(meshList.size()-1);

	return newMesh;
}
//删除指定mesh
bool MeshDocument::delMesh(MeshModel *mmToDel)
{
	if(meshList.size()==1) return false;

	QMutableListIterator<MeshModel *> i(meshList);

	while (i.hasNext())
	{
		MeshModel *md = i.next();

		if (md==mmToDel)
		{
			i.remove();
			delete mmToDel;
		}
	}

	if(currentMesh == mmToDel)
	{
		setCurrentMesh(0);
		emit currentMeshChanged(0);
	}

	return true;
}
//显示选中的面
bool MeshModel::RenderSelectedFaces()
{
  glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_LIGHTING_BIT | GL_DEPTH_BUFFER_BIT );
  glEnable(GL_POLYGON_OFFSET_FILL);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glDepthMask(GL_FALSE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
  glColor4f(1.0f,0.0,0.0,.3f);
  glPolygonOffset(-1.0, -1);
  CMeshO::FaceIterator fi;
	glPushMatrix();
	glMultMatrix(cm.Tr);glBegin(GL_TRIANGLES);
	cm.sfn=0;//选中的面的数目
	for(fi=cm.face.begin();fi!=cm.face.end();++fi)
    if(!(*fi).IsD() && (*fi).IsS())
    {
  		glVertex((*fi).cP(0));
  		glVertex((*fi).cP(1));
  		glVertex((*fi).cP(2));
			++cm.sfn;
    }
  glEnd();
	glPopMatrix();
	glPopAttrib();
  return true;
}


int MeshModel::io2mm(int single_iobit)
{
	switch(single_iobit) 
	{
		case tri::io::Mask::IOM_NONE					: return  MM_NONE;
		case tri::io::Mask::IOM_VERTCOORD		: return  MM_VERTCOORD;
		case tri::io::Mask::IOM_VERTCOLOR		: return  MM_VERTCOLOR;
		case tri::io::Mask::IOM_VERTFLAGS		: return  MM_VERTFLAG;
		case tri::io::Mask::IOM_VERTQUALITY	: return  MM_VERTQUALITY;
		case tri::io::Mask::IOM_VERTNORMAL		: return  MM_VERTNORMAL;
		case tri::io::Mask::IOM_VERTTEXCOORD : return  MM_VERTTEXCOORD;
		case tri::io::Mask::IOM_VERTRADIUS		: return  MM_VERTRADIUS;
		
		case tri::io::Mask::IOM_FACEINDEX   		: return  MM_FACEVERT  ;
		case tri::io::Mask::IOM_FACEFLAGS   		: return  MM_FACEFLAG  ;
		case tri::io::Mask::IOM_FACECOLOR   		: return  MM_FACECOLOR  ;
		case tri::io::Mask::IOM_FACEQUALITY 		: return  MM_FACEQUALITY;
		case tri::io::Mask::IOM_FACENORMAL  		: return  MM_FACENORMAL ;
		
		case tri::io::Mask::IOM_WEDGTEXCOORD 		: return  MM_WEDGTEXCOORD;
		case tri::io::Mask::IOM_WEDGCOLOR				: return  MM_WEDGCOLOR;
		case tri::io::Mask::IOM_WEDGNORMAL   		: return  MM_WEDGNORMAL  ;

		default:
			assert(0);
			return MM_NONE;  // FIXME: Returning this is not the best solution (!)
			break;
	} ;
}

