#include "statistic.h"
#include "query.h"
#include <qDebug>
#include <QSqlQuery>
#include <QVariant>
#include "mainwindow.h"

Statistic::Statistic(QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);

	item_count = 0;

	ui.socialComboBox->addItem("全部");
	ui.socialComboBox->addItem("东北区");
	ui.socialComboBox->addItem("华北区");
	ui.socialComboBox->addItem("西北区");
	ui.socialComboBox->addItem("东南区");
	ui.socialComboBox->addItem("华中区");
	ui.socialComboBox->addItem("华南区");
	ui.socialComboBox->addItem("西南区");
	ui.socialComboBox->addItem("防化兵");
	ui.socialComboBox->addItem("装甲兵");
	ui.socialComboBox->addItem("工程兵");
	ui.socialComboBox->addItem("炮兵");
	ui.socialComboBox->addItem("步兵");

	ui.tableComboBox->addItem("全部", "all");
	ui.tableComboBox->addItem("基本尺寸", "static");
	ui.tableComboBox->addItem("功能尺寸", "func");
	ui.tableComboBox->addItem("关节转角", "joint");
	ui.tableComboBox->addItem("操作力", "operate");
	ui.tableComboBox->addItem("运动生理", "sport");
	ui.tableComboBox->addItem("心理参数", "mental");

	//**********************************************************

	ui.tableWidget->setColumnCount(9);
	/*ui.tableWidget->setRowCount(500);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);*/
	for (int i = 0; i < 9; i++) {
		ui.tableWidget->setColumnWidth(i, 70);
	}
	for (int i = 0; i < 500; i++) {
		ui.tableWidget->setRowHeight(i, 30);
	}

	tableHeader.append("参数名称"); 
	tableHeader.append("最小值"); 
	tableHeader.append("最大值"); 
	tableHeader.append("平均值"); 
	tableHeader.append("标准差"); 
	tableHeader.append("P5");
	tableHeader.append("P50"); 
	tableHeader.append("P95"); 
	tableHeader.append("百分位");
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader); 

	QSqlQuery query;
	query.exec("select item_id, itemnumber from item");
	while (query.next())
	{
		int id = query.value(0).toInt();
		QString itemNum = query.value(1).toString();
		Hash_itemNum_id.insert(itemNum, id);
	}

	ui.addButton->setVisible(false);
	ui.clearButton->setVisible(false);
	ui.percentListWidget->setVisible(false);
	ui.itemLabel->setVisible(false);

	QString dateStr = QDateTime::currentDateTime().toString("yyyy-MM-dd");
	ui.fileNameLineEdit->setText(QString("参数导出文件") + dateStr + ".xls");

	QSqlQuery preciseQuery;
	preciseQuery.exec("select count(*) from precise");
	preciseQuery.next();
	int iCount = preciseQuery.value(0).toInt();
	pQPrecise = new QPrecise[iCount];

	QSqlQuery preQuery;
	preQuery.exec("select * from precise");
	preQuery.next();
	for (int i = 0; i < iCount; ++i)
	{
		pQPrecise[i].id = preQuery.value(0).toInt();
		pQPrecise[i].tableName = preQuery.value(1).toString();
		pQPrecise[i].precise = preQuery.value(2).toInt();
		pQPrecise[i].preciseStd = preQuery.value(3).toInt();
		pQPrecise[i].preciseAvg = preQuery.value(4).toInt();
		preQuery.next();
	}


	/*MainWindow *win = MainWindow::instance();
	glArea = win->GLA();*/

	//connect(ui.listWidget, SIGNAL(itemPressed(QListWidgetItem * item)), this, SLOT(showParameter(QListWidgetItem * item)));

}

Statistic::~Statistic()
{

}

void Statistic::on_tableComboBox_currentIndexChanged(int ind)
{
	ui.listWidget->clear();
	Hash_itemName_itemNum.clear();

	QString table = ui.tableComboBox->currentText();
	QSqlQuery query;
	QString sql = "select itemname, itemnumber from item";
	if (table != "全部") {
		sql += " where category = '" + table + "'";
	}
	qDebug() << sql << endl;
	query.exec(sql);
	while (query.next()) {
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		Hash_itemName_itemNum.insert(itemname, itemnumber);
		QListWidgetItem *item = new QListWidgetItem(itemname);
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		ui.listWidget->addItem(item);
	}
}

void Statistic::on_addButton_clicked()
{
	//QListWidgetItem *item;

	//int size = ui.listWidget->count();
	//for (int i = 0; i < ui.listWidget->count(); i++) {
	//	item = ui.listWidget->item(i);
	//	if ( item->checkState() == Qt::Checked ) {
	//		QString itemname = item->text();	/* 测量项目中文名 */
	//		QString itemnumber = item->data(Qt::UserRole).toString();	/* 测量项目数据库字段名 */
	//		if (!itemMap.contains(itemnumber)) 
	//		{
	//			QTableWidgetItem *itt = new QTableWidgetItem(itemname);
	//			itt->setData(Qt::UserRole, itemnumber);
	//			ui.tableWidget->setItem(item_count++, 0, itt);
	//			itemMap.insert(itemnumber, QList<float>());
	//		}
	//	}
	//}
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "excelimport");
	QString dsn = QString("DRIVER={Microsoft Excel Driver (*.xls)};DSN='';FIRSTROWHASNAMES=1;READONLY=1;CREATE_DB=\"%1\";DBQ=%2").arg("item.xls").arg("item.xls");
	db.setDatabaseName(dsn);
	bool fDBOpen = db.open();
	QSqlQuery *excelQuery = new QSqlQuery(db);

	QString sql = "SELECT * FROM [Sheet1$]";
	bool f = excelQuery->exec(sql);

	QSqlQuery query;
	QString insertSql = "";
	QString itemnumber;
	QString itemname;
	QString category;
	QString posture;
	QString measurebody;
	QString itemdefinition;
	QString measuretool;
	QString itemmeasure;
	while (excelQuery->next())
	{
		QString itemnumber = excelQuery->value(0).toString();
		QString itemname = excelQuery->value(1).toString();
		QString category = excelQuery->value(2).toString();
		QString posture = excelQuery->value(3).toString();
		QString measurebody = excelQuery->value(4).toString();
		QString itemdefinition = excelQuery->value(5).toString();
		QString measuretool = excelQuery->value(6).toString();
		QString itemmeasure = excelQuery->value(7).toString();
		insertSql = "insert into item (itemnumber, itemname, category, posture, measurebody, itemdefinition, measuretool, itemmeasure) \
					values (?, ?, ?, ?, ?, ?, ?, ?)";
		query.prepare(insertSql);
		query.addBindValue(itemnumber);
		query.addBindValue(itemname);
		query.addBindValue(category);
		query.addBindValue(posture);
		query.addBindValue(measurebody);
		query.addBindValue(itemdefinition);
		query.addBindValue(measuretool);
		query.addBindValue(itemmeasure);
		query.exec();
	}

}

void Statistic::on_selectAllButton_clicked()
{
	QList<QListWidgetItem *> list = ui.listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
	for (int i = 0; i < list.size(); ++i) {
		list.at(i)->setCheckState(Qt::Checked);
	}
}

void Statistic::on_selectNoneButton_clicked()
{
	QList<QListWidgetItem *> list = ui.listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
	for (int i = 0; i < list.size(); ++i) {
		list.at(i)->setCheckState(Qt::Unchecked);
	}
}

void Statistic::on_statButton_clicked()
{
#if 0
	QTableWidgetItem *tit;
	QString social = ui.socialComboBox->currentText();
	Stat stat;
	Query *query = Query::getQuery();


	for (int i = 0; i < item_count; i++) {
		tit = ui.tableWidget->item(i, 0);
		QString itemnumber = tit->data(Qt::UserRole).toString();
		QString itemName = tit->text();

		if (social.endsWith("兵")) {
			query->query_data(stat, itemnumber, "", "", social, "", "");
		} else if (social.endsWith("区")) {
			query->query_data(stat, itemnumber, "", social, "", "", "");
		} else {
			query->query_data(stat, itemnumber, "", "", "", "", "");
		}

		if (-1 == stat.stat_min() && -1 == stat.stat_avg() && -1 == stat.stat_std())
		{
			ui.tableWidget->setItem(i, 1, new QTableWidgetItem(""));	/* 最小值 */
			ui.tableWidget->setItem(i, 2, new QTableWidgetItem(""));	/* 平均值 */
			ui.tableWidget->setItem(i, 3, new QTableWidgetItem(""));	/* 最大值 */
			ui.tableWidget->setItem(i, 4, new QTableWidgetItem(""));	/* %5分位 */
			ui.tableWidget->setItem(i, 5, new QTableWidgetItem(""));	/* %50分位 */
			ui.tableWidget->setItem(i, 6, new QTableWidgetItem(""));	/* %95分位 */
			ui.tableWidget->setItem(i, 7, new QTableWidgetItem(""));	/* 标准差 */
		}
		else
		{
			ui.tableWidget->setItem(i, 1, new QTableWidgetItem(D2S(stat.stat_min())));	/* 最小值 */
			ui.tableWidget->setItem(i, 2, new QTableWidgetItem(D2S(stat.stat_avg())));	/* 平均值 */
			ui.tableWidget->setItem(i, 3, new QTableWidgetItem(D2S(stat.stat_max())));	/* 最大值 */
			ui.tableWidget->setItem(i, 4, new QTableWidgetItem(D2S(stat.percentile(0.05))));	/* %5分位 */
			ui.tableWidget->setItem(i, 5, new QTableWidgetItem(D2S(stat.percentile(0.5))));	/* %50分位 */
			ui.tableWidget->setItem(i, 6, new QTableWidgetItem(D2S(stat.percentile(0.95))));	/* %95分位 */
			ui.tableWidget->setItem(i, 7, new QTableWidgetItem(D2S(stat.stat_std())));	/* 标准差 */
		}
		PerButton *perBtn = new PerButton(itemnumber, itemName, this);
		ui.tableWidget->setCellWidget(i, 8, perBtn);
		connect(perBtn, SIGNAL(clicked()), perBtn, SLOT(showItem()));
		connect(perBtn, SIGNAL(clickItem(QString, QString)), this, SLOT(showPercentileDialog(QString, QString)));

		QList<float> *list = &itemMap.find(itemnumber).value();
		list->clear();
		for (int k = 1; k < 100; k++) {
			float p = (float)k/100;
			list->append(stat.percentile(p));
		}
	}
#endif

	itemMap.clear();
	ui.tableWidget->clear();
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader); 
	QString social = ui.socialComboBox->currentText();
	QListWidgetItem * item;//下拉列表项
	QString itemname,nameDb;//测量参数
	int item_id;
	int index = 0;	/* 测量项目在表格中的行号 */
	//遍历测量项目列表，如果被选中，怎统计它，并把统计结果显示在表格
	//query_data(Stat &stat, QString item, QString nativeplace, 
	// QString district, QString armtype, QString education, QString militaryrank)
	QSqlQuery query;
	int selectedItem=0;
	for (int i = 0; i < ui.listWidget->count(); i++) 
	{
		item = ui.listWidget->item(i);
		if ( item->checkState() == Qt::Checked ) 
		{
			itemname = item->text();	/* 测量项目中文名 */
			nameDb = item->data(Qt::UserRole).toString();	/* 测量项目数据库字段名 */
			item_id = Hash_itemNum_id.value(nameDb);
			itemMap.insert(nameDb, QList<float>());
			selectedItem+=1;
			ui.tableWidget->setRowCount(selectedItem);
			ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
		}
		else
		{
			continue;
		}
		QString sql = "select * from statisticmemory where item_id = '" + QString("%1").arg(item_id) + "'";
		sql += " and social = '" + social + "'";
		//qDebug() << "###SQL:" << sql;
		query.exec(sql);
		query.next();

		QTableWidgetItem *itt = new QTableWidgetItem(itemname);
		ui.tableWidget->setItem(selectedItem-1, 0, itt);		/* 测量项目名称 */
		double minValue;
		double maxValue;
		double avgValue;
		double stdValue;

		minValue = query.value(2).toDouble();
		maxValue = query.value(3).toDouble();
		avgValue = query.value(4).toDouble();
		stdValue = query.value(5).toDouble();
		QList<float> *list = &itemMap.find(nameDb).value();
		list->clear();
		float p;
		for (int k = 6; k < 105; k++) {
			p = query.value(k).toDouble();
			list->append(p);
		}

		if (-1 == minValue && -1 == avgValue && -1 == stdValue)
		{
			ui.tableWidget->setItem(selectedItem-1, 1, new QTableWidgetItem(""));	/* 最小值 */
			ui.tableWidget->setItem(selectedItem-1, 2, new QTableWidgetItem(""));	/* 平均值 */
			ui.tableWidget->setItem(selectedItem-1, 3, new QTableWidgetItem(""));	/* 最大值 */
			ui.tableWidget->setItem(selectedItem-1, 4, new QTableWidgetItem(""));	/* %5分位 */
			ui.tableWidget->setItem(selectedItem-1, 5, new QTableWidgetItem(""));	/* %50分位 */
			ui.tableWidget->setItem(selectedItem-1, 6, new QTableWidgetItem(""));	/* %95分位 */
			ui.tableWidget->setItem(selectedItem-1, 7, new QTableWidgetItem(""));	/* 标准差 */
		}
		else
		{
			//得到table值，判断与表precise中的字段是否相同
			QString table;
			if (nameDb.startsWith("hand")) {
				table = "STATIC";
			} else if (nameDb.startsWith("h")) {
				table= "STATIC";
			} else if (nameDb.startsWith("f")) {
				table = "FUNC";
			} else if (nameDb.startsWith("o")) {
				table = "OPERATE";
			} else if (nameDb.startsWith("st")) {
				table = "STATIC";
			} else if (nameDb.startsWith("s"))  {
				table = "SPORT";
			} else if (nameDb.startsWith("j")) {
				table = "JOINT";
			} else if (nameDb.startsWith("m")) {
				table = "MENTAL";
			}
			table=table.toLower();
			//qDebug() << "###table:" << table;
			ui.tableWidget->setItem(selectedItem-1, 1, new QTableWidgetItem(D2S(query.value(2).toDouble(),table, MIN)));	/* 最小值 */
			ui.tableWidget->setItem(selectedItem-1, 2, new QTableWidgetItem(D2S(query.value(3).toDouble(),table, MAX)));	/* 平均值 */
			ui.tableWidget->setItem(selectedItem-1, 3, new QTableWidgetItem(D2S(query.value(4).toDouble(),table, AVG)));	/* 最大值 */
			ui.tableWidget->setItem(selectedItem-1, 4, new QTableWidgetItem(D2S(query.value(5).toDouble(),table, STD)));	/* 标准差 */
			ui.tableWidget->setItem(selectedItem-1, 5, new QTableWidgetItem(D2S(query.value(10).toDouble(),table, PER)));	/* %5分位 */
			ui.tableWidget->setItem(selectedItem-1, 6, new QTableWidgetItem(D2S(query.value(55).toDouble(),table, PER)));	/* %50分位 */
			ui.tableWidget->setItem(selectedItem-1, 7, new QTableWidgetItem(D2S(query.value(100).toDouble(),table, PER)));	/* %95分位 */
			//得到precise中的标准差的精度
			//int Qprecisere;
			//for(int t=0;t< 6;++t){
			//	if(table == pQPrecise[t].tableName){
			//		//qDebug() << "###pQPrecise[t].tableName:" << pQPrecise[t].tableName;
			//		Qprecisere=pQPrecise[t].preciseStd;		 
			//	}
			//}
			//if (query.value(5).toDouble() < 1) {
			//	ui.tableWidget->setItem(selectedItem-1, 4, new QTableWidgetItem(QString::number(query.value(5).toDouble(), 'g', Qprecisere)));
			//}
			//else if (query.value(5).toDouble() < 10) {
			//	ui.tableWidget->setItem(selectedItem-1, 4, new QTableWidgetItem(QString::number(query.value(5).toDouble(), 'g', Qprecisere + 1)));
			//}
			//else if (query.value(5).toDouble() < 100) {
			//	ui.tableWidget->setItem(selectedItem-1, 4, new QTableWidgetItem(QString::number(query.value(5).toDouble(), 'g', Qprecisere +2)));
			//}
			//else if (query.value(5).toDouble() < 1000) {
			//	ui.tableWidget->setItem(selectedItem-1, 4, new QTableWidgetItem(QString::number(query.value(5).toDouble(), 'g', Qprecisere +3)));
			//}
			//else if (query.value(5).toDouble() < 10000) {
			//	ui.tableWidget->setItem(selectedItem-1, 4, new QTableWidgetItem(QString::number(query.value(5).toDouble(), 'g', Qprecisere +4)));
			//}
			//else {
			//	ui.tableWidget->setItem(selectedItem-1, 4, new QTableWidgetItem(QString::number(query.value(5).toDouble(), 'g', Qprecisere +5)));
			//}

		}
		PerButton *perBtn = new PerButton(nameDb, itemname, this);
		ui.tableWidget->setCellWidget(selectedItem-1, 8, perBtn);
		connect(perBtn, SIGNAL(clicked()), perBtn, SLOT(showItem()));
		connect(perBtn, SIGNAL(clickItem(QString, QString)), this, SLOT(showPercentileDialog(QString, QString)));
	}
	index++;
}

//const QString  Statistic::D2S(double data,QString item) //double to string
//{
//	int precise;
//	QString table;
//    if (item.startsWith("hand")) {
//		table = STATIC;
//	} else if (item.startsWith("h")) {
//		table= STATIC;
//	} else if (item.startsWith("f")) {
//		table = FUNC;
//	} else if (item.startsWith("o")) {
//		table = OPERATE;
//	} else if (item.startsWith("st")) {
//		table = STATIC;
//	} else if (item.startsWith("s"))  {
//		table = SPORT;
//	} else if (item.startsWith("j")) {
//		table = JOINT;
//	} else if (item.startsWith("m")) {
//		table = MENTAL;
//	}
//	table=table.toLower();
//	if (data < 1) {
//		precise = 2;
//	}
//	else if (data < 10) {
//		precise = 3;
//	}
//	else if (data < 100) {
//		precise = 4;
//	}
//	else if (data < 1000) {
//		precise = 5;
//	}
//	else if (data < 10000) {
//		precise = 6;
//	}
//	else {
//		precise = 5;
//	}
//	return QString::number(data, 'g', precise);
//}

//const QString  Statistic::D2S(double data,QString item) //double to string
//{
//	int precise;
//	 QString table;
//      int precisere;
//   
//  if (item.startsWith("hand")) {
//		table = STATIC;
//		precisere=-1;
//	} else if (item.startsWith("h")) {
//		table= STATIC;
//		precisere=-1;
//	} else if (item.startsWith("f")) {
//		table = FUNC;
//		precisere=-1;
//	} else if (item.startsWith("o")) {
//		table = OPERATE;
//		precisere=0;
//	} else if (item.startsWith("st")) {
//		table = STATIC;
//		precisere=-1;
//	} else if (item.startsWith("s"))  {
//		table = SPORT;
//		precisere=0;
//	} else if (item.startsWith("j")) {
//		table = JOINT;
//		precisere=-2;
//	} else if (item.startsWith("m")) {
//		table = MENTAL;
//		precisere=0;
//	}
//	table=table.toLower();
//	if (table =="joint" && data < 1) {
//		precise = 2 + precisere +1;	
//	}
//	else if(table !="joint" && data < 1){
//		precise = 2 + precisere;	
//	}
//	else if (data < 10) {
//		precise = 3 + precisere ;
//	}
//	else if (data < 100) {
//		precise = 4 + precisere;
//	}
//	else if (data < 1000) {
//		precise = 5 + precisere;
//	}
//	else if (data < 10000) {
//		precise = 6 + precisere;
//	}
//	else {
//		precise = 5 + precisere;
//	}
//	return QString::number(data, 'g', precise);
//}
const QString  Statistic::D2S(double data, QString table, enum enum_staType type) //double to string
{
	int precise;
	int precisere;
	int valuePrecise = 2;
	int avgPrecise = 2;
	int stdPrecise = 2;
	for(int t = 0; t < 6; ++t)
	{
		if(table == pQPrecise[t].tableName)
		{
			valuePrecise = pQPrecise[t].precise;
			avgPrecise = pQPrecise[t].preciseAvg;
			stdPrecise = pQPrecise[t].preciseStd;
			break;
		}
	}
	//qDebug() << "###S:" << precisere;
	if (3 == type)
	{
		precisere = stdPrecise;
	}
	else
	{
		precisere = valuePrecise;
	}
	if(data < 1){
		precise =  precisere;	
	}
	else if (data < 10) {
		precise = 1 + precisere ;
	}
	else if (data < 100) {
		precise = 2 + precisere;
	}
	else if (data < 1000) {
		precise = 3 + precisere;
	}
	else if (data < 10000) {
		precise = 4 + precisere;
	}
	else {
		precise = 3 + precisere;
	}
	//qDebug() << "###SQ:" << precise;
	return QString::number(data, 'g', precise);
}
void Statistic::on_tableWidget_pressed(QModelIndex mi)
{
	ui.percentListWidget->clear();
	int row = mi.row();
	QTableWidgetItem *tit = ui.tableWidget->item(row, 0);
	if (tit == NULL) {
		return;
	}
	ui.itemLabel->setText(tit->text() + "的百分位");
	QString itemnumber = Hash_itemName_itemNum.value(tit->text());
	QList<float> *li = &itemMap.find(itemnumber).value();

	for (int i = 0; i < li->size(); i++) {
		QListWidgetItem *listItem = new QListWidgetItem(QString("%1%: %2").arg(i+1).arg(li->at(i)));
		ui.percentListWidget->addItem(listItem);
	}

	vcg::Point3f point; 
	QString name; 
	QSqlQuery query;

	MainWindow *win = MainWindow::instance();
	GLArea *glArea = win->GLA();
	if (NULL == glArea)
		return;
	glArea->itemPointVector.clear();
	QString sql = "select name, x, y, z, type, meshID from points where itemnum = '" + itemnumber + "' order by name";
	query.exec(sql);
	while (query.next())
	{
		MyPoint *localPoint = new MyPoint;
		localPoint->pointName = query.value(0).toString();
		localPoint->point[0] = query.value(1).toDouble();
		localPoint->point[1] = query.value(2).toDouble();
		localPoint->point[2] = query.value(3).toDouble();
		localPoint->type = query.value(4).toInt();
		localPoint->meshID = query.value(5).toInt();
		glArea->itemPointVector.push_back(localPoint);
	}
	glArea->showID = 1;
	glArea->update();
}

void Statistic::drawPoints(QString &itemName)
{	
	vcg::Point3f point; 
	QString name; 

	itemPointVector.clear();
	QSqlQuery query;
	QString sql = "select name, x, y, z, itemnum, itemname from points where itemnum = '";
	sql += itemName + "' order by name" ;
	query.exec(sql);
	while (query.next())
	{
		MyPoint *localPoint = new MyPoint;
		localPoint->pointName = query.value(0).toString();
		localPoint->point[0] = query.value(1).toDouble();
		localPoint->point[1] = query.value(2).toDouble();
		localPoint->point[2] = query.value(3).toDouble();

		itemPointVector.push_back(localPoint);
	}

	MainWindow *win = MainWindow::instance();
	GLArea *glArea = win->GLA();
	drawPickedPoints(itemPointVector, glArea);
	/*win->loadPlugins();*/
	//MeshEditInterface *plugin = loadEditPlugin();
	//plugin->paintPickedPoints(itemPointVector);
}

#if 1
void Statistic::drawPickedPoints(std::vector<MyPoint *> &pointVector, GLArea *glArea)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	// enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	//draw the things that we always want to show, like the names 
	glDepthFunc(GL_ALWAYS);
	glDisable(GL_DEPTH_TEST); 
	glDepthMask(GL_FALSE);

	//set point attributes
	glPointSize(4.5);
	bool showNormal = true;
	bool showPin = true;

	for(int i = 0; i < pointVector.size(); ++i)
	{
		MyPoint *localPoint = pointVector[i];
		glColor(Color4b::Blue);
		qDebug() << localPoint->point[0] << localPoint->point[1] << localPoint->point[2] << localPoint->pointName;
		glArea->renderText(localPoint->point[0], localPoint->point[1], localPoint->point[2], localPoint->pointName);

		//draw the dot if we arnt showing the normal or showing the normal as a line
		if(!showNormal || !showPin)
		{
			glColor(Color4b::Green);
			glBegin(GL_POINTS);
			glVertex(localPoint->point);
			glEnd();
		}	
	}

	//now draw the things that we want drawn if they are not ocluded 
	//we can see in bright red
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST); 
	glDepthMask(GL_TRUE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);

	glPopAttrib();	

	glArea->update();
}
#endif

void Statistic::on_clearButton_clicked()
{
	/*ui.tableWidget->clear();
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader); 
	item_count = 0;
	itemMap.clear();
	ui.percentLabel->setText("");
	ui.percentListWidget->clear();*/
}



void Statistic::showPercentileDialog(QString itemnum, QString itemName)
{
	percentileDialog *perDialog = new percentileDialog(itemnum, itemName, itemMap, this);
	perDialog->show();
}


void Statistic::on_openPushButton_clicked()
{
	QString dirName = QFileDialog::getExistingDirectory(this, tr("选择目录"), "C:\\");
	ui.dirLineEdit->setText(dirName);
}

void Statistic::on_exportButton_clicked()
{
	QString filepath = ui.dirLineEdit->text() + "/" + ui.fileNameLineEdit->text();
	QFile file(filepath);
	file.open(QFile::WriteOnly);
	QTextStream out(&file);
	//	QTableWidgetItem *item;

	for (int headnum = 0; headnum < tableHeader.size(); headnum++ ) {
		out << tableHeader.at(headnum) << "\t";
	}
	out << "\n";	
	QListWidgetItem *item;
	int row = 0;
	for (int i = 0; i < ui.listWidget->count(); i++) {
		item = ui.listWidget->item(i);
		if (item->checkState() == Qt::Checked) {
			row++;
		}
	}

	int  column = ui.tableWidget->columnCount()-1;

	for (int i = 0; i < row; i++) 
	{	
		for(int j = 0; j < column; j++) 
		{
			out<< ui.tableWidget->item(i, j)->text()<<"\t";
		}
		out<<"\n";
	}

	file.close();
	QMessageBox::information(this, "信息", "导出成功！");
	//ui.showLabel->setText(tr("导出成功！"));
}

//void Statistic::showParameter(QListWidgetItem * item)
//{
//	QString itemnumber = item->data(Qt::UserRole).toString();
//	vcg::Point3f point; 
//	QString name; 
//	QSqlQuery query;
//
//	MainWindow *win = MainWindow::instance();
//	GLArea *glArea = win->GLA();
//	glArea->itemPointVector.clear();
//	QString sql = "select name, x, y, z, type, meshID from points where itemnum = '" + itemnumber + "' order by name";
//	query.exec(sql);
//	while (query.next())
//	{
//		MyPoint *localPoint = new MyPoint;
//		localPoint->pointName = query.value(0).toString();
//		localPoint->point[0] = query.value(1).toDouble();
//		localPoint->point[1] = query.value(2).toDouble();
//		localPoint->point[2] = query.value(3).toDouble();
//		localPoint->type = query.value(4).toInt();
//		localPoint->meshID = query.value(5).toInt();
//		glArea->itemPointVector.push_back(localPoint);
//	}
//	glArea->showID = 1;
//	glArea->update();
//}

void Statistic::on_listWidget_itemPressed(QListWidgetItem *item)
{
	QString itemnumber = item->data(Qt::UserRole).toString();
	vcg::Point3f point; 
	QString name; 
	QSqlQuery query;

	MainWindow *win = MainWindow::instance();
	GLArea *glArea = win->GLA();
	if (NULL == glArea)
		return;
	glArea->itemPointVector.clear();
	QString sql = "select name, x, y, z, type, meshID from points where itemnum = '" + itemnumber + "' order by name";
	query.exec(sql);
	while (query.next())
	{
		MyPoint *localPoint = new MyPoint;
		localPoint->pointName = query.value(0).toString();
		localPoint->point[0] = query.value(1).toDouble();
		localPoint->point[1] = query.value(2).toDouble();
		localPoint->point[2] = query.value(3).toDouble();
		localPoint->type = query.value(4).toInt();
		localPoint->meshID = query.value(5).toInt();
		glArea->itemPointVector.push_back(localPoint);
	}
	glArea->showID = 1;
	glArea->update();

}