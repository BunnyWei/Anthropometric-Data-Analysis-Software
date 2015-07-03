/**************************************************************
** �ļ�����
** Copyright (c) 2009 ********* MultiPower
** ������:xiejian 
** �� ��: 2009-07-30

** �޸���: 
** �� ��: 
** �޸�������

** �� ��: ����һ����¼����ӡopenGL������ƹ��̵�һЩ��Ϣ.��ϵͳ��Ϣ��������Ϣ��������Ϣ�͵�����Ϣ.

** �汾��1.0
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

//��ӡ��Ӧ����Ϣ
//??�������ӡ?�����л��ǣ�
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
