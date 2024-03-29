/****************************************************************************
* VCGLib                                                            o o     *
* Visual and Computer Graphics Library                            o     o   *
*                                                                _   O  _   *
* Copyright(C) 2004                                                \/)\/    *
* Visual Computing Lab                                            /\/|      *
* ISTI - Italian National Research Council                           |      *
*                                                                    \      *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/

/*
Function: 本文件定义了两个类 GLW 以及一个继承GLW的含有模板的类 GlTrimesh.
1) GLW中定义了四大mode： DrawMode ,NormalMode,ColorMode和TextureMode。用来表示Render过程中各个层面的模式。
		定义了change，Hint以及相关的参数  ??具体参数的意义不清楚
2) GlTrimesh除了GLW中定义的相关变量之外，定义了操作hint等参数的方法
			同时添加了具体的MESH_TYPE作为模板类型，实现在MeshModel中的交互作用
			定义了不同DrawMode,ColorMode和TextureMode对应的Draw方法---- meshlab程序中render菜单下面的rendermode的几大功能都是由这些draw方法具体实现的
Time: 2009-07-08
Author: xiejian
*/





#ifndef __VCG_GLTRIMESH
#define __VCG_GLTRIMESH

#include <queue>
#include <vector>

//#include <GL/glew.h>
#include <wrap/gl/space.h>
#include <wrap/gl/math.h>
#include <vcg/space/color4.h>

namespace vcg {


// classe base di glwrap usata solo per poter usare i vari drawmode, normalmode senza dover
// specificare tutto il tipo (a volte lunghissimo)
// della particolare classe glwrap usata.
class GLW
{
public:
	//定义一些绘制、着色和贴图的模式.
	enum DrawMode	{DMNone, DMBox, DMPoints, DMWire, DMHidden, DMFlat, DMSmooth, DMFlatWire, DMRadar, DMLast} ; //其中的
	enum NormalMode	{NMNone, NMPerVert, NMPerFace, NMPerWedge, NMLast}; //法向量的绘制模型
	enum ColorMode	{CMNone, CMPerMesh, CMPerFace, CMPerVert, CMLast};
	enum TextureMode{TMNone, TMPerVert, TMPerWedge, TMPerWedgeMulti};
	enum Hint { //?? for what?
		HNUseTriStrip		  = 0x0001,				// ha bisogno che ci sia la fftopology gia calcolata!
//		HNUseEdgeStrip		  = 0x0002,			//
		HNUseDisplayList	  = 0x0004,
		HNCacheDisplayList	  = 0x0008,		// Each mode has its dl;
		HNLazyDisplayList	  = 0x0010,			// Display list are generated only when requested
		HNIsTwoManifold		  = 0x0020,			// There is no need to make DetachComplex before .
		HNUsePerWedgeNormal	  = 0x0040,		//
		HNHasFFTopology       = 0x0080,		// E' l'utente che si preoccupa di tenere aggiornata la topologia ff
		HNHasVFTopology       = 0x0100,		// E' l'utente che si preoccupa di tenere aggiornata la topologia vf
		HNHasVertNormal       = 0x0200,		// E' l'utente che si preoccupa di tenere aggiornata le normali per faccia
		HNHasFaceNormal       = 0x0400,		// E' l'utente che si preoccupa di tenere aggiornata le normali per vertice
		HNUseVArray           = 0x0800,
		HNUseLazyEdgeStrip	  = 0x1000,		// Edge Strip are generated only when requested
		HNUseVBO              = 0x2000,		// Use Vertex Buffer Object
		HNIsPolygonal         = 0x4000    // In wireframe modes, hide faux edges
	};

	enum Change { //??for what
		CHVertex		= 0x01,
		CHNormal		= 0x02,
		CHColor			= 0x04,
		CHFace			= 0x08,
		CHFaceNormal	= 0x10,
		CHRender        = 0x20,
		CHAll			= 0xff
	};
	enum HintParami {
		HNPDisplayListSize =0
	};
	enum HintParamf {
		HNPCreaseAngle =0,	// crease angle in radians
		HNPZTwist = 1,				// Z offset used in Flatwire and hiddenline modality
		HNPPointSize = 2		// the point size used in point rendering
	};

	//??for what?
	template<class MESH_TYPE>
	class VertToSplit
	{
	public:
		typename MESH_TYPE::face_base_pointer f;
		char z;
		char edge;
		bool newp;
		typename MESH_TYPE::vertex_pointer v;
	};

	// GL Array Elemet
	class GLAElem {
	public :
		int glmode;
		int len;
		int start;
	};


};

//定义了一个mesh的集合。其中包含hint参数以及GLW中定义的几个mode.
//在MeshModel里面得到使用
template <class MESH_TYPE,  bool partial = false , class FACE_POINTER_CONTAINER = std::vector<typename MESH_TYPE::FacePointer> >
class GlTrimesh : public GLW
{
public:

	typedef MESH_TYPE mesh_type;
	FACE_POINTER_CONTAINER face_pointers;


	std::vector<unsigned int> TMId;
	unsigned int array_buffers[3];

	int curr_hints;      // the current hints

	// The parameters of hints
	int   HNParami[8];
	float HNParamf[8];

	MESH_TYPE *m;
	GlTrimesh()
	{
		m=0;
		dl=0xffffffff;
		curr_hints=HNUseLazyEdgeStrip;
		cdm=DMNone;
		ccm=CMNone;
		cnm=NMNone;

		SetHintParamf(HNPCreaseAngle,float(M_PI/5));
		SetHintParamf(HNPZTwist,0.00005f);
		SetHintParamf(HNPPointSize,1.0f);
	}

	~GlTrimesh()
	{
		//Delete the VBOs
		if(curr_hints&HNUseVBO)
		{
			for(int i=0;i<3;++i)
				if(glIsBuffer(array_buffers[i]))
					glDeleteBuffersARB(1, (GLuint *)(array_buffers+i));
		}
	}

	void SetHintParami(const HintParami hip, const int value)
	{
		HNParami[hip]=value;
	}
	int GetHintParami(const HintParami hip) const
	{
		return HNParami[hip];
	}
	void SetHintParamf(const HintParamf hip, const float value)
	{
		HNParamf[hip]=value;
	}
	float GetHintParamf(const HintParamf hip) const
	{
		return HNParamf[hip];
	}
	void SetHint(Hint hn)
	{
		curr_hints |= hn;
	}
	void ClearHint(Hint hn)
	{
		curr_hints&=(~hn);
	}

	unsigned int dl;
	std::vector<unsigned int> indices;

	DrawMode cdm; // Current DrawMode
	NormalMode cnm; // Current NormalMode
	ColorMode ccm; // Current ColorMode

void Update(/*Change c=CHAll*/)
{
	if(m==0) return;

	if(curr_hints&HNUseVArray || curr_hints&HNUseVBO)
	{
		typename MESH_TYPE::FaceIterator fi;
		indices.clear();
		for(fi = m->face.begin(); fi != m->face.end(); ++fi)
		{
			indices.push_back((unsigned int)((*fi).V(0) - &(*m->vert.begin())));
			indices.push_back((unsigned int)((*fi).V(1) - &(*m->vert.begin())));
			indices.push_back((unsigned int)((*fi).V(2) - &(*m->vert.begin())));
		}

		if(curr_hints&HNUseVBO)
		{
			if(!glIsBuffer(array_buffers[1]))
				glGenBuffers(2,(GLuint*)array_buffers);
			glBindBuffer(GL_ARRAY_BUFFER,array_buffers[0]);
			glBufferData(GL_ARRAY_BUFFER_ARB, m->vn * sizeof(typename MESH_TYPE::VertexType),
				(char *)&(m->vert[0].P()), GL_STATIC_DRAW_ARB);

			glBindBuffer(GL_ARRAY_BUFFER,array_buffers[1]);
			glBufferData(GL_ARRAY_BUFFER_ARB, m->vn * sizeof(typename MESH_TYPE::VertexType),
				(char *)&(m->vert[0].N()), GL_STATIC_DRAW_ARB);
		}

		glVertexPointer(3,GL_FLOAT,sizeof(typename MESH_TYPE::VertexType),0);
		glNormalPointer(GL_FLOAT,sizeof(typename MESH_TYPE::VertexType),0);
	}

	//int C=c;
	//if((C&CHVertex) || (C&CHFace)) {
	//	ComputeBBox(*m);
	//	if(!(curr_hints&HNHasFaceNormal)) m->ComputeFaceNormal();
	//	if(!(curr_hints&HNHasVertNormal)) m->ComputeVertexNormal();
	//	C= (C | CHFaceNormal);
	//}
	//if((C&CHFace) && (curr_hints&HNUseEdgeStrip)) 		 ComputeEdges();
	//if((C&CHFace) && (curr_hints&HNUseLazyEdgeStrip)) ClearEdges();
	//if(MESH_TYPE::HasFFTopology())
	//	if((C&CHFace) && (curr_hints&HNUseTriStrip)) 		{
	//			if(!(curr_hints&HNHasFFTopology)) m->FFTopology();
	//			ComputeTriStrip();
	//		}
	//if((C&CHFaceNormal) && (curr_hints&HNUsePerWedgeNormal))		{
	//	  if(!(curr_hints&HNHasVFTopology)) m->VFTopology();
	//		CreaseWN(*m,MESH_TYPE::scalar_type(GetHintParamf(HNPCreaseAngle)));
	//}
	//if(C!=0) { // force the recomputation of display list
	//	cdm=DMNone;
	//	ccm=CMNone;
	//	cnm=NMNone;
	//}
	//if((curr_hints&HNUseVArray) && (curr_hints&HNUseTriStrip))
	//	{
	//	 ConvertTriStrip<MESH_TYPE>(*m,TStrip,TStripF,TStripVED,TStripVEI);
	//	}
}

//为何要用这种方式来层层递进的Draw?
void Draw(DrawMode dm ,ColorMode cm, TextureMode tm)
{
	switch(dm)
	{
		case	DMNone    : Draw<DMNone    >(cm,tm); break;
		case	DMBox     : Draw<DMBox     >(cm,tm); break;
		case	DMPoints  : Draw<DMPoints  >(cm,tm); break;
		case	DMWire    : Draw<DMWire    >(cm,tm); break;
		case	DMHidden  : Draw<DMHidden  >(cm,tm); break;
		case	DMFlat    : Draw<DMFlat    >(cm,tm); break;
		case	DMSmooth  : Draw<DMSmooth  >(cm,tm); break;
		case	DMFlatWire: Draw<DMFlatWire>(cm,tm); break;
		default : break;
	}
}

template< DrawMode dm >
void Draw(ColorMode cm, TextureMode tm)
{
	switch(cm)
	{
		case	CMNone    : Draw<dm,CMNone   >(tm); break;
		case	CMPerMesh : Draw<dm,CMPerMesh>(tm); break;
		case	CMPerFace : Draw<dm,CMPerFace>(tm); break;
		case	CMPerVert : Draw<dm,CMPerVert>(tm); break;
		default : break;
	}
}

template< DrawMode dm, ColorMode cm >
void Draw(TextureMode tm)
{
	switch(tm)
	{
		case	TMNone          : Draw<dm,cm,TMNone          >(); break;
		case	TMPerVert       : Draw<dm,cm,TMPerVert       >(); break;
		case	TMPerWedge      : Draw<dm,cm,TMPerWedge      >(); break;
		case	TMPerWedgeMulti : Draw<dm,cm,TMPerWedgeMulti >(); break;
		default : break;
	}
}



template< DrawMode dm, ColorMode cm, TextureMode tm>
void Draw()
{
	if(!m) return;
	if((curr_hints & HNUseDisplayList)){
				if (cdm==dm && ccm==cm){
						glCallList(dl);
						return;
				}
				else {
					if(dl==0xffffffff) dl=glGenLists(1);
					glNewList(dl,GL_COMPILE);
				}
	}

	glPushMatrix();
	switch(dm)
		{
			case DMNone		  : break;
			case DMBox		  : DrawBBox(cm);break;					//bounding box.
			case DMPoints   : DrawPoints<NMPerVert,cm>();break;		//points.
			case DMHidden		:	DrawHidden();break;				//hidden lines.
			case DMFlat			:	DrawFill<NMPerFace,cm,tm>();break; //flat --->将Texture后的Model中的线条消除 
			case DMFlatWire :	DrawFlatWire<NMPerFace,cm,tm>();break; //flat lines (fill the face with common texture.)
			case DMRadar		:	DrawRadar<NMPerFace,cm>();break; //
			case DMWire		  :	DrawWire<NMPerVert,cm>();break;		//wireframe
			case DMSmooth   : DrawFill<NMPerVert,cm,tm>();break;	//Smooth. 设置PerVert实现smooth
			default : break;
		}
	glPopMatrix();

	if((curr_hints & HNUseDisplayList)){
		cdm=dm;
		ccm=cm;
		glEndList();
		glCallList(dl);
	}
}


/*********************************************************************************************/
/*********************************************************************************************/

//绘制三角平面，然后填充给定的texture
template <NormalMode nm, ColorMode cm, TextureMode tm>
void DrawFill()
{
	typename FACE_POINTER_CONTAINER::iterator fp;

	typename MESH_TYPE::FaceIterator fi; //FaceIterator 


	typename std::vector<typename MESH_TYPE::FaceType*>::iterator fip;
	short curtexname=-1;

	if(cm == CMPerMesh) //如果是PerMesh的话那么就直接一个颜色着色即可
		glColor(m->C());

	if(tm == TMPerWedge || tm == TMPerWedgeMulti )
		glDisable(GL_TEXTURE_2D);

	if(curr_hints&HNUseVBO)
	{
		if( (cm==CMNone) || (cm==CMPerMesh) )
		{
			if (nm==NMPerVert)
				glEnableClientState (GL_NORMAL_ARRAY);
			glEnableClientState (GL_VERTEX_ARRAY);

			if (nm==NMPerVert)
			{
				glBindBuffer(GL_ARRAY_BUFFER,array_buffers[1]); //绑定一个缓冲区
				glNormalPointer(GL_FLOAT,sizeof(typename MESH_TYPE::VertexType),0);
			}
			glBindBuffer(GL_ARRAY_BUFFER,array_buffers[0]);
			glVertexPointer(3,GL_FLOAT,sizeof(typename MESH_TYPE::VertexType),0) ; //define a array of vertex data
			glDrawElements(GL_TRIANGLES ,m->fn*3,GL_UNSIGNED_INT, &(*indices.begin()) ); //从数组中绘制基本的元素(这里面是triangle)。meshlab里面以三角形作为平面的构建基础
			glDisableClientState (GL_VERTEX_ARRAY);
			if (nm==NMPerVert)
				glDisableClientState (GL_NORMAL_ARRAY);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			return;

		}
	}

	if(curr_hints&HNUseVArray)
	{
		if( (cm==CMNone) || (cm==CMPerMesh) )
		{
			if (nm==NMPerVert)
				glEnableClientState (GL_NORMAL_ARRAY);
			glEnableClientState (GL_VERTEX_ARRAY);

			if (nm==NMPerVert)
				glNormalPointer(GL_FLOAT,sizeof(typename MESH_TYPE::VertexType),&(m->vert.begin()->N()[0]));
			glVertexPointer(3,GL_FLOAT,sizeof(typename MESH_TYPE::VertexType),&(m->vert.begin()->P()[0]));

			glDrawElements(GL_TRIANGLES ,m->fn*3,GL_UNSIGNED_INT, &(*indices.begin()) );
			glDisableClientState (GL_VERTEX_ARRAY);
			if (nm==NMPerVert)
				glDisableClientState (GL_NORMAL_ARRAY);

			return;
		}
	}
	else

 	if(curr_hints&HNUseTriStrip)
	{
		//if( (nm==NMPerVert) && ((cm==CMNone) || (cm==CMPerMesh)))
		//	if(curr_hints&HNUseVArray){
		//		glEnableClientState (GL_NORMAL_ARRAY  );
		//		glNormalPointer(GL_FLOAT,sizeof(MESH_TYPE::VertexType),&(m->vert[0].cN()));
		//		glEnableClientState (GL_VERTEX_ARRAY);
		//		glVertexPointer(3,GL_FLOAT,sizeof(MESH_TYPE::VertexType),&(m->vert[0].cP()));
		//		std::vector<GLAElem>::iterator vi;
		//		for(vi=TStripVED.begin();vi!=TStripVED.end();++vi)
		//					glDrawElements(vi->glmode ,vi->len,GL_UNSIGNED_SHORT,&TStripVEI[vi->start] );
		//
		//		glDisableClientState (GL_NORMAL_ARRAY  );
		//		glDisableClientState (GL_VERTEX_ARRAY);
		//		return;
		//	}

		//std::vector< MESH_TYPE::VertexType *>::iterator vi;
		//glBegin(GL_TRIANGLE_STRIP);
		//if(nm == NMPerFace) fip=TStripF.begin();

		//for(vi=TStrip.begin();vi!=TStrip.end(); ++vi){
		//	if((*vi)){
		//		if(nm==NMPerVert) glNormal((*vi)->cN());
		//		if(nm==NMPerFace) glNormal((*fip)->cN());
		//		glVertex((*vi)->P());
		//		}
		//	else
		//		{
		//			glEnd();
		//			glBegin(GL_TRIANGLE_STRIP);
		//		}
		//	if(nm == NMPerFace) ++fip;
		//	}
		//glEnd();
	}
 	else
	{
		if(partial) //partial 用来做什么控制?
			fp = face_pointers.begin();
		else
			fi = m->face.begin(); //两个面集到底有什么区别??

		if(tm==TMPerWedgeMulti)
		{
			curtexname=(*fi).WT(0).n();
			if (curtexname >= 0)
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,TMId[curtexname]);
			}
			else
			{
				glDisable(GL_TEXTURE_2D);
			}
		}

		glBegin(GL_TRIANGLES);

		while( (partial)?(fp!=face_pointers.end()):(fi!=m->face.end()))
		{
 			typename MESH_TYPE::FaceType & f = (partial)?(*(*fp)): *fi;

			if(!f.IsD())
			{
				if(tm==TMPerWedgeMulti)
				if(f.WT(0).n() != curtexname)
				{
					curtexname=(*fi).WT(0).n();
					glEnd();

					if (curtexname >= 0)
					{
						glEnable(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D,TMId[curtexname]); //进行贴图的绑定
					}
					else
					{
						glDisable(GL_TEXTURE_2D);
					}

					glBegin(GL_TRIANGLES);
				}

				if(nm == NMPerFace)	glNormal(f.cN());
				if(nm == NMPerVert)	glNormal(f.V(0)->cN());
				if(nm == NMPerWedge)glNormal(f.WN(0));

				if(cm == CMPerFace)	glColor(f.C());
				if(cm == CMPerVert)	glColor(f.V(0)->C());
//				if(tm==TMPerVert) glTexCoord(f.V(0)->T());
				if( (tm==TMPerWedge)||(tm==TMPerWedgeMulti) )glTexCoord(f.WT(0).t(0));
				glVertex(f.V(0)->P());

				if(nm == NMPerVert)	glNormal(f.V(1)->cN());
				if(nm == NMPerWedge)glNormal(f.WN(1));
				if(cm == CMPerVert)	glColor(f.V(1)->C());
//				if(tm==TMPerVert) glTexCoord(f.V(1)->T());
				if( (tm==TMPerWedge)|| (tm==TMPerWedgeMulti)) glTexCoord(f.WT(1).t(0));
				glVertex(f.V(1)->P());

				if(nm == NMPerVert)	glNormal(f.V(2)->cN());
				if(nm == NMPerWedge)glNormal(f.WN(2));
				if(cm == CMPerVert) glColor(f.V(2)->C());
	//			if(tm==TMPerVert) glTexCoord(f.V(2)->T());
				if( (tm==TMPerWedge)|| (tm==TMPerWedgeMulti)) glTexCoord(f.WT(2).t(0));
				glVertex(f.V(2)->P());
			}

			if(partial)
				++fp;
			else
				++fi;
		}

		glEnd();

	}
}

// A draw wireframe that hides faux edges
//绘制没有内部边的构成平面的多边形.
//通过从Model中获取相应的面，面上的三个点每两个以直线为绘制基本单位。从而绘制没有内部边的平面多边形
template <NormalMode nm, ColorMode cm>
void DrawWirePolygonal()
{
	typename MESH_TYPE::FaceIterator fi;
	typename FACE_POINTER_CONTAINER::iterator fp;

	typename std::vector<typename MESH_TYPE::FaceType*>::iterator fip;

	if(cm == CMPerMesh)
		glColor(m->C());

	{
		if(partial) //??partial作用是?
			fp = face_pointers.begin();
		else
			fi = m->face.begin();

		glBegin(GL_LINES); //treat each pair of vertices as a independent line.

		while( (partial)?(fp!=face_pointers.end()):(fi!=m->face.end()))
		{
 			typename MESH_TYPE::FaceType & f = (partial)?(*(*fp)): *fi;

			if(!f.IsD())
			{

				if(nm == NMPerFace)	glNormal(f.cN());
				if(cm == CMPerFace)	glColor(f.C());
				
				if (!f.IsF(0)) { //isF---用来判断给定的边是否是内部边，通常应用于被分割成三角形的的对变形中内部边的判断。
				  if(nm == NMPerVert)	glNormal(f.V(0)->cN());
          if(nm == NMPerWedge)glNormal(f.WN(0));
				  if(cm == CMPerVert)	glColor(f.V(0)->C());
				  glVertex(f.V(0)->P()); //f.V(0)

				  if(nm == NMPerVert)	glNormal(f.V(1)->cN());
				  if(nm == NMPerWedge)glNormal(f.WN(1));
				  if(cm == CMPerVert)	glColor(f.V(1)->C());
				  glVertex(f.V(1)->P());
        }

				if (!f.IsF(1)) {
				  if(nm == NMPerVert)	glNormal(f.V(1)->cN());
          if(nm == NMPerWedge)glNormal(f.WN(1));
				  if(cm == CMPerVert)	glColor(f.V(1)->C());
				  glVertex(f.V(1)->P());

				  if(nm == NMPerVert)	glNormal(f.V(2)->cN());
				  if(nm == NMPerWedge)glNormal(f.WN(2));
				  if(cm == CMPerVert)	glColor(f.V(2)->C());
				  glVertex(f.V(2)->P());
        }

				if (!f.IsF(2)) {
				  if(nm == NMPerVert)	glNormal(f.V(2)->cN());
          if(nm == NMPerWedge)glNormal(f.WN(2));
				  if(cm == CMPerVert)	glColor(f.V(2)->C());
				  glVertex(f.V(2)->P());

				  if(nm == NMPerVert)	glNormal(f.V(0)->cN());
				  if(nm == NMPerWedge)glNormal(f.WN(0));
				  if(cm == CMPerVert)	glColor(f.V(0)->C());
				  glVertex(f.V(0)->P());
        }

			}

			if(partial)
				++fp;
			else
				++fi;
		}

		glEnd();

	}
}

/// Basic Point drawing fucntion
// works also for mesh with deleted vertices
//由模型来获取模型中的点集然后遍历进行绘制所有的点
template<NormalMode nm, ColorMode cm>
void DrawPointsBase()
{
	typename MESH_TYPE::VertexIterator vi;
	glBegin(GL_POINTS);
	if(cm==CMPerMesh) glColor(m->C());

	for(vi=m->vert.begin();vi!=m->vert.end();++vi)if(!(*vi).IsD())
	{
			if(nm==NMPerVert) glNormal((*vi).cN());
			if(cm==CMPerVert) glColor((*vi).C());
			glVertex((*vi).P());
	}
	glEnd();
}

/// Utility function that computes in eyespace the current distance between the camera and the center of the bbox of the mesh
//?? what is the function ?
double CameraDistance(){
	Point3<typename MESH_TYPE::ScalarType> res;
	Matrix44<typename MESH_TYPE::ScalarType> mm;
	glGetv(GL_MODELVIEW_MATRIX,mm);
	Point3<typename MESH_TYPE::ScalarType>  c=m->bbox.Center();
	res=mm*c;
	return Norm(res);
}

template<NormalMode nm, ColorMode cm>
void DrawPoints()
{
	//点的参数设置
	glPointSize(GetHintParamf(HNPPointSize));

	if (glPointParameterfv) {
  	float camDist = CameraDistance();
	  float quadratic[] = { 0.0f, 0.0f, 1.0f/(camDist*camDist) , 0.0f };
	  glPointParameterfv( GL_POINT_DISTANCE_ATTENUATION, quadratic ); // GL_POINT_DISTANCE_ATTENUATION 一个带有三个浮点值的系数用来进行伸缩点的大小的计算.
	  glPointParameterf( GL_POINT_SIZE_MAX, 16.0f ); // glPointParameter(pname,value); 设置参数pname的值为value
	  glPointParameterf( GL_POINT_SIZE_MIN, 1.0f );
  }
	
	//当实际的点的数目不等于点集大小的时候。(也就是有deleted stuff)    ?? vn 和vert.size()区别在哪里
	//用vert点集来绘点
	if(m->vn!=(int)m->vert.size())
		{
			DrawPointsBase<nm,cm>();
			return;
		}

	// Perfect case, no deleted stuff,
	// draw the vertices using vertex arrays
	// 用实际的点的数组来绘点
	if (nm==NMPerVert)
		{
			glEnableClientState (GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT,sizeof(typename MESH_TYPE::VertexType),&(m->vert.begin()->N()[0]));
		}
	if (cm==CMPerVert)
		{
			glEnableClientState (GL_COLOR_ARRAY);
			glColorPointer(4,GL_UNSIGNED_BYTE,sizeof(typename MESH_TYPE::VertexType),&(m->vert.begin()->C()[0]));
		}

	glEnableClientState (GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,sizeof(typename MESH_TYPE::VertexType),&(m->vert.begin()->P()[0]));

	//glDrawElements(GL_POINTS ,m->vn,GL_UNSIGNED_INT, &(*indices.begin()) );
	glDrawArrays(GL_POINTS,0,m->vn);

	glDisableClientState (GL_VERTEX_ARRAY);
	if (nm==NMPerVert)  glDisableClientState (GL_NORMAL_ARRAY);
	if (cm==CMPerVert)  glDisableClientState (GL_COLOR_ARRAY);

	return;
}

//将背向观察面的线和点隐去，加快渲染速度 //隐去的动作在哪里体现?
void DrawHidden()
{
	//const float ZTWIST=HNParamf[HNPZTwist];
  glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT );
	
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0, 1);
	//glDepthRange(ZTWIST,1.0f);
	glDisable(GL_LIGHTING);
	glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
	DrawFill<NMNone,CMNone,TMNone>();	//作出三角平面构成的体
	glDisable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_LIGHTING);
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	//glDepthRange(0.0f,1.0f-ZTWIST);
	DrawWire<NMPerVert,CMNone>(); 
	glPopAttrib();
//	glDepthRange(0,1.0f);
}

template <NormalMode nm, ColorMode cm, TextureMode tm>
void DrawFlatWire() //将wireframe填充普通的texture。
{
	//const float ZTWIST=HNParamf[HNPZTwist];
	//glDepthRange(ZTWIST,1.0f);
  glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT );
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1.0, 1);
	DrawFill<nm,cm,tm>();
  glDisable(GL_POLYGON_OFFSET_FILL);
	//glDepthRange(0.0f,1.0f-ZTWIST);
  glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	//glColorMaterial(GL_FRONT,GL_DIFFUSE);
  glColor3f(.3f,.3f,.3f);
	DrawWire<nm,CMNone>();
	glPopAttrib();
	//glDepthRange(0,1.0f);
}

template <NormalMode nm, ColorMode cm>
void DrawRadar()
{
		const float ZTWIST=HNParamf[HNPZTwist];
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(0);
	glDepthRange(ZTWIST,1.0f);

	if (cm == CMNone)
		glColor4f(0.2f, 1.0f, 0.4f, 0.2f);
//	DrawFill<nm,cm,TMNone>();
	Draw<DMFlat,CMNone,TMNone>();

	glDepthMask(1);
	glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
//	DrawFill<nm,cm,TMNone>();
	Draw<DMFlat,CMNone,TMNone>();

	glDepthRange(0.0f,1.0f-ZTWIST);
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	glColor4f(0.1f, 1.0f, 0.2f, 0.6f);
	Draw<DMWire,CMNone,TMNone>();
	glDisable(GL_BLEND);
	glDepthRange(0,1.0f);

}



#ifdef GL_TEXTURE0_ARB
// Multitexturing nel caso voglia usare due texture unit.
void DrawTexture_NPV_TPW2()
{
	unsigned int texname=(*(m->face.begin())).WT(0).n(0);
	glBindTexture(GL_TEXTURE_2D,TMId[texname]);
	typename MESH_TYPE::FaceIterator fi;
	glBegin(GL_TRIANGLES);
	for(fi=m->face.begin();fi!=m->face.end();++fi)if(!(*fi).IsD()){
		  if(texname!=(*fi).WT(0).n(0))	{
				texname=(*fi).WT(0).n(0);
				glEnd();
				glBindTexture(GL_TEXTURE_2D,TMId[texname]);
				glBegin(GL_TRIANGLES);
			}
			glMultiTexCoordARB(GL_TEXTURE0_ARB, (*fi).WT(0).t(0));
			glMultiTexCoordARB(GL_TEXTURE1_ARB, (*fi).WT(0).t(0));
			glNormal((*fi).V(0)->N());
			glVertex((*fi).V(0)->P());

			glMultiTexCoordARB(GL_TEXTURE0_ARB, (*fi).WT(1).t(0));
			glMultiTexCoordARB(GL_TEXTURE1_ARB, (*fi).WT(1).t(0));
			glNormal((*fi).V(1)->N());
			glVertex((*fi).V(1)->P());

			glMultiTexCoordARB(GL_TEXTURE0_ARB, (*fi).WT(2).t(0));
			glMultiTexCoordARB(GL_TEXTURE1_ARB, (*fi).WT(2).t(0));
			glNormal((*fi).V(2)->N());
			glVertex((*fi).V(2)->P());
	}
	glEnd();
}

#endif


/*int MemUsed()
{
	int tot=sizeof(GlTrimesh);
	tot+=sizeof(mesh_type::edge_type)*edge.size();
	tot+=sizeof(MESH_TYPE::VertexType *) * EStrip.size();
	tot+=sizeof(MESH_TYPE::VertexType *) * TStrip.size();
	tot+=sizeof(MESH_TYPE::FaceType *)   * TStripF.size();
	return tot;
}*/

private:

template <NormalMode nm, ColorMode cm>
void DrawWire()
{
	//if(!(curr_hints & (HNUseEdgeStrip | HNUseLazyEdgeStrip) ) )
  if ( (curr_hints & HNIsPolygonal) ) 
	  {
      DrawWirePolygonal<nm,cm>();
    }
	else 
    {
			glPushAttrib(GL_POLYGON_BIT);
			glPolygonMode(GL_FRONT_AND_BACK ,GL_LINE);
			DrawFill<nm,cm,TMNone>(); //调用相应nm和cm的DrawFill
			glPopAttrib();
    }
	//	{
//			if(!HasEdges()) ComputeEdges();

			//if(cm==CMPerMesh)	glColor(m->C());
			//std::vector< MESH_TYPE::VertexType *>::iterator vi;
			//glBegin(GL_LINE_STRIP);
			//for(vi=EStrip.begin();vi!=EStrip.end(); ++vi){
			//	if((*vi)){
			//			glNormal((*vi)->N());
			//			glVertex((*vi)->P());
			//		}
			//	else
			//		{
			//			glEnd();
			//			glBegin(GL_LINE_STRIP);
			//		}
			//}
			//glEnd();
	//	}
}

//对应draw bouding box
void DrawBBox(ColorMode cm)
{
	if(cm==CMPerMesh) glColor(m->C());
	glBoxWire(m->bbox);		//bbox is the bounding box of the mesh
}


};// end class

/*
Crease Angle
Assume che:
la mesh abbia la topologia ff
la mesh non abbia complex (o se li aveva fossero stati detached)
Abbia le normali per faccia normalizzate!!


Prende una mesh e duplica tutti gli edge le cui normali nelle facce incidenti formano un angolo maggiore
di <angle> (espresso in rad).
foreach face
 foreach unvisited vert vi
   scan the star of triangles around vi duplicating vi each time we encounter a crease angle.

the new (and old) vertexes are put in a std::vector that is swapped with the original one at the end.
*/
// uncomment one of the following line to enable the Verbose Trace for Crease
#define VCTRACE (void)0
//#define VCTRACE TRACE

template<class MESH_TYPE>
void Crease(MESH_TYPE &m, typename MESH_TYPE::scalar_type angleRad)
{
	assert(m.HasFFTopology());
	typename MESH_TYPE::scalar_type cosangle=Cos(angleRad);

	std::vector<GLW::VertToSplit<MESH_TYPE> > SPL;
	std::vector<typename MESH_TYPE::VertexType> newvert;
	newvert.reserve(m.fn*3);
	// indica se un il vertice z della faccia e' stato processato
	enum {VISITED_0= MESH_TYPE::FaceType::USER0,
				VISITED_1= MESH_TYPE::FaceType::USER0<<1,
				VISITED_2= MESH_TYPE::FaceType::USER0<<2} ;
	int vis[3]={VISITED_0,VISITED_1,VISITED_2};

	int _t2=clock();
	typename MESH_TYPE::FaceIterator fi;
	for(fi=m.face.begin();fi!=m.face.end();++fi)
		if(!(*fi).IsD())	(*fi).Supervisor_Flags()&= (~(VISITED_0 | VISITED_1 | VISITED_2));

	for(fi=m.face.begin();fi!=m.face.end();++fi)
		if(!(*fi).IsD())
		 for(int j=0;j<3;++j)
			 if(!((*fi).Supervisor_Flags() & (vis[j])))
			 {
				 //VCTRACE("Face %i Spinning around vertex %i\n",fi-m.face.begin(), (*fi).V(j)-m.vert.begin());
				//(*fi).Supervisor_Flags() |= vis[j];
				typename MESH_TYPE::hedgepos_type he(&*fi,j,(*fi).V(j));
				typename MESH_TYPE::hedgepos_type she=he;
				typename MESH_TYPE::face_base_pointer nextf;
				GLW::VertToSplit<MESH_TYPE>  spl;
				spl.newp=false;
				spl.edge=-1;

				//Primo giro per trovare un bordo da cui partire
				do {
					he.FlipF();
					he.FlipE();
					if(he.IsBorder()) break;
				}	while(he!=she);
       if(he==she) // non c'e'bordi allora si cerca un crease
			 {
				 do {
						he.FlipF();
						he.FlipE();
						nextf=he.f->F(he.z);
						typename MESH_TYPE::scalar_type ps=nextf->N()*he.f->N();
						if(ps<cosangle)   break;
						int vz=0;
						if(he.v == he.f->V(he.z)) vz=he.z;
						if(he.v == he.f->V((he.z+1)%3)) vz=(he.z+1)%3;
						assert((he.f->Supervisor_Flags() & vis[vz] )==0);
					}	while(he!=she);
				}
				he.FlipE();

				she=he;
				newvert.push_back(*(*fi).V(j));
				typename MESH_TYPE::vertex_pointer curvert=&newvert.back();
//				VCTRACE("Starting from face %i edge %i vert %i \n",he.f-m.face.begin(), he.z, he.v-m.vert.begin());

				// Secondo giro in cui si riempie il vettore SPL con tutte le info per fare i nuovi vertici
				do{
					//TRACE("     -- spinning face %i edge %i vert %i\n",he.f-m.face.begin(), he.z, he.v-m.vert.begin());
					spl.v=curvert;
					spl.f=he.f;
					spl.z=-1;
					if(he.v == he.f->V(he.z)) spl.z=he.z;
					if(he.v == he.f->V((he.z+1)%3)) spl.z=(he.z+1)%3;
					assert(spl.z>=0);
					//VCTRACE("     -- spinning face vert %i Adding spl face %i vert %i\n",
					//	he.v-m.vert.begin(),	spl.f-m.face.begin(), spl.z );
					assert((spl.f->Supervisor_Flags() & vis[spl.z] )==0);
					spl.f->Supervisor_Flags() |= vis[spl.z];
					SPL.push_back(spl);
					spl.newp=false;
					spl.edge=-1;
					if(he.IsBorder()) break;
					nextf=he.f->F(he.z);
					if(nextf==she.f) break;
					typename MESH_TYPE::scalar_type ps=nextf->N()*he.f->N();
					if(ps<cosangle){
//									VCTRACE("splitting faces %i-%i edge %i vert %i\n",nextf-m.face.begin(),he.f-m.face.begin(), he.z, he.v-m.vert.begin());
									newvert.push_back(*(he.v));
									curvert=&newvert.back();
									spl.newp=true;
									//spl.edge=he.z;
					}
					he.FlipF();
					if(spl.newp) spl.edge=he.z;
					he.FlipE();

				}while(he!=she);
			 }
	assert(SPL.size()==m.fn*3);

	typename std::vector<GLW::VertToSplit<MESH_TYPE> >::iterator vsi;
	for(vsi=SPL.begin();vsi!=SPL.end();++vsi)
		{
			(*vsi).f->V((*vsi).z)=(*vsi).v;
			if((*vsi).newp){
				assert((*vsi).edge>=0 && (*vsi).edge<3);
					if(!(*vsi).f->IsBorder( (*vsi).edge) )
						(*vsi).f->Detach((*vsi).edge);

			}
		}

	m.vert.math::Swap(newvert);
	m.vn=m.vert.size();
}

/*
	Secondo tipo di crease angle. ha bisogno del per wedge normal
	e delle adiacence per vertice faccia gia fatte;
	Assume che le normali per faccia siano gia'state fatte (se ci sono)
 */

/*template<class MESH_TYPE>
void CreaseWN(MESH_TYPE &m, typename MESH_TYPE::scalar_type angle)
{
	if(!(MESH_TYPE::FaceType::OBJ_TYPE & MESH_TYPE::FaceType::OBJ_TYPE_WN) )
		{
			assert(0); // You needs a mesh with faces having per wedge normals
			return;
		}

	typename MESH_TYPE::scalar_type cosangle=Cos(angle);

	typename MESH_TYPE::FaceIterator fi;

	// Clear the per wedge normals
	for(fi=m.face.begin();fi!=m.face.end();++fi) if(!(*fi).IsD())
		{
			(*fi).WN(0)=MESH_TYPE::vectorial_type(0,0,0);
			(*fi).WN(1)=MESH_TYPE::vectorial_type(0,0,0);
			(*fi).WN(2)=MESH_TYPE::vectorial_type(0,0,0);
		}

	typename MESH_TYPE::FaceType::vectorial_type nn;

	for(fi=m.face.begin();fi!=m.face.end();++fi)		 if(!(*fi).IsD())
		{
			nn=(*fi).cN();
			for(int i=0;i<3;++i)
			 {
		 		VEdgePosB<MESH_TYPE::FaceType::face_base> x;
						for(x.f = (*fi).V(i)->Fp(), x.z = (*fi).V(i)->Zp(); x.f!=0; x.NextF() )	{
							assert(x.f->V(x.z)==(*fi).V(i));
							if(x.f->cN()*nn > cosangle)		x.f->WN(x.z)+=nn;
						}
				}
		}

}*/

} // end namespace

 #endif
