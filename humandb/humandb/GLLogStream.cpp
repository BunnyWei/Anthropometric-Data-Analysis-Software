/**************************************************************
** 文件名：
** Copyright (c) 2009 ********* MultiPower
** 创建人:xiejian 
** 日 期: 2009-07-30

** 修改人: 
** 日 期: 
** 修改描述：

** 描 述: 定义一个记录、打印openGL区域绘制过程的一些信息.有系统信息，警告信息、过滤信息和调试信息.

** 版本：1.0
****************************************************************/

#include <QFont>
#include <QGLWidget>

#include <stdio.h>

#include "GLLogStream.h"

using namespace std;

void GLLogStream::print(QStringList &l)
{
/*	list<pair <int,string> > ::iterator li;
	
	foreach(li=S.begin();li!=S.end();++li)
		l << (*li).second.c_str();*/
}

//打印相应的信息
//??在哪里打印?程序中还是？
void GLLogStream::Logf(int Level, const char * f, ... )
{
	char buf[4096];
	va_list marker;
	va_start( marker, f );     

	vsprintf(buf,f,marker);
	va_end( marker );              
	Log(Level,buf);
}

void GLLogStream::Save(int /*Level*/, const char * filename )
{
	FILE *fp=fopen(filename,"wb");
	QList<pair <int,QString> > ::iterator li;
	for(li=S.begin();li!=S.end();++li)
		fprintf(fp,qPrintable((*li).second));
}


void  GLLogStream::glDraw(QGLWidget *qgl, int Level, int nlines,float vSpacing,QFont font)
{
	if( nlines > (int)S.size() ) nlines = S.size();
	QList<pair <int,QString> > ::iterator li;
	li=S.begin();

	advance(li,S.size()-nlines); 

	if(li==S.end())
		li=S.begin();

	int StartLine =  qgl->height() - (nlines * vSpacing+5);

	for(;li!=S.end();++li)
	{
		if(Level == -1 || (*li).first == Level)
			qgl->renderText(20,StartLine+=vSpacing,(*li).second,font);
	}
}
