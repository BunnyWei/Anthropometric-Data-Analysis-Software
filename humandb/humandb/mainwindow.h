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

#define MAXRECENTFILES 4 //����������ļ�����ʾ�������ļ���

class QAction;
class QLabel;
class QMdiArea;
class QProgressBar;

class MainWindow : public QMainWindow, MainWindowInterface // �����˼̳�MainWindowInterface��ʵ�ֲ���Ľ��롣
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
	const QString appName() const {return tr("½������������ݿ�v")+appVer(); }
	const QString appVer() const {return tr("1.0"); }

	//���ص�ǰ�����GLArea
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
		bool open(QString fileName=QString(),  GLArea *gla=0); // GLArea QT��֧��openGL������
		/////////////Slot Update Menu/////////////////////////
		//void updateMenus();  //���MDI���ĵ������У���һ�����ڱ������ʱ��,��������Ӧ�ĳ���״̬��

		void wrapSetActiveSubWindow(QWidget* window);
		void createControlDock();
		void exitWindow();//�˳�
		void modifyPassword();//�޸�����

		void userManage();//�û�����
		void basicManage();//�������ݹ���
		void originalManage();//ԭʼ���ݹ���
		void delData();//����ɾ��

		void literalSearch();//���ֲ���
		void graphicSearch();//ͼ�β���

		void staticSize();//�����ߴ��ѯ

		void allParameter();//ȫ������ѯ
		void standardPerson();//��׼�˲�ѯ

		void indirectSearch();//��Ӳ�ѯ
		void relativeSearch();//��ز�����ѯ
		void correlationAnalysis();//����Է���
		void centileSearch();//�ٷ�λ��ѯ
		void applyEditMode();

		void help();//����
		void showGLA();//��ʾ��ά����

		void staticSizeSearch();
		void functionSearch();
		void jointSearch();
		void operateSearch();
		void sportSearch();
		void mentalSearch();

private:
	void addFileMenu();//����ļ��˵�
	void addDataManageMenu();//������ݹ���˵�
	void addSearchMenu();//��Ӳ��Ҳ˵�
	void addBasicMenu();//��ӻ�����ѯ�˵�
	void addmultipleMenu();//����ۺϲ�ѯ�˵�
	void addAdvancedMenu();//��Ӹ߼���ѯ�˵�
	void addHelpMenu();//��ӹ���

	void createActions();
	void createMenus();
	void createContextMenu();
	void createToolBars();
	void createStatusBar();
	/*bool createConnection();*/
public:
	void loadPlugins(); //������أ��ڸ���Ŀ������֧�ִ򿪲�ͬ����ά��ʽ���ļ�
	void setCurrentFile(const QString &fileName); //���ô�file��app����ص�current file������
	//void updateRecentFileActions(); //���������File Actions
private:
	//���嶯��

	QAction *exitAction;//�˳�
	QAction *passwordAction;//�޸�����

	QAction *userAction;//�û�����
	QAction *basicAction;//�������ݹ���
	QAction *originalAction;//ԭʼ���ݹ���
	QAction *deleteAction;//����ɾ��

	QAction *literalSearchAction;//���ֲ���
	QAction *graphicSearchAction;//ͼ�β���

	QAction *staticAction;//�����ߴ��ѯ

	QAction *allAction;//ȫ������ѯ
	QAction *standardAction;//��׼�˲�ѯ

	QAction *indirectAction;//��Ӳ�ѯ
	QAction *relativeAction;//��ز�����ѯ
	QAction *correlationAction;//����Է���
	QAction *centileAction;//�ٷ�λ��ѯ

	QAction *helpAction;//����
	QAction *glAction;//��ά��ʾ

	//һ�¶���ÿ��������λ��Ӧ��ACTION
	QAction *staticSizeAction;
	QAction *functionAction;
	QAction *jointAction;
	QAction *operateAction;
	QAction *sportAction;
	QAction *mentalAction;

	//����˵�
	QMenu *fileMenu;//�ļ��˵�
	QMenu *dataMenu;//���ݹ���˵�
	QMenu *searchMenu;//���Ҳ˵�
	QMenu *basicMenu;//������ѯ�˵�
	QMenu *multipleMenu;//�ۺϲ�ѯ�˵�
	QMenu *advancedMenu;//�߼���ѯ�˵�
	QMenu *helpMenu;//���ڲ˵�

	QToolBar *toolBar;
	QToolBar *mainToolBar;

	QBuffer myLocalBuf;

	QMdiArea *mdiarea;
public:
	Statistic *staDialog;
	LiteralFind *literalFindDialog;//���ֲ���
	ControlDock *controlDock;
private:
	GraphicFind *graphicFindDialog;//ͼ�β���
	QLabel *locationLabel;

	static QProgressBar *qb;

	QSignalMapper *windowMapper;  //����mapperΪ��������ÿ�������Ӧ
	QDir pluginsDir;			  //���dir	
	QStringList pluginFileNames;  //�������
	std::vector<MeshIOInterface*> meshIOPlugins; //�������

	QDir lastUsedDirectory;  //This will hold the last directory that was used to load/save a file/project in

	QSqlDatabase db;
};

#endif