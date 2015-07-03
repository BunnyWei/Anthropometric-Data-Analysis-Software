#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
#include "query.h"
#include "glarea.h"
#include "controldock.h"
#include "interfaces.h"

#define MAXRECENTFILES 4 //定义最近打开文件中显示的最多的文件数

class QAction;
class QLabel;
class QMdiArea;
class QProgressBar;

class MainWindow : public QMainWindow, MainWindowInterface // 增加了继承MainWindowInterface来实现插件的接入。
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();
	static MainWindow *self;

	static MainWindow *instance()
	{
		return self;
	}

	static bool QCallBack(const int pos, const char *str);
	const QString appName() const {return tr("陆军人体参数数据库v")+appVer(); }
	const QString appVer() const {return tr("1.0"); }

	//返回当前激活的GLArea
	GLArea *GLA() const 
	{
		if(mdiarea->currentSubWindow()==0) return 0;
		GLArea *glw = qobject_cast<GLArea *>(mdiarea->currentSubWindow());
		if(glw) return glw;
		glw = qobject_cast<GLArea *>(mdiarea->currentSubWindow()->widget());
		assert(glw);
		return glw;
	}
	static QStatusBar *&globalStatusBar()
	{
		static QStatusBar *_qsb=0;
		return _qsb;
	}

	ControlDock *getControlDock()
	{
		return this->controlDock;
	}

	public slots:
		bool open(QString fileName=QString(),  GLArea *gla=0); // GLArea QT中支持openGL的区域
		/////////////Slot Update Menu/////////////////////////
		//void updateMenus();  //针对MDI多文档界面中，当一个窗口被激活的时候,激活他对应的程序状态。

		void wrapSetActiveSubWindow(QWidget* window);
		void createControlDock();
		void exitWindow();//退出
		void modifyPassword();//修改密码

		void userManage();//用户管理
		void basicManage();//基本数据管理
		void originalManage();//原始数据管理
		void delData();//数据删除

		void literalSearch();//文字查找
		void graphicSearch();//图形查找

		void staticSize();//基本尺寸查询

		void allParameter();//全参数查询
		void standardPerson();//标准人查询

		void indirectSearch();//间接查询
		void relativeSearch();//相关参数查询
		void correlationAnalysis();//相关性分析
		void centileSearch();//百分位查询
		void applyEditMode();

		void help();//关于
		void showGLA();//显示三维区域

		void staticSizeSearch();
		void functionSearch();
		void jointSearch();
		void operateSearch();
		void sportSearch();
		void mentalSearch();

private:
	void addFileMenu();//添加文件菜单
	void addDataManageMenu();//添加数据管理菜单
	void addSearchMenu();//添加查找菜单
	void addBasicMenu();//添加基本查询菜单
	void addmultipleMenu();//添加综合查询菜单
	void addAdvancedMenu();//添加高级查询菜单
	void addHelpMenu();//添加关于

	void createActions();
	void createMenus();
	void createContextMenu();
	void createToolBars();
	void createStatusBar();
	/*bool createConnection();*/
public:
	void loadPlugins(); //插件加载，在该项目中用来支持打开不同的三维格式的文件
	void setCurrentFile(const QString &fileName); //设置打开file后app的相关的current file的设置
	//void updateRecentFileActions(); //更新最近的File Actions
private:
	//定义动作

	QAction *exitAction;//退出
	QAction *passwordAction;//修改密码

	QAction *userAction;//用户管理
	QAction *basicAction;//基本数据管理
	QAction *originalAction;//原始数据管理
	QAction *deleteAction;//数据删除

	QAction *literalSearchAction;//文字查找
	QAction *graphicSearchAction;//图形查找

	QAction *staticAction;//基本尺寸查询

	QAction *allAction;//全参数查询
	QAction *standardAction;//标准人查询

	QAction *indirectAction;//间接查询
	QAction *relativeAction;//相关参数查询
	QAction *correlationAction;//相关性分析
	QAction *centileAction;//百分位查询

	QAction *helpAction;//关于
	QAction *glAction;//三维显示

	//一下定义每个特征部位对应的ACTION
	QAction *staticSizeAction;
	QAction *functionAction;
	QAction *jointAction;
	QAction *operateAction;
	QAction *sportAction;
	QAction *mentalAction;

	//定义菜单
	QMenu *fileMenu;//文件菜单
	QMenu *dataMenu;//数据管理菜单
	QMenu *searchMenu;//查找菜单
	QMenu *basicMenu;//基本查询菜单
	QMenu *multipleMenu;//综合查询菜单
	QMenu *advancedMenu;//高级查询菜单
	QMenu *helpMenu;//关于菜单

	QToolBar *toolBar;
	QToolBar *mainToolBar;

	QBuffer myLocalBuf;

	QMdiArea *mdiarea;
public:
	Statistic *staDialog;
	LiteralFind *literalFindDialog;//文字查找
	ControlDock *controlDock;
private:
	GraphicFind *graphicFindDialog;//图形查找
	QLabel *locationLabel;

	static QProgressBar *qb;

	QSignalMapper *windowMapper;  //定义mapper为程序功能与每个界面对应
	QDir pluginsDir;			  //插件dir	
	QStringList pluginFileNames;  //插件名字
	std::vector<MeshIOInterface*> meshIOPlugins; //插件向量

	QDir lastUsedDirectory;  //This will hold the last directory that was used to load/save a file/project in

	QSqlDatabase db;
};

#endif