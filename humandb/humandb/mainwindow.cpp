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

QProgressBar *MainWindow::qb; //��̬���� ��Ϊ��ֻ��һ���ļ���˱�������
MainWindow *MainWindow::self = 0;
MainWindow::MainWindow() 
{
	self = this;
	mdiarea = new QMdiArea(this);
	setCentralWidget(mdiarea);
	windowMapper = new QSignalMapper(this);

	//����ÿ��subWindow��Ӧ��mapper���ź���ۺ�����ϵ������
	connect(windowMapper, SIGNAL(mapped(QWidget*)),this, SLOT(wrapSetActiveSubWindow(QWidget *))); 
	//�������ض�����ʱ�򣬸��¶�Ӧ�ĳ���״̬��
	connect(mdiarea, SIGNAL(subWindowActivated(QMdiSubWindow *)),this, SLOT(updateMenus()));

	createActions();
	createToolBars();
	
	loadPlugins(); //����IO���

	setStatusBar(new QStatusBar(this));
	globalStatusBar()=statusBar();
	qb=new QProgressBar(this);
	qb->setMaximum(100);
	statusBar()->addPermanentWidget(qb,0);

	setAcceptDrops(true); //֧���Ϸ�
	mdiarea->setAcceptDrops(true);
	setWindowTitle(appName());
	setWindowIcon(QIcon("Resources/�˳�.png"));
	//*****************************************************
	/*mdiarea->setBackground(Qt::NoBrush);
	QPixmap pixmap("hello.png");
    pixmap.scaled(mdiarea->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    mdiarea->setBackground(QBrush(pixmap));*/

	mdiarea->setBackground(Qt::NoBrush);
  // mdiArea->setStyleSheet(" background-image: url(e:/delete.png);"); //ƽ�� OK
    setStyleSheet("QMdiArea { border-image: url(welcome.png)}");  //��� OK
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

/* �򵥺�����
1) ��file�˵���������close�رղ�����
2) ��Render�����colorMode�Լ�Selected Face Renderingɾ�����ó����в�֧��.
*/
void MainWindow::createActions() 
{
	exitAction = new QAction(tr("&�˳�����"), this);
	exitAction->setIcon(QIcon("Resources/�˳�.png"));
    //exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("�˳�����"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exitWindow()));

	passwordAction = new QAction(tr("&�޸�����"), this);
	passwordAction->setIcon(QIcon("Resources/�����޸�.png"));
    //passwordAction->setShortcut(tr("Ctrl+Q"));
    passwordAction->setStatusTip(tr("�޸�����"));
    connect(passwordAction, SIGNAL(triggered()), this, SLOT(modifyPassword()));

	userAction = new QAction(tr("&�û�����"), this);
    userAction->setIcon(QIcon("Resources/�û�����.png"));
    //userAction->setShortcut(tr("Ctrl+U"));
    userAction->setStatusTip(tr("�û�����"));
    connect(userAction, SIGNAL(triggered()), this, SLOT(userManage()));

	basicAction = new QAction(tr("&�������ݹ���"), this);
    basicAction->setIcon(QIcon("Resources/�������ݹ���.png"));
    //basicAction->setShortcut(tr("Ctrl+U"));
    basicAction->setStatusTip(tr("�������ݹ���"));
    connect(basicAction, SIGNAL(triggered()), this, SLOT(basicManage()));

	originalAction = new QAction(tr("&���ݵ���"), this);
    originalAction->setIcon(QIcon("Resources/�������ݹ���.png"));
    //originalAction->setShortcut(tr("Ctrl+U"));
    originalAction->setStatusTip(tr("���ݵ���"));
    connect(originalAction, SIGNAL(triggered()), this, SLOT(originalManage()));

	deleteAction = new QAction(tr("&����ɾ��"), this);
    deleteAction->setIcon(QIcon("Resources/ɾ��.png"));
    //deleteAction->setShortcut(tr("Ctrl+U"));
    deleteAction->setStatusTip(tr("����ɾ��"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(delData()));

    

	literalSearchAction = new QAction(tr("&��������"), this);
    literalSearchAction->setIcon(QIcon("Resources/��������.png"));
    //literalSearchAction->setShortcut(tr("Ctrl+L"));
    literalSearchAction->setStatusTip(tr("��������"));
    connect(literalSearchAction, SIGNAL(triggered()), this, SLOT(literalSearch()));

	graphicSearchAction = new QAction(tr("&ͼ�����"), this);
    graphicSearchAction->setIcon(QIcon("Resources/ͼ�����.png"));
    //graphicSearchAction->setShortcut(tr("Ctrl+G"));
    graphicSearchAction->setStatusTip(tr("��ͼ���ϲ���"));
    connect(graphicSearchAction, SIGNAL(triggered()), this, SLOT(graphicSearch()));

	staticAction = new QAction(tr("&������ѯ"), this);
    staticAction->setIcon(QIcon("Resources/������ѯ.png"));
    //staticAction->setShortcut(tr("Ctrl+S"));
    staticAction->setStatusTip(tr("������ѯ"));
    connect(staticAction, SIGNAL(triggered()), this, SLOT(staticSize()));


	allAction = new QAction(tr("&ȫ������ѯ"), this);
    //allAction->setIcon(QIcon(":/images/new.png"));
    //allAction->setShortcut(tr("Ctrl+L"));
    allAction->setStatusTip(tr("ȫ������ѯ"));
    connect(allAction, SIGNAL(triggered()), this, SLOT(allParameter()));

	standardAction = new QAction(tr("&��׼�˲�ѯ"), this);
    standardAction->setIcon(QIcon("Resources/��׼�˲�ѯ.png"));
    //standardAction->setShortcut(tr("Ctrl+L"));
    standardAction->setStatusTip(tr("��׼�˲�ѯ"));
    connect(standardAction, SIGNAL(triggered()), this, SLOT(standardPerson()));

	indirectAction = new QAction(tr("&��ϲ���"), this);
    indirectAction->setIcon(QIcon("Resources/��ϲ���.png"));
    //indirectAction->setShortcut(tr("Ctrl+L"));
    indirectAction->setStatusTip(tr("��ϲ���"));
    connect(indirectAction, SIGNAL(triggered()), this, SLOT(indirectSearch()));

	relativeAction = new QAction(tr("&��ز�����ѯ"), this);
    relativeAction->setIcon(QIcon("Resources/��ز�����ѯ.png"));
    //relativeAction->setShortcut(tr("Ctrl+L"));
    relativeAction->setStatusTip(tr("��ز�����ѯ"));
    connect(relativeAction, SIGNAL(triggered()), this, SLOT(relativeSearch()));

	correlationAction = new QAction(tr("&����Է���"), this);
    correlationAction->setIcon(QIcon("Resources/����Է���.png"));
    //correlationAction->setShortcut(tr("Ctrl+L"));
    correlationAction->setStatusTip(tr("����Է���"));
    connect(correlationAction, SIGNAL(triggered()), this, SLOT(correlationAnalysis()));

	centileAction = new QAction(tr("&�߼���ѯ"), this);
    centileAction->setIcon(QIcon("Resources/�߼���ѯ.png"));
    //centileAction->setShortcut(tr("Ctrl+L"));
    centileAction->setStatusTip(tr("�߼���ѯ"));
    connect(centileAction, SIGNAL(triggered()), this, SLOT(centileSearch()));

	helpAction = new QAction(tr("&����"), this);
    helpAction->setIcon(QIcon("Resources/����.png"));
    //helpAction->setShortcut(tr("Ctrl+L"));
    helpAction->setStatusTip(tr("����"));
    connect(helpAction, SIGNAL(triggered()), this, SLOT(help()));

	glAction = new QAction(tr("&ģ����ʾ"), this);
    glAction->setIcon(QIcon("Resources/��ά��ʾ.png"));
    //helpAction->setShortcut(tr("Ctrl+L"));
    glAction->setStatusTip(tr("ģ����ʾ"));
    connect(glAction, SIGNAL(triggered()), this, SLOT(showGLA()));

	functionAction = new QAction(tr("&���ܳߴ�"), this);
    functionAction->setIcon(QIcon("Resources/���ܳߴ�.png"));
    functionAction->setStatusTip(tr("���ܳߴ�"));
    connect(functionAction, SIGNAL(triggered()), this, SLOT(functionSearch()));

	staticSizeAction = new QAction(tr("&�����ߴ�"), this);
    staticSizeAction->setIcon(QIcon("Resources/�����ߴ�.png"));
    staticSizeAction->setStatusTip(tr("�����ߴ�"));
    connect(staticSizeAction, SIGNAL(triggered()), this, SLOT(staticSizeSearch()));

	jointAction = new QAction(tr("&�ؽ�ת��"), this);
    jointAction->setIcon(QIcon("Resources/�ؽ�ת��.png"));
    jointAction->setStatusTip(tr("�ؽ�ת��"));
    connect(jointAction, SIGNAL(triggered()), this, SLOT(jointSearch()));

	operateAction = new QAction(tr("&������"), this);
    operateAction->setIcon(QIcon("Resources/������.png"));
    operateAction->setStatusTip(tr("������"));
    connect(operateAction, SIGNAL(triggered()), this, SLOT(operateSearch()));

	sportAction = new QAction(tr("&�˶�����"), this);
    sportAction->setIcon(QIcon("Resources/�˶�����.png"));
    sportAction->setStatusTip(tr("�˶�����"));
    connect(sportAction, SIGNAL(triggered()), this, SLOT(sportSearch()));

	mentalAction = new QAction(tr("&�������"), this);
    mentalAction->setIcon(QIcon("Resources/�������.png"));
    mentalAction->setStatusTip(tr("�������"));
    connect(mentalAction, SIGNAL(triggered()), this, SLOT(mentalSearch()));
}

void MainWindow::createMenus() 
{
    if (QGlobalVar::userType == 1)//�����û�
	{
		addFileMenu();//�ļ�
		addSearchMenu();//��������
		addDataManageMenu();//���ݹ���
		addBasicMenu();//������ѯ
		//addmultipleMenu();//�ۺϲ�ѯ
		addAdvancedMenu();//�߼���ѯ
		addHelpMenu();//����
	}
	else if (QGlobalVar::userType == 2)//�߼��û�
	{
		addFileMenu();
		addSearchMenu();
		addBasicMenu();
		//addmultipleMenu();
		addAdvancedMenu();
		addHelpMenu();
	}
	else//��ͨ�û�
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
	QSettings settings; //�������������Ļ���ô�ͱ���Ҫ����main�г�ʼ��OrganizationName��ApplicationName
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
** �������ܣ� ��Ŀ¼�д��ļ�
��ͨ��IO�ļ����ѡȡ��ȡ·��Ȼ����ļ�������IO���֧�ִ򿪲�����
*/
bool MainWindow::open(QString fileName,  GLArea *gla)
{
	// Opening files in a transparent form (IO plugins contribution is hidden to user)
	QStringList filters;

	// HashTable storing all supported formats togheter with
	// the (1-based) index  of first plugin which is able to open it
	QHash<QString, int> allKnownFormats;

	LoadKnownFilters(meshIOPlugins, filters, allKnownFormats,IMPORT); //filters--- ��ȡ�����в����֧�ֵ��ļ�������Ϣ��������Ϣ

	QStringList fileNameList;

	if (fileName.isEmpty()) 
	{
		//fileNameList = QFileDialog::getOpenFileNames(this,tr("Open File"), 
		//	lastUsedDirectory.path(), filters.join("\n")); //��ȡ��ǰ�û��ڴ��ļ�������ѡ�е�filename
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
			QString errorMsgFormat = "�޷��� file:\n\"%1\"\n\nError ��ϸ������Ϣ: �ļ� %1 ������";
			QMessageBox::critical(this, tr("��ά����ɨ��ϵͳ�ļ���ʧ��"), errorMsgFormat.arg(fileName));
			return false;
		}
		if(!fi.isReadable()) 	{
			QString errorMsgFormat = "�޷��� file:\n\"%1\"\n\nError ��ϸ������Ϣ: �ļ� %1 ���ɶ�";
			QMessageBox::critical(this, tr("��ά����ɨ��ϵͳ�ļ���ʧ��"), errorMsgFormat.arg(fileName));
			return false;
		}

		// this change of dir is needed for subsequent textures/materials loading
		QDir::setCurrent(fi.absoluteDir().absolutePath());

		QString extension = fi.suffix();

		// retrieving corresponding IO plugin
		//���ݺ�׺���ҵ���Ӧ��IO���
		int idx = allKnownFormats[extension.toLower()];
		if (idx == 0)
		{
			QString errorMsgFormat = "���ļ� file:\n\"%1\"\n\nError ���� ��ϸ������Ϣ:  \"%2\" �ļ���׺������ϵͳ֧�ֵ���ά��ʽ��.";
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
		//���õ�ǰIO����Ĵ򿪲���
		if (!pCurrentIOPlugin->open(extension, fileName, *mm ,mask,prePar,QCallBack,this /*gla*/))
		{
			QMessageBox::warning(this, tr("��ʧ��"), QString("����: '%1'\n\n").arg(fileName)+pCurrentIOPlugin->errorMsg()); // text
			delete mm;
		}
		else
		{
			// After opening the mesh lets ask to the io plugin if this format
			// requires some optional, or userdriven post-opening processing.
			// and in that case ask for the required parameters and then
			// ask to the plugin to perform that processing
			//���ļ��ɹ�֮������ж���Ĳ�����Ҫ���õĻ�����������Ӧ�Ĳ�����
			// ����mask����MeshModel����Ӧ����Ⱦ��ģʽ��
			// ��glarea������Ⱦ��
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
			//����gla�ж�Ӧ��meshmodel��Ӧ�ĸ��Ե�Id
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

			if( mask & vcg::tri::io::Mask::IOM_FACECOLOR)  //mask ��ӦmeshModel����Ӧ�ĵ�/���ģʽ
				gla->setColorMode(GLW::CMPerFace);
			if( mask & vcg::tri::io::Mask::IOM_VERTCOLOR)
			{
				gla->setColorMode(GLW::CMPerVert);
			}
			if(!GLA()->mm()->cm.textures.empty()) //����������Ϊ���ò���ʹ��
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
				QMessageBox::warning(this, "��ά����ɨ��ϵͳ ����", QString("�������������� %1 ����NAN ����ĵ� %2 �˻�����.\nCorrected.").arg(delVertNum).arg(delFaceNum) );
			GLA()->meshDoc.busy=false;
			if(newGla) GLA()->resetTrackBall();
		}
	}// end foreach file of the input list
	if(GLA()) GLA()->update();
	qb->reset();
	return true;
}

/* 
** �������ܣ��жϵ�ǰ�Ĵ����Ƿ���QMdi���Ӵ��ڣ�ͬʱ�ж��Ƿ�Ϊ�ա�
������������Ļ���ô�ͽ���ǰ�Ĵ�������ΪActive
** window ---- ��ǰ�Ĵ���
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
** ����֧�ֵĲ��
*/
void MainWindow::loadPlugins()
{
	// getPluginDirPath()����plugins�ľ���·��
	pluginsDir=QDir(getPluginDirPath());	
	// without adding the correct library path in the mac the loading of jpg (done via qt plugins) fails
	qApp->addLibraryPath(getPluginDirPath());
	qApp->addLibraryPath(getBaseDirPath());

	qDebug( "Current Plugins Dir: %s ",qPrintable(pluginsDir.absolutePath()));
	foreach (QString fileName, pluginsDir.entryList(QDir::Files)) 
	{		/* ����pluginsĿ¼��ÿ���ļ� */

		// ��ȡdll�ļ��ľ���·����ʹ��QPluginLoader���ز��
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
		qDebug( "Current DLL Dir: %s ",qPrintable(pluginsDir.absoluteFilePath(fileName)));
		// ʵ�������������Filters,Render�˵��µĲ�������ò����Ĺ��캯��������Edit�µĲ˵������ù����Ĺ��캯��
		QObject *plugin = loader.instance();  // ??�÷�����ʵ�ֻ��ơ�?
		
		qDebug("Error Message: %s",qPrintable(loader.errorString()));
		// ʵ�������������Filters,Render�˵��µĲ�������ò����Ĺ��캯��������Edit�µĲ˵������ù����Ĺ��캯��
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
** �ص�����---���н���������ʾ
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
//����Ϊ�ۺ���ʵ��
//================================================================================//
void MainWindow::exitWindow()
{//��ʵ�֣��˳�
	int ret = 0;
		this->setWindowIcon(QIcon("Resources/�˳�.png"));
	ret = QMessageBox::question(this, "�˳�", "��Ҫ�˳���", QMessageBox::Yes | QMessageBox::No);
   //  
	qDebug() << "ret:" << ret;
	if (65536 == ret)
		return;
	else
		exit(1);
}

void MainWindow::modifyPassword()
{//�޸�����
	/*modifyPasswordDialog = new ModifyPassword(this);
    setCentralWidget(modifyPasswordDialog);*/
	controlDock->stackedWidget->setCurrentIndex(10);
}

void MainWindow::userManage()
{//�û�����
	/*UserManageDialog = new UserManage(this);
    setCentralWidget(UserManageDialog);*/
	controlDock->stackedWidget->setCurrentIndex(6);
}

void MainWindow::basicManage()
{//�������ݹ���
	/*basicManageDialog = new BasicManageDialog(this);
    setCentralWidget(basicManageDialog);*/
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(7);
}
void MainWindow::originalManage()
{//ԭʼ���ݹ���
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
{//��ʵ�֣������ߴ��ѯ
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

void MainWindow::allParameter()//ȫ������ѯ
{}
void MainWindow::standardPerson()//��׼�˲�ѯ
{
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(1);
}
void MainWindow::indirectSearch()//��Ӳ�ѯ
{
	/*customParameter = new CustomParameter;
	setCentralWidget(customParameter);*/
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(3);
}
void MainWindow::relativeSearch()//��ز�����ѯRelativeParameter
{
	/*relativeParameter = new RelativeParameter;
	setCentralWidget(relativeParameter);*/
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(5);
}
void MainWindow::correlationAnalysis()//����Է���
{
    /*fitWidget = new FitWidget;
	setCentralWidget(fitWidget);*/
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(4);
}
void MainWindow::centileSearch()//ͳ�Ʒ���
{
	/*statWidget = new StatWidget;
	setCentralWidget(statWidget);*/
	getControlDock()->setVisible( true );
	controlDock->stackedWidget->setCurrentIndex(2);

}

void MainWindow::help()//����
{
	QProcess::execute("HelpSystem/HelpSystem.exe");
}

void MainWindow::showGLA()//��ʾ��ά����
{
	if (!GLA())
	{				
		QMessageBox msgBox;//setWindowTitle
		msgBox.setWindowTitle("��ά��ʾ");
		msgBox.setWindowIcon(QIcon("Resources/��ά��ʾ.png"));
		msgBox.setText("������άģ����Ҫ���1����ʱ��");
		msgBox.setInformativeText("��ȷ��Ҫ����ģ����?");
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
//����Ϊ��Ӳ˵�����ʵ��
//================================================================================//

void  MainWindow::addFileMenu()//����ļ��˵�
{
	fileMenu = menuBar()->addMenu(tr("&�� ��"));
	fileMenu->addAction(passwordAction);
    fileMenu->addAction(exitAction);
}
void  MainWindow::addDataManageMenu()//������ݹ���˵�
{
	dataMenu = menuBar()->addMenu(tr("&���ݹ���"));
    dataMenu->addAction(userAction);
    dataMenu->addAction(basicAction);
	dataMenu->addAction(originalAction);
	dataMenu->addAction(deleteAction);
}
void  MainWindow::addSearchMenu()//��Ӳ��Ҳ˵�
{
	searchMenu = menuBar()->addMenu(tr("&��������"));
    searchMenu->addAction(literalSearchAction);
   // searchMenu->addAction(graphicSearchAction);
}
void  MainWindow::addBasicMenu()//��ӻ�����ѯ�˵�
{
	basicMenu = menuBar()->addMenu(tr("&ͳ�Ʋ�ѯ"));
    basicMenu->addAction(staticAction);
	basicMenu->addAction(standardAction);
}
void  MainWindow::addmultipleMenu()//����ۺϲ�ѯ�˵�
{
	multipleMenu = menuBar()->addMenu(tr("&�ۺϲ�ѯ"));
    multipleMenu->addAction(allAction);
    multipleMenu->addAction(standardAction);
}
void  MainWindow::addAdvancedMenu()//��Ӹ߼���ѯ�˵�
{
	advancedMenu = menuBar()->addMenu(tr("&�߼���ѯ"));
	advancedMenu->addAction(centileAction);
    advancedMenu->addAction(indirectAction);
    advancedMenu->addAction(relativeAction);
	advancedMenu->addAction(correlationAction);
}
void  MainWindow::addHelpMenu()//��Ӱ���
{
	helpMenu = menuBar()->addMenu(tr("&��  ��"));
    helpMenu->addAction(helpAction);
}

void MainWindow::createToolBars()
{
	QDesktopWidget* desktopWidget = QApplication::desktop();
    //�õ��ͻ�������
    QRect clientRect = desktopWidget->availableGeometry();
    //�õ�Ӧ�ó������
    QRect applicationRect = desktopWidget->screenGeometry();

	int IconSize = applicationRect.height()/15;

	mainToolBar = addToolBar(tr("main"));
	mainToolBar->setIconSize(QSize(IconSize, IconSize));
	if (QGlobalVar::userType == 1)//�����û�
	{
		mainToolBar->addAction(literalSearchAction);//��������
		mainToolBar->addAction(staticAction);//������ѯ
		
		//mainToolBar->addAction(graphicSearchAction);
		mainToolBar->addAction(centileAction);//�߼���ѯ
		mainToolBar->addAction(relativeAction);//��ز�����ѯ
		mainToolBar->addAction(indirectAction);//��ϲ���
		
		mainToolBar->addAction(correlationAction);//����Է���
		mainToolBar->addAction(standardAction);//��׼�˲�ѯ

		//mainToolBar->addAction(userAction);
		//mainToolBar->addAction(basicAction);
		mainToolBar->addAction(originalAction);//�������ݹ���
		mainToolBar->addAction(deleteAction);//����ɾ��

		//mainToolBar->addAction(passwordAction);
		mainToolBar->addAction(glAction);//��ά��ʾ
		mainToolBar->addAction(helpAction);//����		
		mainToolBar->addAction(exitAction);//�˳�
	}
	else if (QGlobalVar::userType == 2)//�߼��û�
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
	else//��ͨ�û�
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
	query.exec("select itemname, itemnumber from item where category='�����ߴ�'");
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
	query.exec("select itemname, itemnumber from item where category='���ܳߴ�'");
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
	query.exec("select itemname, itemnumber from item where category='�ؽ�ת��'");
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
	query.exec("select itemname, itemnumber from item where category='������'");
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
	query.exec("select itemname, itemnumber from item where category='�˶�����'");
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
	query.exec("select itemname, itemnumber from item where category='�������'");
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