#include <QtGui>
#include <QToolBar>
#include <QProgressBar>
#include <QDesktopServices>
#include <QSettings>
#include <QProcess>

#include "mainwindow.h"
#include "meshmodel.h"
#include "interfaces.h"
#include "glarea.h"
#include "plugin_support.h"
#include   <tchar.h>

#include <wrap/io_trimesh/io_mask.h>
#include <vcg/complex/trimesh/update/normal.h>
#include <vcg/complex/trimesh/update/bounding.h>
#include <vcg/complex/trimesh/clean.h>

using namespace std;
using namespace vcg;

QProgressBar *MainWindow::qb; //静态变量 因为域只在一个文件因此必须声明
MainWindow *MainWindow::self = 0;
MainWindow::MainWindow() 
{
	self = this;
	mdiarea = new QMdiArea(this);
	setCentralWidget(mdiarea);
	windowMapper = new QSignalMapper(this);

	//将与每个subWindow对应的mapper的信号与槽函数联系起来。
	connect(windowMapper, SIGNAL(mapped(QWidget*)),this, SLOT(wrapSetActiveSubWindow(QWidget *))); 
	//当激活特定窗口时候，更新对应的程序状态。
	connect(mdiarea, SIGNAL(subWindowActivated(QMdiSubWindow *)),this, SLOT(updateMenus()));

	createActions();
	createToolBars();
	
	loadPlugins(); //加载IO插件

	setStatusBar(new QStatusBar(this));
	globalStatusBar()=statusBar();
	qb=new QProgressBar(this);
	qb->setMaximum(100);
	statusBar()->addPermanentWidget(qb,0);

	setAcceptDrops(true); //支持拖放
	mdiarea->setAcceptDrops(true);
	setWindowTitle(appName());
	setWindowIcon(QIcon("Resources/退出.png"));
	//*****************************************************
	/*mdiarea->setBackground(Qt::NoBrush);
	QPixmap pixmap("hello.png");
    pixmap.scaled(mdiarea->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    mdiarea->setBackground(QBrush(pixmap));*/

	mdiarea->setBackground(Qt::NoBrush);
  // mdiArea->setStyleSheet(" background-image: url(e:/delete.png);"); //平铺 OK
    setStyleSheet("QMdiArea { border-image: url(welcome.png)}");  //填充 OK
   createControlDock();
	//updateMenus();
}

MainWindow::~MainWindow()
{
	db.close();
}

void MainWindow::createControlDock()
{
	controlDock = new ControlDock(this);
	//controlDock->setVisible( true );
	controlDock->setVisible( false );
	controlDock->setAllowedAreas (Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	addDockWidget(Qt::LeftDockWidgetArea,controlDock);
}

/* 简单函数；
1) 在file菜单中增加了close关闭操作。
2) 将Render下面的colorMode以及Selected Face Rendering删掉。该程序中不支持.
*/
void MainWindow::createActions() 
{
	exitAction = new QAction(tr("&退出程序"), this);
	exitAction->setIcon(QIcon("Resources/退出.png"));
    //exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("退出程序"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exitWindow()));

	passwordAction = new QAction(tr("&修改密码"), this);
	passwordAction->setIcon(QIcon("Resources/密码修改.png"));
    //passwordAction->setShortcut(tr("Ctrl+Q"));
    passwordAction->setStatusTip(tr("修改密码"));
    connect(passwordAction, SIGNAL(triggered()), this, SLOT(modifyPassword()));

	userAction = new QAction(tr("&用户管理"), this);
    userAction->setIcon(QIcon("Resources/用户管理.png"));
    //userAction->setShortcut(tr("Ctrl+U"));
    userAction->setStatusTip(tr("用户管理"));
    connect(userAction, SIGNAL(triggered()), this, SLOT(userManage()));

	basicAction = new QAction(tr("&基本数据管理"), this);
    basicAction->setIcon(QIcon("Resources/基本数据管理.png"));
    //basicAction->setShortcut(tr("Ctrl+U"));
    basicAction->setStatusTip(tr("基本数据管理"));
    connect(basicAction, SIGNAL(triggered()), this, SLOT(basicManage()));

	originalAction = new QAction(tr("&数据导入"), this);
    originalAction->setIcon(QIcon("Resources/基本数据管理.png"));
    //originalAction->setShortcut(tr("Ctrl+U"));
    originalAction->setStatusTip(tr("数据导入"));
    connect(originalAction, SIGNAL(triggered()), this, SLOT(originalManage()));

	deleteAction = new QAction(tr("&数据删除"), this);
    deleteAction->setIcon(QIcon("Resources/删除.png"));
    //deleteAction->setShortcut(tr("Ctrl+U"));
    deleteAction->setStatusTip(tr("数据删除"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(delData()));

    

	literalSearchAction = new QAction(tr("&参数搜索"), this);
    literalSearchAction->setIcon(QIcon("Resources/参数搜索.png"));
    //literalSearchAction->setShortcut(tr("Ctrl+L"));
    literalSearchAction->setStatusTip(tr("参数搜索"));
    connect(literalSearchAction, SIGNAL(triggered()), this, SLOT(literalSearch()));

	graphicSearchAction = new QAction(tr("&图像查找"), this);
    graphicSearchAction->setIcon(QIcon("Resources/图像查找.png"));
    //graphicSearchAction->setShortcut(tr("Ctrl+G"));
    graphicSearchAction->setStatusTip(tr("在图像上查找"));
    connect(graphicSearchAction, SIGNAL(triggered()), this, SLOT(graphicSearch()));

	staticAction = new QAction(tr("&基本查询"), this);
    staticAction->setIcon(QIcon("Resources/基本查询.png"));
    //staticAction->setShortcut(tr("Ctrl+S"));
    staticAction->setStatusTip(tr("基本查询"));
    connect(staticAction, SIGNAL(triggered()), this, SLOT(staticSize()));


	allAction = new QAction(tr("&全参数查询"), this);
    //allAction->setIcon(QIcon(":/images/new.png"));
    //allAction->setShortcut(tr("Ctrl+L"));
    allAction->setStatusTip(tr("全参数查询"));
    connect(allAction, SIGNAL(triggered()), this, SLOT(allParameter()));

	standardAction = new QAction(tr("&标准人查询"), this);
    standardAction->setIcon(QIcon("Resources/标准人查询.png"));
    //standardAction->setShortcut(tr("Ctrl+L"));
    standardAction->setStatusTip(tr("标准人查询"));
    connect(standardAction, SIGNAL(triggered()), this, SLOT(standardPerson()));

	indirectAction = new QAction(tr("&组合参数"), this);
    indirectAction->setIcon(QIcon("Resources/组合参数.png"));
    //indirectAction->setShortcut(tr("Ctrl+L"));
    indirectAction->setStatusTip(tr("组合参数"));
    connect(indirectAction, SIGNAL(triggered()), this, SLOT(indirectSearch()));

	relativeAction = new QAction(tr("&相关参数查询"), this);
    relativeAction->setIcon(QIcon("Resources/相关参数查询.png"));
    //relativeAction->setShortcut(tr("Ctrl+L"));
    relativeAction->setStatusTip(tr("相关参数查询"));
    connect(relativeAction, SIGNAL(triggered()), this, SLOT(relativeSearch()));

	correlationAction = new QAction(tr("&相关性分析"), this);
    correlationAction->setIcon(QIcon("Resources/相关性分析.png"));
    //correlationAction->setShortcut(tr("Ctrl+L"));
    correlationAction->setStatusTip(tr("相关性分析"));
    connect(correlationAction, SIGNAL(triggered()), this, SLOT(correlationAnalysis()));

	centileAction = new QAction(tr("&高级查询"), this);
    centileAction->setIcon(QIcon("Resources/高级查询.png"));
    //centileAction->setShortcut(tr("Ctrl+L"));
    centileAction->setStatusTip(tr("高级查询"));
    connect(centileAction, SIGNAL(triggered()), this, SLOT(centileSearch()));

	helpAction = new QAction(tr("&帮助"), this);
    helpAction->setIcon(QIcon("Resources/帮助.png"));
    //helpAction->setShortcut(tr("Ctrl+L"));
    helpAction->setStatusTip(tr("帮助"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));

	glAction = new QAction(tr("&模型显示"), this);
    glAction->setIcon(QIcon("Resources/三维显示.png"));
    //helpAction->setShortcut(tr("Ctrl+L"));
    glAction->setStatusTip(tr("模型显示"));
    connect(glAction, SIGNAL(triggered()), this, SLOT(showGLA()));

	functionAction = new QAction(tr("&功能尺寸"), this);
    functionAction->setIcon(QIcon("Resources/功能尺寸.png"));
    functionAction->setStatusTip(tr("功能尺寸"));
    connect(functionAction, SIGNAL(triggered()), this, SLOT(functionSearch()));

	staticSizeAction = new QAction(tr("&基本尺寸"), this);
    staticSizeAction->setIcon(QIcon("Resources/基本尺寸.png"));
    staticSizeAction->setStatusTip(tr("基本尺寸"));
    connect(staticSizeAction, SIGNAL(triggered()), this, SLOT(staticSizeSearch()));

	jointAction = new QAction(tr("&关节转角"), this);
    jointAction->setIcon(QIcon("Resources/关节转角.png"));
    jointAction->setStatusTip(tr("关节转角"));
    connect(jointAction, SIGNAL(triggered()), this, SLOT(jointSearch()));

	operateAction = new QAction(tr("&操作力"), this);
    operateAction->setIcon(QIcon("Resources/操作力.png"));
    operateAction->setStatusTip(tr("操作力"));
    connect(operateAction, SIGNAL(triggered()), this, SLOT(operateSearch()));

	sportAction = new QAction(tr("&运动生理"), this);
    sportAction->setIcon(QIcon("Resources/运动生理.png"));
    sportAction->setStatusTip(tr("运动生理"));
    connect(sportAction, SIGNAL(triggered()), this, SLOT(sportSearch()));

	mentalAction = new QAction(tr("&心理参数"), this);
    mentalAction->setIcon(QIcon("Resources/心理参数.png"));
    mentalAction->setStatusTip(tr("心理参数"));
    connect(mentalAction, SIGNAL(triggered()), this, SLOT(mentalSearch()));
}

void MainWindow::createMenus() 
{
    if (QGlobalVar::userType == 1)//超级用户
	{
		addFileMenu();//文件
		addSearchMenu();//参数查找
		addDataManageMenu();//数据管理
		addBasicMenu();//基本查询
		//addmultipleMenu();//综合查询
		addAdvancedMenu();//高级查询
		addHelpMenu();//关于
	}
	else if (QGlobalVar::userType == 2)//高级用户
	{
		addFileMenu();
		addSearchMenu();
		addBasicMenu();
		//addmultipleMenu();
		addAdvancedMenu();
		addHelpMenu();
	}
	else//普通用户
	{
		addFileMenu();
		addSearchMenu();
		addBasicMenu();
		//addmultipleMenu();
		addHelpMenu();
	}
}

void MainWindow::createStatusBar() 
{
}

void MainWindow::setCurrentFile(const QString &fileName)
{
	QSettings settings; //如果是这样构造的话那么就必须要先在main中初始化OrganizationName和ApplicationName
	QStringList files = settings.value("recentFileList").toStringList();
	files.removeAll(fileName);
	files.prepend(fileName);
	while (files.size() > MAXRECENTFILES)
		files.removeLast();

	settings.setValue("recentFileList", files);

	foreach (QWidget *widget, QApplication::topLevelWidgets()) {
		MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
		//if (mainWin) mainWin->updateRecentFileActions();
	}

	settings.setValue("totalKV",          settings.value("totalKV",0).toInt()           + (GLA()->mm()->cm.vn)/1000);
	settings.setValue("loadedMeshCounter",settings.value("loadedMeshCounter",0).toInt() + 1);

	int loadedMeshCounter    = settings.value("loadedMeshCounter",20).toInt();
	int connectionInterval   = settings.value("connectionInterval",20).toInt();
	int lastComunicatedValue = settings.value("lastComunicatedValue",0).toInt();

	if(loadedMeshCounter-lastComunicatedValue>connectionInterval && !myLocalBuf.isOpen())
  {
#if not defined(__DISABLE_AUTO_STATS__)
		checkForUpdates(false);
#endif
		int congratsMeshCounter = settings.value("congratsMeshCounter",0).toInt();
		if(loadedMeshCounter > congratsMeshCounter + 100 )
			{
				QFile txtFile(":/images/100mesh.html");
				txtFile.open(QIODevice::ReadOnly | QIODevice::Text);
				QString tttt=txtFile.readAll();
				// This preference values store when you did the last request for a mail
				settings.setValue("congratsMeshCounter",loadedMeshCounter);

				//QDialog *congratsDialog = new QDialog();
				//Ui::CongratsDialog temp;
				//temp.setupUi(congratsDialog);

				//temp.buttonBox->addButton("Send Mail", QDialogButtonBox::AcceptRole);
				//temp.congratsTextEdit->setHtml(tttt);
				//congratsDialog->exec();
				//if(congratsDialog->result()==QDialog::Accepted)
				//	QDesktopServices::openUrl(QUrl("mailto:p.cignoni@isti.cnr.it?subject=[MeshLab] Reporting Info on MeshLab Usage"));
			}
	}
}

/* 
** 函数功能： 从目录中打开文件
先通过IO文件框的选取获取路径然后打开文件，加载IO插件支持打开操作。
*/
bool MainWindow::open(QString fileName,  GLArea *gla)
{
	// Opening files in a transparent form (IO plugins contribution is hidden to user)
	QStringList filters;

	// HashTable storing all supported formats togheter with
	// the (1-based) index  of first plugin which is able to open it
	QHash<QString, int> allKnownFormats;

	LoadKnownFilters(meshIOPlugins, filters, allKnownFormats,IMPORT); //filters--- 获取了所有插件所支持的文件描述信息和类型信息

	QStringList fileNameList;

	if (fileName.isEmpty()) 
	{
		//fileNameList = QFileDialog::getOpenFileNames(this,tr("Open File"), 
		//	lastUsedDirectory.path(), filters.join("\n")); //获取当前用户在打开文件窗口中选中的filename
	} 
	else 
	{
		fileNameList.push_back(fileName);
	}

	if (fileNameList.isEmpty())	{
		return false;
	} else {
		//save path away so we can use it again
		QString path = fileNameList.first();
		path.truncate(path.lastIndexOf("/"));
		lastUsedDirectory.setPath(path);
	}

	foreach(fileName,fileNameList)
	{
		QFileInfo fi(fileName);
		if(!fi.exists()) 	{
			QString errorMsgFormat = "无法打开 file:\n\"%1\"\n\nError 详细错误信息: 文件 %1 不存在";
			QMessageBox::critical(this, tr("三维人体扫描系统文件打开失败"), errorMsgFormat.arg(fileName));
			return false;
		}
		if(!fi.isReadable()) 	{
			QString errorMsgFormat = "无法打开 file:\n\"%1\"\n\nError 详细错误信息: 文件 %1 不可读";
			QMessageBox::critical(this, tr("三维人体扫描系统文件打开失败"), errorMsgFormat.arg(fileName));
			return false;
		}

		// this change of dir is needed for subsequent textures/materials loading
		QDir::setCurrent(fi.absoluteDir().absolutePath());

		QString extension = fi.suffix();

		// retrieving corresponding IO plugin
		//根据后缀名找到对应的IO插件
		int idx = allKnownFormats[extension.toLower()];
		if (idx == 0)
		{
			QString errorMsgFormat = "打开文件 file:\n\"%1\"\n\nError 错误 详细错误信息:  \"%2\" 文件后缀名不在系统支持的三维格式内.";
			QMessageBox::critical(this, tr("Opening Error"), errorMsgFormat.arg(fileName, extension));
			return false;
		}
		MeshIOInterface* pCurrentIOPlugin = meshIOPlugins[idx-1];
		pCurrentIOPlugin->setLog(&(GLA()->log));
		//qb->show();
		FilterParameterSet prePar;
		pCurrentIOPlugin->initPreOpenParameter(extension, fileName,prePar);
		/*if(!prePar.isEmpty())
		{
			GenericParamDialog preOpenDialog(this, &prePar, tr("Pre-Open Options"));
			preOpenDialog.exec();
		}*/

		int mask = 0;
		MeshModel *mm= new MeshModel();
		//调用当前IO插件的打开操作
		if (!pCurrentIOPlugin->open(extension, fileName, *mm ,mask,prePar,QCallBack,this /*gla*/))
		{
			QMessageBox::warning(this, tr("打开失败"), QString("当打开: '%1'\n\n").arg(fileName)+pCurrentIOPlugin->errorMsg()); // text
			delete mm;
		}
		else
		{
			// After opening the mesh lets ask to the io plugin if this format
			// requires some optional, or userdriven post-opening processing.
			// and in that case ask for the required parameters and then
			// ask to the plugin to perform that processing
			//打开文件成功之后，如果有额外的参数需要设置的话，就设置相应的参数。
			// 根据mask设置MeshModel的相应的渲染等模式。
			// 在glarea里面渲染。
			FilterParameterSet par;
			pCurrentIOPlugin->initOpenParameter(extension, *mm, par);
			/*if(!par.isEmpty())
			{
				GenericParamDialog postOpenDialog(this, &par, tr("Post-Open Processing"));
				postOpenDialog.exec();
				pCurrentIOPlugin->applyOpenParameter(extension, *mm, par);
			}*/
			bool newGla = false;
			if(gla==0)
			{
				gla=new GLArea(mdiarea);
				/*addDockWidget(Qt::RightDockWidgetArea,gla->layerDialog);*/
				newGla =true;
			}
			gla->meshDoc.busy=true;
			gla->meshDoc.addNewMesh(qPrintable(fileName),mm);
			//设置gla中对应的meshmodel对应的各自的Id
			int size = gla->meshDoc.meshList.size();
			qDebug() << "mesh size:" << size;
			if (size > 1)
			for (int i = 0; i < size; i++)
			{
				qDebug() << "meshList.at(i)->visible" << gla->meshDoc.meshList.at(i)->visible;
				qDebug() << QString("meshList.at(i)->fileName:%1").arg(gla->meshDoc.meshList.at(i)->fileName.c_str());
				//<< gla->meshDoc.meshList.at(i)->fileName;
				qDebug() << "meshList.at(i)->modelId" << gla->meshDoc.meshList.at(i)->modelId;
			}
			
			//gla->mm()->ioMask |= mask;				// store mask into model structure
			gla->setFileName(mm->fileName.c_str());

			if(newGla){
				mdiarea->addSubWindow(gla);
			}
			if(mdiarea->isVisible()) gla->showMaximized();
			setCurrentFile(fileName);

			if( mask & vcg::tri::io::Mask::IOM_FACECOLOR)  //mask 对应meshModel的相应的点/面等模式
				gla->setColorMode(GLW::CMPerFace);
			if( mask & vcg::tri::io::Mask::IOM_VERTCOLOR)
			{
				gla->setColorMode(GLW::CMPerVert);
			}
			if(!GLA()->mm()->cm.textures.empty()) //否则则设置为可用并且使用
			{
				GLA()->setTextureMode(GLW::TMPerWedgeMulti);
			}

			if( mask & vcg::tri::io::Mask::IOM_VERTNORMAL)
				vcg::tri::UpdateNormals<CMeshO>::PerFace(mm->cm);
			else
				vcg::tri::UpdateNormals<CMeshO>::PerVertexNormalizedPerFaceNormalized(mm->cm);

			vcg::tri::UpdateBounding<CMeshO>::Box(mm->cm);					// updates bounding box

			if(gla->mm()->cm.fn==0){
				gla->setDrawMode(vcg::GLW::DMPoints);
				if(!(mask & vcg::tri::io::Mask::IOM_VERTNORMAL)) gla->setLight(false);
				else mm->updateDataMask(MeshModel::MM_VERTNORMAL);
			}
			else mm->updateDataMask(MeshModel::MM_VERTNORMAL);

			//updateMenus();
			int delVertNum = vcg::tri::Clean<CMeshO>::RemoveDegenerateVertex(mm->cm);
			int delFaceNum = vcg::tri::Clean<CMeshO>::RemoveDegenerateFace(mm->cm);

			if(delVertNum>0 || delFaceNum>0 )
				QMessageBox::warning(this, "三维人体扫描系统 警告", QString("警告三角网格含有 %1 带有NAN 坐标的点 %2 退化的面.\nCorrected.").arg(delVertNum).arg(delFaceNum) );
			GLA()->meshDoc.busy=false;
			if(newGla) GLA()->resetTrackBall();
		}
	}// end foreach file of the input list
	if(GLA()) GLA()->update();
	qb->reset();
	return true;
}

/* 
** 函数功能：判断当前的窗口是否是QMdi的子窗口，同时判断是否为空。
如果满足条件的话那么就将当前的窗口设置为Active
** window ---- 当前的窗口
*/
void MainWindow::wrapSetActiveSubWindow(QWidget* window){
	QMdiSubWindow* subwindow;
	subwindow = dynamic_cast<QMdiSubWindow*>(window);
	if(subwindow!= NULL){
		mdiarea->setActiveSubWindow(subwindow);
	}else{
		qDebug("Type of window is not a QMdiSubWindow*");
	}
}

/*
** 加载支持的插件
*/
void MainWindow::loadPlugins()
{
	// getPluginDirPath()返回plugins的绝对路径
	pluginsDir=QDir(getPluginDirPath());	
	// without adding the correct library path in the mac the loading of jpg (done via qt plugins) fails
	qApp->addLibraryPath(getPluginDirPath());
	qApp->addLibraryPath(getBaseDirPath());

	qDebug( "Current Plugins Dir: %s ",qPrintable(pluginsDir.absolutePath()));
	foreach (QString fileName, pluginsDir.entryList(QDir::Files)) 
	{		/* 遍历plugins目录下每个文件 */

		// 获取dll文件的绝对路径，使用QPluginLoader加载插件
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
		qDebug( "Current DLL Dir: %s ",qPrintable(pluginsDir.absoluteFilePath(fileName)));
		// 实例化插件，对于Filters,Render菜单下的插件，调用插件类的构造函数，对于Edit下的菜单，调用工厂的构造函数
		QObject *plugin = loader.instance();  // ??该方法的实现机制。?
		
		qDebug("Error Message: %s",qPrintable(loader.errorString()));
		// 实例化插件，对于Filters,Render菜单下的插件，调用插件类的构造函数，对于Edit下的菜单，调用工厂的构造函数
		if (plugin) {
			MeshIOInterface *iIO = qobject_cast<MeshIOInterface *>(plugin);
			if (iIO) {
				meshIOPlugins.push_back(iIO);
			}
			MeshEditInterfaceFactory *iEditFactory = qobject_cast<MeshEditInterfaceFactory *>(plugin);
			QAction *editAction = 0;
			if(iEditFactory) {
				//qDebug() << "Here with filename:" << fileName;
				foreach(editAction, iEditFactory->actions()) {
					if(!editAction->icon().isNull()) {
						//mainToolBar->addAction(editAction);
					} else {
						qDebug() << "action was null";
					}
					connect(editAction, SIGNAL(triggered()), this, SLOT(applyEditMode()));
				}
			}
		}
	}
}

void MainWindow::applyEditMode()
{
	if(!GLA()) { //prevents crash without mesh
		QAction *action = qobject_cast<QAction *>(sender());
		action->setChecked(false);
		return;
	}

	QAction *action = qobject_cast<QAction *>(sender());

	if(GLA()->getCurrentEditAction()) //prevents multiple buttons pushed
		{
		  if(action==GLA()->getCurrentEditAction()) // We have double pressed the same action and that means disable that actioon
			{
				if(GLA()->suspendedEditor)
				{
					//suspendEditMode();
					return;
				}
				GLA()->endEdit();
				//updateMenus();
				return;
			}
			assert(0); // it should be impossible to start an action without having ended the previous one.
			return;
		}

	//if this GLArea does not have an instance of this action's MeshEdit tool then give it one
	if(!GLA()->editorExistsForAction(action))
	{
		MeshEditInterfaceFactory *iEditFactory = qobject_cast<MeshEditInterfaceFactory *>(action->parent());
		MeshEditInterface *iEdit = iEditFactory->getMeshEditInterface(action);
		GLA()->addMeshEditor(action, iEdit);
	}
	GLA()->setCurrentEditAction(action);

	//setSelectionRendering(true);

	//updateMenus();
}

/*
** 回调函数---进行进程条的显示
*/
bool MainWindow::QCallBack(const int pos, const char * str)
{
	static int lastPos=-1;
	if(pos==lastPos) return true;
	lastPos=pos;

	static QTime currTime;
	if(currTime.elapsed()< 100) return true;
	currTime.start();
	MainWindow::globalStatusBar()->showMessage(str,5000);
	MainWindow::qb->show();
	MainWindow::qb->setEnabled(true);
	MainWindow::qb->setValue(pos);
	MainWindow::globalStatusBar()->update();
	qApp->processEvents();
	return true;
}

//=================================================================================//
//以下为槽函数实现
//================================================================================//
void MainWindow::exitWindow()
{//槽实现：退出
	int ret = 0;
		this->setWindowIcon(QIcon("Resources/退出.png"));
	ret = QMessageBox::question(this, "退出", "您要退出吗？", QMessageBox::Yes | QMessageBox::No);
   //  
	qDebug() << "ret:" << ret;
	if (65536 == ret)
		return;
	else
		exit(1);
}

void MainWindow::modifyPassword()
{//修改密码
	/*modifyPasswordDialog = new ModifyPassword(this);
    setCentralWidget(modifyPasswordDialog);*/
	controlDock->stackedWidget->setCurrentIndex(10);
}

void MainWindow::userManage()
{//用户管理
	/*UserManageDialog = new UserManage(this);
    setCentralWidget(UserManageDialog);*/
	controlDock->stackedWidget->setCurrentIndex(6);
}

void MainWindow::basicManage()
{//基本数据管理
	/*basicManageDialog = new BasicManageDialog(this);
    setCentralWidget(basicManageDialog);*/
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(7);
}
void MainWindow::originalManage()
{//原始数据管理
	/*importWidget = new ImportWidget(this);
    setCentralWidget(importWidget);*/
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(8);
}

void MainWindow::delData()
{
	/*deleteWidgt = new DeleteWidgt(this);
    setCentralWidget(deleteWidgt);*/
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(9);
}

void MainWindow::literalSearch()
{
	//getControlDock()->setVisible( true );
	literalFindDialog = new LiteralFind(this);
	literalFindDialog->show();
}

void MainWindow::graphicSearch()
{
	graphicFindDialog = new GraphicFind(this);
    graphicFindDialog->show();
}


void MainWindow::staticSize()
{//槽实现：基本尺寸查询
	/*staDialog = new Statistic(this);
    setCentralWidget(staDialog);*/
	//if (!getControlDock()->isWindow())
	//createControlDock();
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(0);
	controlDock->staDialog->ui.listWidget->clear();
	QSqlQuery query;
	query.exec("select itemname, itemnumber from item");
	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem(itemname);
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		controlDock->staDialog->ui.listWidget->addItem(item);
	}
}

void MainWindow::allParameter()//全参数查询
{}
void MainWindow::standardPerson()//标准人查询
{
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(1);
}
void MainWindow::indirectSearch()//间接查询
{
	/*customParameter = new CustomParameter;
	setCentralWidget(customParameter);*/
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(3);
}
void MainWindow::relativeSearch()//相关参数查询RelativeParameter
{
	/*relativeParameter = new RelativeParameter;
	setCentralWidget(relativeParameter);*/
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(5);
}
void MainWindow::correlationAnalysis()//相关性分析
{
    /*fitWidget = new FitWidget;
	setCentralWidget(fitWidget);*/
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(4);
}
void MainWindow::centileSearch()//统计分析
{
	/*statWidget = new StatWidget;
	setCentralWidget(statWidget);*/
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(2);

}

void MainWindow::help()//帮助
{
	QProcess::execute("HelpSystem/HelpSystem.exe");
}

void MainWindow::showGLA()//显示三维区域
{
	if (!GLA())
	{				
		QMessageBox msgBox;//setWindowTitle
		msgBox.setWindowTitle("三维显示");
		msgBox.setWindowIcon(QIcon("Resources/三维显示.png"));
		msgBox.setText("载入三维模型需要大概1分钟时间");
		msgBox.setInformativeText("您确定要载入模型吗?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		//msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		qDebug() << "ret:" << ret;
		if (65536 == ret)
			return;
		else
		{
			open(QApplication::applicationDirPath() + "/model/standard.ply", GLA());
			open(QApplication::applicationDirPath() + "/model/standing.ply", GLA());
			open(QApplication::applicationDirPath() + "/model/sitting.ply", GLA());
			open(QApplication::applicationDirPath() + "/model/head.ply", GLA());
			open(QApplication::applicationDirPath() + "/model/hand.ply", GLA());
			open(QApplication::applicationDirPath() + "/model/LF.ply", GLA());
		}
	}
}

//=================================================================================//
//以下为添加菜单函数实现
//================================================================================//

void  MainWindow::addFileMenu()//添加文件菜单
{
	fileMenu = menuBar()->addMenu(tr("&文 件"));
	fileMenu->addAction(passwordAction);
    fileMenu->addAction(exitAction);
}
void  MainWindow::addDataManageMenu()//添加数据管理菜单
{
	dataMenu = menuBar()->addMenu(tr("&数据管理"));
    dataMenu->addAction(userAction);
    dataMenu->addAction(basicAction);
	dataMenu->addAction(originalAction);
	dataMenu->addAction(deleteAction);
}
void  MainWindow::addSearchMenu()//添加查找菜单
{
	searchMenu = menuBar()->addMenu(tr("&参数查找"));
    searchMenu->addAction(literalSearchAction);
   // searchMenu->addAction(graphicSearchAction);
}
void  MainWindow::addBasicMenu()//添加基本查询菜单
{
	basicMenu = menuBar()->addMenu(tr("&统计查询"));
    basicMenu->addAction(staticAction);
	basicMenu->addAction(standardAction);
}
void  MainWindow::addmultipleMenu()//添加综合查询菜单
{
	multipleMenu = menuBar()->addMenu(tr("&综合查询"));
    multipleMenu->addAction(allAction);
    multipleMenu->addAction(standardAction);
}
void  MainWindow::addAdvancedMenu()//添加高级查询菜单
{
	advancedMenu = menuBar()->addMenu(tr("&高级查询"));
	advancedMenu->addAction(centileAction);
    advancedMenu->addAction(indirectAction);
    advancedMenu->addAction(relativeAction);
	advancedMenu->addAction(correlationAction);
}
void  MainWindow::addHelpMenu()//添加帮助
{
	helpMenu = menuBar()->addMenu(tr("&帮  助"));
    helpMenu->addAction(helpAction);
}

void MainWindow::createToolBars()
{
	QDesktopWidget* desktopWidget = QApplication::desktop();
    //得到客户区矩形
    QRect clientRect = desktopWidget->availableGeometry();
    //得到应用程序矩形
    QRect applicationRect = desktopWidget->screenGeometry();

	int IconSize = applicationRect.height()/15;

	mainToolBar = addToolBar(tr("main"));
	mainToolBar->setIconSize(QSize(IconSize, IconSize));
	if (QGlobalVar::userType == 1)//超级用户
	{
		mainToolBar->addAction(literalSearchAction);//参数搜索
		mainToolBar->addAction(staticAction);//基本查询
		
		//mainToolBar->addAction(graphicSearchAction);
		mainToolBar->addAction(centileAction);//高级查询
		mainToolBar->addAction(relativeAction);//相关参数查询
		mainToolBar->addAction(indirectAction);//组合参数
		
		mainToolBar->addAction(correlationAction);//相关性分析
		mainToolBar->addAction(standardAction);//标准人查询

		//mainToolBar->addAction(userAction);
		//mainToolBar->addAction(basicAction);
		mainToolBar->addAction(originalAction);//基本数据管理
		mainToolBar->addAction(deleteAction);//数据删除

		//mainToolBar->addAction(passwordAction);
		mainToolBar->addAction(glAction);//三维显示
		mainToolBar->addAction(helpAction);//帮助		
		mainToolBar->addAction(exitAction);//退出
	}
	else if (QGlobalVar::userType == 2)//高级用户
	{
		mainToolBar->addAction(staticAction);
		mainToolBar->addAction(standardAction);
		mainToolBar->addAction(literalSearchAction);
		//mainToolBar->addAction(graphicSearchAction);
		mainToolBar->addAction(centileAction);
		mainToolBar->addAction(indirectAction);
		mainToolBar->addAction(relativeAction);
		mainToolBar->addAction(correlationAction);

		mainToolBar->addAction(passwordAction);
		mainToolBar->addAction(exitAction);
		mainToolBar->addAction(helpAction);
	}
	else//普通用户
	{
		mainToolBar->addAction(staticAction);
		mainToolBar->addAction(staticSizeAction);
		mainToolBar->addAction(functionAction);
		mainToolBar->addAction(jointAction);
		mainToolBar->addAction(operateAction);
		mainToolBar->addAction(sportAction);
		mainToolBar->addAction(mentalAction);

		mainToolBar->addAction(literalSearchAction);
		mainToolBar->addAction(standardAction);
	
		//mainToolBar->addAction(passwordAction);		
		mainToolBar->addAction(helpAction);
		mainToolBar->addAction(glAction);
		mainToolBar->addAction(exitAction);
	}
}

void MainWindow::staticSizeSearch()
{
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(0);
	controlDock->staDialog->ui.listWidget->clear();
	QSqlQuery query;
	query.exec("select itemname, itemnumber from item where category='基本尺寸'");
	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem(itemname);
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		controlDock->staDialog->ui.listWidget->addItem(item);
	}
}
void MainWindow::functionSearch()
{
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(0);
	controlDock->staDialog->ui.listWidget->clear();
	QSqlQuery query;
	query.exec("select itemname, itemnumber from item where category='功能尺寸'");
	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem(itemname);
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		controlDock->staDialog->ui.listWidget->addItem(item);
	}
}
void MainWindow::jointSearch()
{
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(0);
	controlDock->staDialog->ui.listWidget->clear();
	QSqlQuery query;
	query.exec("select itemname, itemnumber from item where category='关节转角'");
	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem(itemname);
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		controlDock->staDialog->ui.listWidget->addItem(item);
	}
}
void MainWindow::operateSearch()
{
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(0);
	controlDock->staDialog->ui.listWidget->clear();
	QSqlQuery query;
	query.exec("select itemname, itemnumber from item where category='操作力'");
	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem(itemname);
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		controlDock->staDialog->ui.listWidget->addItem(item);
	}
}
void MainWindow::sportSearch()
{
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(0);
	controlDock->staDialog->ui.listWidget->clear();
	QSqlQuery query;
	query.exec("select itemname, itemnumber from item where category='运动生理'");
	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem(itemname);
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		controlDock->staDialog->ui.listWidget->addItem(item);
	}
}
void MainWindow::mentalSearch()
{
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(0);
	controlDock->staDialog->ui.listWidget->clear();
	QSqlQuery query;
	query.exec("select itemname, itemnumber from item where category='心理参数'");
	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem(itemname);
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		controlDock->staDialog->ui.listWidget->addItem(item);
	}
}