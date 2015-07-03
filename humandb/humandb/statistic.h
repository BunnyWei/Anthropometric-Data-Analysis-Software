#ifndef STATISTIC_H
#define STATISTIC_H

//#define EDIT_PickPoints_PLUGIN_EXPORT
#include "../edit_pickpoints/editpickpoints.h"

#include <QWidget>
#include <QSqlQuery>
#include <QMap>
#include <QList>
#include <cassert>
#include "ui_statistic.h"
#include "chartwidget.h"
#include "interfaces.h"
#include "glarea.h"
#include "percentiledialog.h"
#include "perbutton.h"
#include <GL/glew.h>
#include <wrap/gl/picking.h>
#include <wrap/gl/pick.h>
#include <math.h>
#include "../edit_pickpoints/pickpointsDialog.h"
#include <vcg/space/index/grid_static_ptr.h>
#include <vcg/complex/trimesh/closest.h>

using namespace vcg;
class MyPoint;
//class MyPoint
//{
//public:
//	vcg::Point3f point; 
//	QString pointName;
//};
class QPrecise
{
public:
	QPrecise()
	{
		this->id = 0;
		this->tableName = "";
		this->precise = 0;
		this->preciseAvg = 0;
		this->preciseStd = 0;
	};
	int id;
	QString tableName;
	int precise;
	int preciseStd;
	int preciseAvg;

};
//统计类型
enum enum_staType { MAX, MIN, AVG, STD, PER, TYPESIZE};

class Statistic : public QWidget
{
	Q_OBJECT

public:
	Statistic(QWidget *parent = 0);
	~Statistic();
	Ui::StatisticClass ui;
	void drawPoints(QString &itemName);
	std::vector<MyPoint *> itemPointVector;
private:
	//Ui::StatisticClass ui;
	QStringList tableHeader;
	int item_count;
	QMap<QString, QList<float> > itemMap;
	QHash<QString, int> Hash_itemNum_id;
	QHash<QString, QString> Hash_itemName_itemNum;
	//GLArea *glArea;

	const QString D2S(double data,QString item, enum enum_staType type);
	void drawPickedPoints(std::vector<MyPoint *> &pointVector, GLArea *glArea);
	//int preUse(QString item);
	QDir pluginsDir;			  //插件dir	
	QStringList pluginFileNames;  //插件名字
	std::vector<MeshEditInterface *> meshEditPlugins; //插件向量

	QDir lastUsedDirectory;  //This will hold the last directory that was used to load/save a file/project in
	QPrecise * pQPrecise;
	

private slots:
	void on_listWidget_itemPressed(QListWidgetItem*);
	void on_exportButton_clicked();
	void on_openPushButton_clicked();
	void on_clearButton_clicked();
	void on_tableWidget_pressed(QModelIndex);
	void on_statButton_clicked();
	void on_selectNoneButton_clicked();
	void on_selectAllButton_clicked();
	void on_addButton_clicked();
	void on_tableComboBox_currentIndexChanged(int);
	void showPercentileDialog(QString itemnum, QString itemName);
	//void showParameter(QListWidgetItem * item);
};

#endif // STATISTIC_H
