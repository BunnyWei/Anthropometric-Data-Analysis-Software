#ifndef CONTROLDOCK_H
#define CONTROLDOCK_H

#include <QtGui>
#include <QtSql>
#include "Statistic.h"
#include "literalfind.h"
#include "graphicfind.h"
#include "qglobalvar.h"
#include "basicmanagedialog.h"
#include "stat_widget.h"
#include "fit_widget.h"
#include "customparameter.h"
#include "modifypassword.h"
#include "usermanage.h"
#include "import_widget.h"
#include "delete_widgt.h"
#include "relativeparameter.h"
#include "standardwidget.h"
#include "query.h"

class MyWidget : public QWidget
{
public:
	QSize sizeHint() const
	{
	    return QSize(parentWidget()->parentWidget()->width(), 900);		/* ����control dock�ĳ�ʼ��С */
	}
};

class ControlDock : public QDockWidget
{
	Q_OBJECT
public:
	ControlDock(QWidget *parent = 0, Qt::WFlags flags = 0);
	void createInterface(); 
	/*void showFullScreen () ;*/
	~ControlDock();

//������ʾ����
	Statistic *staDialog;
	StandardWidget *standardWidget;//��׼�˲�ѯ
	LiteralFind *literalFindDialog;//���ֲ���
	GraphicFind *graphicFindDialog;//ͼ�β���
	MyWidget *dockWidgetContents;
	QVBoxLayout *mainLayout;
	QStackedWidget *stackedWidget;
	BasicManageDialog *basicManageDialog;
	StatWidget *statWidget;//����ͳ�Ʒ�������
	FitWidget *fitWidget;//��������Է�������
	CustomParameter *customParameter;//����Զ����������
	ModifyPassword *modifyPasswordDialog;
	UserManage *userManageDialog;
	ImportWidget *importWidget;
	DeleteWidgt *deleteWidgt;
	//GLArea *gLArea;
	RelativeParameter *relativeParameter;
//protected:
//   bool fullscreen;
	
     
};

#endif // CONTROLDOCK_H
