/**************************************************************
** �ļ�����
** Copyright (c) 2009 ********* MultiPower
** ������:xiejian 
** �� ��: 2009-07-30

** �޸���: 
** �� ��: 
** �޸�������

** �� ��: ���������GL�Ĳ�����¼

** �汾��1.0
****************************************************************/

#ifndef GLLOGSTREAM_H
#define GLLOGSTREAM_H

#include <list>
#include <utility>
#include <QFont>

class QGLWidget;
class GLArea;

class GLLogStream 
{
public:
	enum Levels
	{
		SYSTEM = 0,
		WARNING = 1,
		FILTER = 2,
		DEBUG = 3
	};
	
	virtual ~GLLogStream () {}
  void print(QStringList &list);		// Fills a QStringList with the log entries 
  void glDraw(QGLWidget *qgl, int Level, int nlines,float vSpacing,QFont font);
  void Save(int Level, const char *filename);
  void Clear() {S.clear();}
	void Logf(int Level, const char * f, ... );
  void Log(int Level, const char * buf )
	{
		S.push_back(std::make_pair<int,QString>(Level,buf));
	}

//private:
  QList<std::pair<int,QString> > S;
};

#endif //GLLOGSTREAM_H
