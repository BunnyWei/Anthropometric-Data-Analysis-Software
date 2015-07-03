#include <QtGui>
#include "controldock.h"

#include "Trace.h"
#include "mainwindow.h"

ControlDock::ControlDock(QWidget *parent, Qt::WFlags flags)
	: QDockWidget(parent, flags)
{
	//fullscreen=fs;
	createInterface();
	mainLayout->addWidget(stackedWidget);

	dockWidgetContents->setLayout(mainLayout);
	setWidget(dockWidgetContents);
	/*if(fullsceen)
		showFullScreen();*/
	//this -> setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint|Qt::FramelessWindowHint );
}

void ControlDock::createInterface()
{
	dockWidgetContents = new MyWidget;
	dockWidgetContents->setMaximumSize(1100, 900);
	mainLayout = new QVBoxLayout;
	stackedWidget = new QStackedWidget;
	stackedWidget->setMaximumSize(1100, 900);
   
	staDialog = new Statistic(this);//������ѯ0
    standardWidget = new StandardWidget(this); //��׼�˲�ѯ1

	statWidget = new StatWidget;//ͳ�Ʋ�ѯ2
	customParameter = new CustomParameter;//��Ӳ�ѯ3
	fitWidget = new FitWidget;//����Է���4
	relativeParameter = new RelativeParameter;//��ز�����ѯ5

	userManageDialog = new UserManage(this);//�û�����6
	basicManageDialog = new BasicManageDialog(this);//�������ݹ���7
	importWidget = new ImportWidget(this);//���ݵ���8
	deleteWidgt = new DeleteWidgt(this);//����ɾ��9
  //******************************************************
	//gLArea = new GLArea(this);
	//modifyPasswordDialog = new ModifyPassword(this);//�����޸�10

	stackedWidget->insertWidget(0, staDialog);
	stackedWidget->insertWidget(1, standardWidget);
	stackedWidget->insertWidget(2, statWidget);
	stackedWidget->insertWidget(3, customParameter);
	stackedWidget->insertWidget(4, fitWidget);
	stackedWidget->insertWidget(5, relativeParameter);
	stackedWidget->insertWidget(6, userManageDialog);
	stackedWidget->insertWidget(7, basicManageDialog);
	stackedWidget->insertWidget(8, importWidget);
	stackedWidget->insertWidget(9, deleteWidgt);
	//************************************************************************************
	//stackedWidget->insertWidget(10,gLArea);
	//stackedWidget->insertWidget(10, modifyPasswordDialog);

	//QScrollArea *dockWidgetContentsScroll = new QScrollArea;
	//dockWidgetContentsScroll->setWidget(dockWidgetContents);
	QScrollArea *staDialogScroll = new QScrollArea;
	staDialogScroll->setWidget(staDialog);
	QScrollArea *standardWidgetScroll = new QScrollArea;
	standardWidgetScroll->setWidget(standardWidget);
	QScrollArea *statWidgetScroll = new QScrollArea;
	statWidgetScroll->setWidget(statWidget);
	QScrollArea *customParameterScroll = new QScrollArea;
	customParameterScroll->setWidget(customParameter);
	QScrollArea *fitWidgetScroll = new QScrollArea;
	fitWidgetScroll->setWidget(fitWidget);

	QScrollArea *relativeParameterScroll = new QScrollArea;
	relativeParameterScroll->setWidget(relativeParameter);
	QScrollArea *userManageDialogScroll = new QScrollArea;
	userManageDialogScroll->setWidget(userManageDialog);
	QScrollArea *basicManageDialogScroll = new QScrollArea;
	basicManageDialogScroll->setWidget(basicManageDialog);
	QScrollArea *importWidgetScroll = new QScrollArea;
	importWidgetScroll->setWidget(importWidget);
	QScrollArea *deleteWidgtScroll = new QScrollArea;
	deleteWidgtScroll->setWidget(deleteWidgt);
//*****************************************************************
//QScrollArea *glareaWidgtScroll = new QScrollArea;
	//glareaWidgtScroll->setWidget(gLArea);
	//stackedWidget->addWidget(dockWidgetContentsScroll);
	stackedWidget->addWidget(staDialogScroll);
	stackedWidget->addWidget(standardWidgetScroll);
	stackedWidget->addWidget(statWidgetScroll);
	stackedWidget->addWidget(customParameterScroll);
	stackedWidget->addWidget(fitWidgetScroll);

	stackedWidget->addWidget(relativeParameterScroll);
	stackedWidget->addWidget(userManageDialogScroll);
	stackedWidget->addWidget(basicManageDialogScroll);
	stackedWidget->addWidget(importWidgetScroll);
	stackedWidget->addWidget(deleteWidgtScroll);
	stackedWidget->setCurrentIndex(0);
}
//void ControlDock::showFullScreen () 
//{
//}

ControlDock::~ControlDock()
{
}