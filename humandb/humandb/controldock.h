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
	    return QSize(parentWidget()->parentWidget()->width(), 900);		/* 设置control dock的初始大小 */
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

//定义显示窗口
	Statistic *staDialog;
	StandardWidget *standardWidget;//标准人查询
	LiteralFind *literalFindDialog;//文字查找
	GraphicFind *graphicFindDialog;//图形查找
	MyWidget *dockWidgetContents;
	QVBoxLayout *mainLayout;
	QStackedWidget *stackedWidget;
	BasicManageDialog *basicManageDialog;
	StatWidget *statWidget;//定义统计分析窗口
	FitWidget *fitWidget;//定义相关性分析窗口
	CustomParameter *customParameter;//添加自定义参数窗口
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
