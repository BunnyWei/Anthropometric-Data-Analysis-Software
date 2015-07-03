/**************************************************************
** �� ��: ��������в��ݵ�meshModel���Լ�Model��Ӧ�ĵ㡢�ߺ���
****************************************************************/

#ifndef MESHMODEL_H
#define MESHMODEL_H
#include <GL/glew.h>

#include <stdio.h>
#include <time.h>

#include <vcg/simplex/vertex/base.h>
#include <vcg/simplex/vertex/component_ocf.h>
#include <vcg/simplex/edge/base.h>
#include <vcg/simplex/face/base.h>
#include <vcg/simplex/face/component_ocf.h>
#include <vcg/simplex/face/topology.h>

#include <vcg/complex/trimesh/base.h>
#include <vcg/complex/trimesh/update/topology.h>
#include <vcg/complex/trimesh/update/normal.h>
#include <vcg/complex/trimesh/update/flag.h>

#include <wrap/gl/trimesh.h>
#include <wrap/callback.h>
#include <wrap/io_trimesh/io_mask.h>
#include <wrap/io_trimesh/additionalinfo.h>
#include <QList>
#include <QString>
#include <QObject>

class CEdge;
class CFaceO;
class CVertexO;

//Vert Mem Occupancy  --- 40b ---

class CVertexO  : public vcg::VertexSimp2< CVertexO, CEdge, CFaceO,
  vcg::vertex::InfoOcf,           /*  4b */
  vcg::vertex::Coord3f,           /* 12b */
  vcg::vertex::BitFlags,          /*  4b */
  vcg::vertex::Normal3f,          /* 12b */
  vcg::vertex::Qualityf,          /*  4b */
  vcg::vertex::Color4b,           /*  4b */
  vcg::vertex::VFAdjOcf,          /*  0b */
  vcg::vertex::MarkOcf,           /*  0b */
  vcg::vertex::CurvaturefOcf,     /*  0b */
  vcg::vertex::CurvatureDirfOcf,  /*  0b */
  vcg::vertex::RadiusfOcf         /*  0b */
  >{
};


class CEdge : public vcg::EdgeSimp2<CVertexO,CEdge,CFaceO, vcg::edge::EVAdj> {
public:
	inline CEdge(){};
  inline CEdge( CVertexO * v0, CVertexO * v1){ V(0)= v0 ; V(1)= v1;};
  static inline CEdge OrderedEdge(CVertexO* v0,CVertexO* v1){
   if(v0<v1) return CEdge(v0,v1);
   else return CEdge(v1,v0);
	}
};

  //inline CEdge( Edge<CEdge,CVertexO> &e):Edge<CEdge,CVertexO>(e){};


//Face Mem Occupancy  --- 32b ---

class CFaceO    : public vcg::FaceSimp2<  CVertexO, CEdge, CFaceO,
      vcg::face::InfoOcf,              /* 4b */
      vcg::face::VertexRef,            /*12b */
      vcg::face::BitFlags,             /* 4b */
      vcg::face::Normal3f,             /*12b */
      vcg::face::QualityfOcf,          /* 0b */
      vcg::face::MarkOcf,              /* 0b */
      vcg::face::Color4bOcf,           /* 0b */
      vcg::face::FFAdjOcf,             /* 0b */
      vcg::face::VFAdjOcf,             /* 0b */
      vcg::face::WedgeTexCoordfOcf     /* 0b */
    > {};

//�̳ж�Ӧ��base.h�ж����TriMesh
class CMeshO    : public vcg::tri::TriMesh< vcg::vertex::vector_ocf<CVertexO>, vcg::face::vector_ocf<CFaceO> > {
public :
	int sfn; //The number of selected faces.
	//���mesh�еı仯����
	vcg::Matrix44f Tr; // Usually it is the identity. It is applied in rendering and filters can or cannot use it. (most of the filter will ignore this)
  const vcg::Box3f &trBB() {
	static vcg::Box3f bb;
	bb.SetNull();
	bb.Add(Tr,bbox);
		return bb;
	}
};

/*
MeshModel Class
The base class for representing a single mesh.
It contains a single vcg mesh object with some additional information for keeping track of its origin and of what info it has.
*/

class MeshModel 
{
public:
/*
 This enum specify the various simplex components
 It is used in various parts of the framework:
 - to know what elements are currently active and therefore can be saved on a file
 - to know what elements are required by a filter and therefore should be made ready before starting the filter (e.g. if a
 - to know what elements are changed by a filter and therefore should be saved/restored in case of dynamic filters with a preview
	*/
	//������һЩ����Ԫ�ص�״̬��
 	enum MeshElement {
		MM_NONE							= 0x00000000,
		MM_VERTCOORD				= 0x00000001,
		MM_VERTNORMAL				= 0x00000002,
		MM_VERTFLAG					= 0x00000004,
		MM_VERTCOLOR				= 0x00000008,
		MM_VERTQUALITY			= 0x00000010,
		MM_VERTMARK					= 0x00000020,
		MM_VERTFACETOPO			= 0x00000040,
		MM_VERTCURV					= 0x00000080,
		MM_VERTCURVDIR			= 0x00000100,
		MM_VERTRADIUS				= 0x00000200,
		MM_VERTTEXCOORD			= 0x00000400,

		MM_FACEVERT					= 0x00001000,
		MM_FACENORMAL				= 0x00002000,
		MM_FACEFLAG					= 0x00004000,
		MM_FACECOLOR				= 0x00008000,
		MM_FACEQUALITY			= 0x00010000,
		MM_FACEMARK					= 0x00020000,
		MM_FACEFACETOPO			= 0x00040000,
		MM_WEDGTEXCOORD			= 0x00080000,
		MM_WEDGNORMAL				= 0x00100000,
		MM_WEDGCOLOR				= 0x00200000,

// 	SubParts of bits
		MM_VERTFLAGSELECT		= 0x01000000,
		MM_FACEFLAGSELECT		= 0x02000000,
// This part should be deprecated.
		MM_VERTFLAGBORDER		= 0x04000000,
		MM_FACEFLAGBORDER		= 0x08000000,

// Per Mesh Stuff....
		MM_CAMERA						= 0x10000000,

		MM_ALL							= 0xffffffff

	} ;


  CMeshO cm; // ����������

public:
  vcg::GlTrimesh<CMeshO> glw; //����tri..
	std::string fileName;
	int soldierId; //ԭʼģ�͵�Id
	int modelId;  //��׼ģ�͵�Id

	/*

	Bitmask denoting what fields are currently used in the mesh
  it is composed by MeshElement enums.
	it should be changed by only mean the following functions:

	updateDataMask(neededStuff)
	clearDataMask(no_needed_stuff)
	hasDataMask(stuff)

	Note that if an element is active means that is also allocated
	Some unactive elements (vertex color) are usually already allocated
	other elements (FFAdj or curvature data) not necessarily.

	*/

//private:
  int currentDataMask; //��ǰ��״̬mask������ʶ����enum�ж�������״̬
public:
  // Bitmask denoting what fields are loaded/saved
  // it is composed by OR-ing IOM_XXXX enums (defined in tri::io::Mask)
//  int ioMask;

	bool visible; // used in rendering; Needed for toggling on and off the meshes

  //abstract pointer to fileformat's dependent additional info
  AdditionalInfo* addinfo; //io��ʹ�õ� ---- �ļ��Ķ�����Ϣ��

	//���캯��
	MeshModel(const char *meshName=0) {
		//��ʼ������IdΪ-1
		soldierId=0;
		modelId=0;

		glw.m=&cm; //��ʼ��glw

		// These data are always active on the mesh
		// ��ʼ��״̬
		currentDataMask = MM_NONE;
		currentDataMask |= MM_VERTCOORD | MM_VERTNORMAL | MM_VERTFLAG ;
		currentDataMask |= MM_FACEVERT  | MM_FACENORMAL | MM_FACEFLAG ;

		//ioMask= IOM_VERTCOORD | IOM_FACEINDEX | IOM_FLAGS | IOM_VERTNORMAL;

		visible=true; //��ʼ�� �ɼ�
		cm.Tr.SetIdentity(); //��ʼ����ǰ�ľ���
		cm.sfn=0; //the number of selected face = 0 
		if(meshName) fileName=meshName; //��ʼ��meshName
	}

	//����model����Ⱦ
  bool Render(vcg::GLW::DrawMode _dm, vcg::GLW::ColorMode _cm, vcg::GLW::TextureMode _tm)
	{
		// Needed to be defined here for splatrender as long there is no "MeshlabCore" library.
		using namespace vcg;
		glPushMatrix();
		glMultMatrix(cm.Tr); //����ǰ�ľ�����仯�������(ʵ����Ӧ��model�仯)

		//�����Ӧ��colorMode������textureMode�������˵���û�ж�Ӧ��color������Texture��ô��������Ӧ��ģʽΪnone
		if( (_cm == GLW::CMPerFace)  && (!tri::HasPerFaceColor(cm)) ) _cm=GLW::CMNone;
		if( (_tm == GLW::TMPerWedge )&& (!tri::HasPerWedgeTexCoord(cm)) ) _tm=GLW::TMNone;
		if( (_tm == GLW::TMPerWedgeMulti )&& (!tri::HasPerWedgeTexCoord(cm)) ) _tm=GLW::TMNone;
		glw.Draw(_dm,_cm,_tm); //����Ӧ��ģʽ����Draw
		glPopMatrix();
		return true;
	}

  bool RenderSelectedFaces(); //��Ⱦѡ������.


  // This function is roughly equivalent to the updateDataMask,
  // but it takes in input a mask coming from a filetype instead of a filter requirement (like topology etc)
  //ͨ��������ļ��е�mask�������������Ӧ��meshmodel�����״̬λ
  void Enable(int openingFileMask)
  {
		if( openingFileMask & vcg::tri::io::Mask::IOM_WEDGTEXCOORD ) updateDataMask(MM_WEDGTEXCOORD);
		if( openingFileMask & vcg::tri::io::Mask::IOM_VERTCOLOR    ) updateDataMask(MM_VERTCOLOR);
		if( openingFileMask & vcg::tri::io::Mask::IOM_FACECOLOR    ) updateDataMask(MM_FACECOLOR);
		if( openingFileMask & vcg::tri::io::Mask::IOM_VERTRADIUS   ) updateDataMask(MM_VERTRADIUS);
		if( openingFileMask & vcg::tri::io::Mask::IOM_CAMERA				) updateDataMask(MM_CAMERA);
		if( openingFileMask & vcg::tri::io::Mask::IOM_VERTQUALITY	) updateDataMask(MM_VERTQUALITY);
		if( openingFileMask & vcg::tri::io::Mask::IOM_FACEQUALITY	) updateDataMask(MM_FACEQUALITY);
	}
	//�ж�����data mask
  bool hasDataMask(int maskToBeTested)
	{
		return ((currentDataMask & maskToBeTested)!= 0);
	}

  //����neededDataMask���ж�Ӧλ������
  void updateDataMask(int neededDataMask)
  {
	  //������õ���FACEFACETOPO��ô����face��EnableFFAjacencyʹ��������֮���������
		if( ( (neededDataMask & MM_FACEFACETOPO)!=0) && !hasDataMask(MM_FACEFACETOPO) )
		{
			cm.face.EnableFFAdjacency();
			vcg::tri::UpdateTopology<CMeshO>::FaceFace(cm);
		}
		//VERTFACETOPO
		if( ( (neededDataMask & MM_VERTFACETOPO)!=0) && !hasDataMask(MM_VERTFACETOPO) )
		{
			cm.vert.EnableVFAdjacency();
			cm.face.EnableVFAdjacency();
			vcg::tri::UpdateTopology<CMeshO>::VertexFace(cm);
		}
		if( ( (neededDataMask & MM_WEDGTEXCOORD)!=0)	&& !hasDataMask(MM_WEDGTEXCOORD)) 	cm.face.EnableWedgeTex();
		if( ( (neededDataMask & MM_FACECOLOR)!=0)			&& !hasDataMask(MM_FACECOLOR))			cm.face.EnableColor();
		if( ( (neededDataMask & MM_FACEQUALITY)!=0)		&& !hasDataMask(MM_FACEQUALITY))		cm.face.EnableQuality();
		if( ( (neededDataMask & MM_FACEMARK)!=0)			&& !hasDataMask(MM_FACEMARK))				cm.face.EnableMark();
		if( ( (neededDataMask & MM_VERTMARK)!=0)			&& !hasDataMask(MM_VERTMARK))				cm.vert.EnableMark();
		if( ( (neededDataMask & MM_VERTCURV)!=0)			&& !hasDataMask(MM_VERTCURV))				cm.vert.EnableCurvature();
		if( ( (neededDataMask & MM_VERTCURVDIR)!=0)		&& !hasDataMask(MM_VERTCURVDIR))		cm.vert.EnableCurvatureDir();
		if( ( (neededDataMask & MM_VERTRADIUS)!=0)		&& !hasDataMask(MM_VERTRADIUS))			cm.vert.EnableRadius();


		if(  ( (neededDataMask & MM_FACEFLAGBORDER) && !hasDataMask(MM_FACEFLAGBORDER) ) ||
				 ( (neededDataMask & MM_VERTFLAGBORDER) && !hasDataMask(MM_VERTFLAGBORDER) )    )
		{
			if( (currentDataMask & MM_FACEFACETOPO) || (neededDataMask & MM_FACEFACETOPO))
					 vcg::tri::UpdateFlags<CMeshO>::FaceBorderFromFF(cm);
			else vcg::tri::UpdateFlags<CMeshO>::FaceBorderFromNone(cm);
			vcg::tri::UpdateFlags<CMeshO>::VertexBorderFromFace(cm);
		}

		currentDataMask |= neededDataMask;
   }

  //������Ҫ��״̬λ��գ�ͬʱ������Ӧ�ķ���
  void clearDataMask(int unneededDataMask)
  {
		if( ( (unneededDataMask & MM_VERTFACETOPO)!=0)	&& hasDataMask(MM_VERTFACETOPO)) {cm.face.DisableVFAdjacency();
																																											cm.vert.DisableVFAdjacency(); }
		if( ( (unneededDataMask & MM_FACEFACETOPO)!=0)	&& hasDataMask(MM_FACEFACETOPO))	cm.face.DisableFFAdjacency();

		if( ( (unneededDataMask & MM_WEDGTEXCOORD)!=0)	&& hasDataMask(MM_WEDGTEXCOORD)) 	cm.face.DisableWedgeTex();
		if( ( (unneededDataMask & MM_FACECOLOR)!=0)			&& hasDataMask(MM_FACECOLOR))			cm.face.DisableColor();
		if( ( (unneededDataMask & MM_FACEQUALITY)!=0)		&& hasDataMask(MM_FACEQUALITY))		cm.face.DisableQuality();
		if( ( (unneededDataMask & MM_FACEMARK)!=0)			&& hasDataMask(MM_FACEMARK))			cm.face.DisableMark();
		if( ( (unneededDataMask & MM_VERTMARK)!=0)			&& hasDataMask(MM_VERTMARK))			cm.vert.DisableMark();
		if( ( (unneededDataMask & MM_VERTCURV)!=0)			&& hasDataMask(MM_VERTCURV))			cm.vert.DisableCurvature();
		if( ( (unneededDataMask & MM_VERTCURVDIR)!=0)		&& hasDataMask(MM_VERTCURVDIR))		cm.vert.DisableCurvatureDir();
		if( ( (unneededDataMask & MM_VERTRADIUS)!=0)		&& hasDataMask(MM_VERTRADIUS))		cm.vert.DisableRadius();

    currentDataMask = currentDataMask & (~unneededDataMask);
  }
	
	static int io2mm(int single_iobit);

};// end class MeshModel



//ͼ����Ⱦ��ģʽ
class RenderMode
{
public:

	//GLW�е�����mode������Ӧ�������ڱ��ļ��е�GlTrimesh<CMeshO> glw.
  	vcg::GLW::DrawMode	drawMode;
  	vcg::GLW::ColorMode	colorMode;
  	vcg::GLW::TextureMode	textureMode;

    bool lighting;
    bool backFaceCull;
    bool doubleSideLighting;
    bool fancyLighting;
    bool castShadow;
    bool selectedFaces;
    vcg::Point3f lightDir;


		RenderMode()
		{
      drawMode	= vcg::GLW::DMFlat;  //Ĭ�ϵ�����ΪFlat
			colorMode = vcg::GLW::CMNone; //colorΪnone
			textureMode = vcg::GLW::TMNone; //

			lighting = true; //lighting�ƹ��ǿ���
			backFaceCull = false; //������ѡ��Ϊfalse
			doubleSideLighting = false;
			fancyLighting = false;
			castShadow = false;
      selectedFaces=false;
    }
		
}; // end class RenderMode

//����֧��MDI���࣬����һ��meshList�������򿪵�����meshModel
class MeshDocument : public QObject
{
	Q_OBJECT

public:

	MeshDocument(): QObject()
	{
		currentMesh = NULL;
		busy=false;
	}

	//deletes each meshModel
	~MeshDocument()
	{
		foreach(MeshModel *mmp, meshList)
			delete mmp;
	}

	//returns the mesh ata given position in the list
	MeshModel *getMesh(int i)
	{
		return meshList.at(i);
	}

	MeshModel *getMesh(const char *name);

	//set the current mesh to be the one at index i
	void setCurrentMesh(unsigned int i);

	MeshModel *mm() {
		return currentMesh;
	}

	/// The very important member:
	/// The list of MeshModels.
	QList<MeshModel *> meshList;

	int size() const {return meshList.size();}
	bool busy;    // used in processing. To disable access to the mesh by the rendering thread

	//add a new mesh with the given name
	MeshModel *addNewMesh(const char *meshName,MeshModel *newMesh=0);

	//remove the mesh from the list and delete it from memory
	bool delMesh(MeshModel *mmToDel);

  int vn() /// Sum of all the vertices of all the meshes
	{
			int tot=0;
			foreach(MeshModel *mmp, meshList)
					tot+= mmp->cm.vn;
			return tot;
	}
	int fn() {
			int tot=0;
			foreach(MeshModel *mmp, meshList)
					tot+= mmp->cm.fn;
			return tot;
	}

 vcg::Box3f bbox()
 {
		vcg::Box3f FullBBox;
		foreach(MeshModel * mp, meshList)
			FullBBox.Add(mp->cm.Tr,mp->cm.bbox);
		return FullBBox;
 }

	private:
		MeshModel *currentMesh;

	signals:
		//when ever the current mesh changed this will send out the index of the newest mesh
		void currentMeshChanged(int index);

};// end class MeshDocument

/*
	A class designed to save partial aspects of the state of a mesh, such as vertex colors, current selections, vertex positions
	and then be able to restore them later.
	This is a fundamental part for the dynamic filters framework.

	Note: not all the MeshElements are supported!!
*/
//��¼һЩMeshModel��state��
class MeshModelState
{
	public:
	int changeMask; // a bit mask indicating what have been changed. Composed of
	MeshModel *m; // the mesh which the changes refers to.
	std::vector<vcg::Color4b> vertColor;
	std::vector<vcg::Point3f> vertCoord;
	std::vector<vcg::Point3f> vertNormal;
	std::vector<bool> faceSelection;

	//��changeMask��������,Ȼ�����Ӧ��changeMask������Ӧ
	void create(int _mask, MeshModel* _m)
	{
		m=_m;
		changeMask=_mask;
		//�Ըı��mask����Ӧ����Ӧ
		if(changeMask & MeshModel::MM_VERTCOLOR)
		{
			vertColor.resize(m->cm.vert.size());
			std::vector<vcg::Color4b>::iterator ci;
			CMeshO::VertexIterator vi;
			for(vi = m->cm.vert.begin(), ci = vertColor.begin(); vi != m->cm.vert.end(); ++vi, ++ci)
				if(!(*vi).IsD()) (*ci)=(*vi).C();
		}

		if(changeMask & MeshModel::MM_VERTCOORD)
		{
			vertCoord.resize(m->cm.vert.size());
			std::vector<vcg::Point3f>::iterator ci;
			CMeshO::VertexIterator vi;
			for(vi = m->cm.vert.begin(), ci = vertCoord.begin(); vi != m->cm.vert.end(); ++vi, ++ci)
				 if(!(*vi).IsD()) (*ci)=(*vi).P();
		}

		if(changeMask & MeshModel::MM_VERTNORMAL)
		{
			vertNormal.resize(m->cm.vert.size());
			std::vector<vcg::Point3f>::iterator ci;
			CMeshO::VertexIterator vi;
			for(vi = m->cm.vert.begin(), ci = vertNormal.begin(); vi != m->cm.vert.end(); ++vi, ++ci)
				 if(!(*vi).IsD()) (*ci)=(*vi).N();
		}

		if(changeMask & MeshModel::MM_FACEFLAGSELECT)
		{
			faceSelection.resize(m->cm.face.size());
			std::vector<bool>::iterator ci;
			CMeshO::FaceIterator fi;
			for(fi = m->cm.face.begin(), ci = faceSelection.begin(); fi != m->cm.face.end(); ++fi, ++ci)
			{
				if((*fi).IsS())
					(*ci) = true;
				else
					(*ci) = false;
			}
		}
	}
	//ֱ�Ӷ����е�changeMask����Ӧ
	bool apply(MeshModel *_m)
	{
	  if(_m != m) return false;
		if(changeMask & MeshModel::MM_VERTCOLOR)
		{
			if(vertColor.size() != m->cm.vert.size()) return false;
			std::vector<vcg::Color4b>::iterator ci;
			CMeshO::VertexIterator vi;
			for(vi = m->cm.vert.begin(), ci = vertColor.begin(); vi != m->cm.vert.end(); ++vi, ++ci)
				if(!(*vi).IsD()) (*vi).C()=(*ci);
		}

		if(changeMask & MeshModel::MM_VERTCOORD)
		{
			if(vertCoord.size() != m->cm.vert.size()) return false;
			std::vector<vcg::Point3f>::iterator ci;
			CMeshO::VertexIterator vi;
			for(vi = m->cm.vert.begin(), ci = vertCoord.begin(); vi != m->cm.vert.end(); ++vi, ++ci)
				if(!(*vi).IsD()) (*vi).P()=(*ci);
		}

		if(changeMask & MeshModel::MM_VERTNORMAL)
		{
			if(vertNormal.size() != m->cm.vert.size()) return false;
			std::vector<vcg::Point3f>::iterator ci;
			CMeshO::VertexIterator vi;
			for(vi = m->cm.vert.begin(), ci=vertNormal.begin(); vi != m->cm.vert.end(); ++vi, ++ci)
				if(!(*vi).IsD()) (*vi).N()=(*ci);

			//now reset the face normals
			vcg::tri::UpdateNormals<CMeshO>::PerFaceNormalized(m->cm);
		}

		if(changeMask & MeshModel::MM_FACEFLAGSELECT)
		{
			if(faceSelection.size() != m->cm.face.size()) return false;
			std::vector<bool>::iterator ci;
			CMeshO::FaceIterator fi;
			for(fi = m->cm.face.begin(), ci = faceSelection.begin(); fi != m->cm.face.end(); ++fi, ++ci)
			{
				if((*ci))
					(*fi).SetS();
				else
					(*fi).ClearS();
			}
		}
		return true;
  }

	bool isValid(MeshModel *m);

};

#endif