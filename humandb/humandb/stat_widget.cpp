#include <math.h>
#include "stat_widget.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QFile>
#include <QFileDialog>
#include "QGlobalVar.h"
#include "statistic.h"
StatWidget::StatWidget(QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);

	ui.groupComboBox->addItem("全部参数", "all");
	ui.groupComboBox->addItem("基本尺寸", "static");
	ui.groupComboBox->addItem("功能尺寸", "func");
	ui.groupComboBox->addItem("关节转角", "joint");
	ui.groupComboBox->addItem("操作力", "operate");
	ui.groupComboBox->addItem("运动生理", "sport");
	ui.groupComboBox->addItem("心理参数", "mental");
	
	ui.bingzhongComboBox->addItem("全部");
	ui.bingzhongComboBox->addItem("防化兵");
	ui.bingzhongComboBox->addItem("装甲兵");
	ui.bingzhongComboBox->addItem("工程兵");
	ui.bingzhongComboBox->addItem("炮兵");
	ui.bingzhongComboBox->addItem("步兵");


	ui.districtComboBox->addItem("全部");
	ui.districtComboBox->addItem("东北区");
	ui.districtComboBox->addItem("华北区");
	ui.districtComboBox->addItem("西北区");
	ui.districtComboBox->addItem("东南区");
	ui.districtComboBox->addItem("华中区");
	ui.districtComboBox->addItem("华南区");
	ui.districtComboBox->addItem("西南区");

	ui.wenhuaComboBox->addItem("全部");
	ui.wenhuaComboBox->addItem("小学");
	ui.wenhuaComboBox->addItem("初中");
	ui.wenhuaComboBox->addItem("高中");
	ui.wenhuaComboBox->addItem("中专");
	ui.wenhuaComboBox->addItem("大专");
	ui.wenhuaComboBox->addItem("本科");
	ui.wenhuaComboBox->addItem("硕士");
	ui.wenhuaComboBox->addItem("博士");

	ui.jiguanComboBox->addItem("全部");
	QSqlQuery query("select Province from province order by Province asc");
	query.exec();
	while (query.next()) {
		ui.jiguanComboBox->addItem( query.value(0).toString() );
	}

	ui.junxianComboBox->addItem("全部");
	ui.junxianComboBox->addItem("列兵");
	ui.junxianComboBox->addItem("上等兵");
	ui.junxianComboBox->addItem("下士");
	ui.junxianComboBox->addItem("中士");
	ui.junxianComboBox->addItem("上士");
	ui.junxianComboBox->addItem("四级军士长");
	//ui.junxianComboBox->addItem("五级士官");
	//ui.junxianComboBox->addItem("六级士官");
	ui.junxianComboBox->addItem("少尉");
	ui.junxianComboBox->addItem("中尉");
	ui.junxianComboBox->addItem("上尉");
	ui.junxianComboBox->addItem("少校");
	ui.junxianComboBox->addItem("中校");
    //添加自定义百分位
	for (int i = 0; i < 100; i++) 
	{
		ui.percentileComboBox->addItem(QString("%1").arg(i));
	}

	ui.tableWidget->setColumnCount(9);
	/*ui.tableWidget->setRowCount(500);*/
	for (int i = 1; i < 9; i++) {
		ui.tableWidget->setColumnWidth(i, 80);
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
	tableHeader.append("自定义百分位"); 
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader); 

	QSqlQuery entryQuery("select itemname, itemnumber from item");
	entryQuery.exec();
	while (entryQuery.next())
	{
        QString itemname = entryQuery.value(0).toString();
		QString itemnumber = entryQuery.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem( itemname );
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		ui.listWidget->addItem(item);
	}

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

}

//筛选，首先得从info表里选出符合条件的军人编号
void StatWidget::getFilter()
{
	this->filterSql = "";
	this->filter = "";
	QString jiguan = ui.jiguanComboBox->currentText();
	QString district = ui.districtComboBox->currentText();
	QString bingzhong = ui.bingzhongComboBox->currentText();
	QString wenhua = ui.wenhuaComboBox->currentText();
	QString junxian = ui.junxianComboBox->currentText();

    if ("全部" != district) {	/* 有地域参数 */
		filter += " and region='" + district + "'";
	}
	if ("全部" != junxian) {	/* 有军衔参数 */
		filter += " and junxian='" + junxian + "'";
	}
	if ("全部" != bingzhong) {	/* 有兵种参数 */
		filter += " and bingzhong='" + bingzhong + "'";
	}
	if ("全部" != jiguan) {	/* 有籍贯参数 */
		filter += " and jiguan like '" + jiguan + "%'";
	}
	if("全部" != wenhua){ /*有学历参数*/
		filter += "and wenhua='" + wenhua + "'";
	}
	filter = filter.right(filter.size()-4);
	filterSql = "";
	if (filter != "") {
		filterSql = "select count(*) from info " ;  
		filterSql = "select count(*) from info where " + filter;
	}
	else {
	//filterSql += "select count(*) from info " ;
		filterSql = "select count(*) from info " ;
	}
	//********************************************************
	
	qDebug() << "###### filterSql= " << filterSql << endl;
}
/*
* 把满足条件的测量项目添加到列表
* 
*/
int StatWidget::getcount()
{
	getFilter();
	/*QString jiguan = ui.jiguanComboBox->currentText();
	QString district = ui.districtComboBox->currentText();
	QString bingzhong = ui.bingzhongComboBox->currentText();
	QString wenhua = ui.wenhuaComboBox->currentText();
	QString junxian = ui.junxianComboBox->currentText();*/
	QSqlQuery query;
	QString sql;
	sql=this->filterSql;
	// if ("全部" == district) {	/* 有地域参数 */
	//	district="";
	//}
	//if ("全部" == junxian) {	/* 有军衔参数 */
	//	junxian="";
	//}
	//if ("全部" == bingzhong) {	/* 有兵种参数 */
	//	bingzhong="";
	//}
	//if ("全部" == jiguan) {	/* 有籍贯参数 */
	//	jiguan="";
	//}
	//if("全部" == wenhua){ /*有学历参数*/
	//	wenhua="";
	//}
	//QString sql = "select count(*)  from info where  jiguan=ui.jiguanComboBox->currentText() AND region= ui.districtComboBox->currentText() AND wenhua = ui.wenhuaComboBox->currentText() AND  bingzhong = ui.bingzhongComboBox->currentText() 	AND junxian = ui.junxianComboBox->currentText()";
	//QString sql =" select count(*) from info where  region='"+district+"' and junxian='"+junxian+"' and bingzhong='"+bingzhong+"'and jiguan like '"+ jiguan + "%'and wenhua='" + wenhua + "'";
	qDebug() << sql << endl;
	bool b = query.exec(sql);
	int count;
	while (query.next()) {
		count = query.value(0).toInt();
	}
	return count;
}
void StatWidget::on_okButton_clicked()//确定
{
	//getFilter();
	ui.listWidget->clear();
	QString todayStr = QDateTime::currentDateTime().toString("yyyy-MM-dd");
	QString fileName =ui.groupComboBox->currentText() +"统计分析"+ todayStr + ".xls";
	ui.fileNameLineEdit->setText(fileName);

	QString groupStr = ui.groupComboBox->currentText();
	QString typeStr = ui.typeComboBox->currentText();

	QSqlQuery query;
	QString sql = "select itemname,itemnumber from item ";

	if (groupStr != "全部参数")
	{
		if (typeStr != "全部")
		{
			sql += "where category = '" + groupStr + "' and posture = '" + typeStr + "'";
		}
		else
		{
			sql += "where category = '" + groupStr + "'";
		}
	}

	//qDebug() << "查找参数SQL: " << sql << endl;

	query.exec(sql);

	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem( itemname );
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		ui.listWidget->addItem(item);
	}
	
}
#if 1
void StatWidget::on_statButton_clicked()
{
	ui.tableWidget->clear();
	
	QString customPercentile = "P" + ui.percentileComboBox->currentText();//自定义百分位
	tableHeader.removeAt(8);
	tableHeader.append(customPercentile);//使自定义表头显示用户选择百分位
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader); //添加列标题
	int per = customPercentile.remove('P').toInt();
	float percent = (float)per/100;
	
    QListWidgetItem * item;//下拉列表项
	QString itemname,nameDb;//测量参数
	//新增
//	QLable  countpeople;
	int index = 0;	/* 测量项目在表格中的行号 */

	Query *query = Query::getQuery();
	Stat stat;
	QString jiguan = ui.jiguanComboBox->currentText();
	if ("全部" == jiguan)
	{
		jiguan = "";
	}
	QString district = ui.districtComboBox->currentText();
	if ("全部" == district)
	{
		district = "";
	}
	QString bingzhong = ui.bingzhongComboBox->currentText();
	if ("全部" == bingzhong)
	{
		bingzhong = "";
	}
	QString wenhua = ui.wenhuaComboBox->currentText();
	if ("全部" == wenhua)
	{
		wenhua = "";
	}
	QString junxian = ui.junxianComboBox->currentText();
	if ("全部" == junxian)
	{
		junxian = "";
	}
	//QLable countpeople=query->get_people_count;//

	//遍历测量项目列表，如果被选中，怎统计它，并把统计结果显示在表格
	//query_data(Stat &stat, QString item, QString nativeplace, 
					  // QString district, QString armtype, QString education, QString militaryrank)
	int selectedItem=0;
	for (int i = 0; i < ui.listWidget->count(); i++) 
	{
		item = ui.listWidget->item(i);
		if ( item->checkState() == Qt::Checked ) 
		{
			itemname = item->text();	/* 测量项目中文名 */
			nameDb = item->data(Qt::UserRole).toString();	/* 测量项目数据库字段名 */
			selectedItem+=1;
			 ui.tableWidget->setRowCount(selectedItem);
	    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
		}
		else
		{
			continue;
		}

		QTableWidgetItem *itt = new QTableWidgetItem(itemname);
		ui.tableWidget->setItem(index, 0, itt);		/* 测量项目名称 */
       
	  
		query->query_data(stat, nameDb, jiguan, district, bingzhong, wenhua, junxian);
		

		/*qDebug() << "最小值：" << stat.stat_min() <<endl;
		qDebug() << "平均值：" << stat.stat_avg() <<endl;
		qDebug() << "最大值：" << stat.stat_max() <<endl;
		qDebug() << "标准差：" << stat.stat_std() <<endl;
		qDebug() << "5%：" << stat.percentile(0.05) <<endl;
		qDebug() << "50%：" << stat.percentile(0.5) <<endl;
		qDebug() << "95%：" << stat.percentile(0.95) <<endl;
		qDebug() << "自定义百分位：" << stat.percentile(percent) <<endl;*/

		if (-1 == stat.stat_min() && -1 == stat.stat_avg() && -1 == stat.stat_std())
		{
			ui.tableWidget->setItem(selectedItem-1, 1, new QTableWidgetItem(""));	/* 最小值 */
			ui.tableWidget->setItem(selectedItem-1, 2, new QTableWidgetItem(""));	/* 平均值 */
			ui.tableWidget->setItem(selectedItem-1, 3, new QTableWidgetItem(""));	/* 最大值 */
			ui.tableWidget->setItem(selectedItem-1, 4, new QTableWidgetItem(""));	/* %5分位 */
			ui.tableWidget->setItem(selectedItem-1, 5, new QTableWidgetItem(""));	/* %50分位 */
			ui.tableWidget->setItem(selectedItem-1, 6, new QTableWidgetItem(""));	/* %95分位 */
			ui.tableWidget->setItem(selectedItem-1, 7, new QTableWidgetItem(""));	/* 标准差 */
			ui.tableWidget->setItem(selectedItem-1, 8, new QTableWidgetItem(""));	/* 标准差 */
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
			ui.tableWidget->setItem(selectedItem-1, 1, new QTableWidgetItem(D2S(stat.stat_min(), table, MIN)));	/* 最小值 */
			ui.tableWidget->setItem(selectedItem-1, 2, new QTableWidgetItem(D2S(stat.stat_max(), table, MAX)));	/* 最大值 */
			ui.tableWidget->setItem(selectedItem-1, 3, new QTableWidgetItem(D2S(stat.stat_avg(), table, AVG)));	/* 平均值 */
			ui.tableWidget->setItem(selectedItem-1, 4, new QTableWidgetItem(D2S(stat.stat_std(), table, STD)));	/* 标准差 */
			
			ui.tableWidget->setItem(selectedItem-1, 5, new QTableWidgetItem(D2S(stat.percentile(0.05), table, PER)));	/* %5分位 */
			ui.tableWidget->setItem(selectedItem-1, 6, new QTableWidgetItem(D2S(stat.percentile(0.5), table, PER)));	/* %50分位 */
			ui.tableWidget->setItem(selectedItem-1, 7, new QTableWidgetItem(D2S(stat.percentile(0.95), table, PER)));	/* %95分位 */
			if (percent < 0.0000001){
				ui.tableWidget->setItem(selectedItem-1, 8, new QTableWidgetItem(""));
			}
			else{
				ui.tableWidget->setItem(selectedItem-1, 8, new QTableWidgetItem(D2S(stat.percentile(percent), table, PER)));	/* 标准差 */
			}
		}
		index++;
	}
	 QString label = QString::number(getcount()) + "条记录";
	   ui.label_count->setText(label);
}
#endif

#if 0
void StatWidget::on_statButton_clicked()
{
	getFilter();
	ui.showLabel->setText(tr(""));
	ui.tableWidget->clear();
	QString percentile = ui.percentileComboBox->currentText();
	tableHeader.removeAt(8);
	tableHeader.append(percentile);//使自定义表头显示用户选择百分位
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader); //添加列标题
	QString filter = "";

	QListWidgetItem * item;//下拉列表项
	QString itemname,nameDb;//测量参数
	QSqlQuery query, query2;
	QString sql, sql2;	/* sql用来求最大值，最小值，方差等，sql2用来求百分位 */
	QString group;
	QString table; //查找对应的表
	float variance;//方差
	int index = 0;	/* 测量项目在表格中的行号 */

	group = ui.groupComboBox->itemData( ui.groupComboBox->currentIndex(), Qt::UserRole ).toString();
	//遍历测量项目列表，如果被选中，怎统计它，并把统计结果显示在表格
	for (int i = 0; i < ui.listWidget->count(); i++) {
		item = ui.listWidget->item(i);
		if ( item->checkState() == Qt::Checked ) {
			itemname = item->text();	/* 测量项目中文名 */
			nameDb = item->data(Qt::UserRole).toString();	/* 测量项目数据库字段名 */
#if 1
            //根据待查找的字段名决定要查找的表名
			if (nameDb.startsWith("hand")) 
			{
				table = "handtemp";
			} 
			else if (nameDb.startsWith("h")) 
			{
				table = "headtemp";
			} 
			else if (nameDb.startsWith("f")) 
			{
				table = "functemp";
			} 
			else if (nameDb.startsWith("o")) 
			{
				table = "operatetemp";
			} 
			else if (nameDb.startsWith("st")) 
			{
				table = "statictemp";
			} 
			else if (nameDb.startsWith("s")) 
			{
				table = "sporttemp";
			} 
			else if (nameDb.startsWith("j")) 
			{
				table = "jointtemp";
			} 
			else if (nameDb.startsWith("m")) 
			{
				table = "mentaltemp";
			} 
			else 
			{
				qDebug() << "nameDb " << nameDb << "no table" << endl;
			}
#endif
#if 0
			if (nameDb.startsWith("hand")) 
			{
				table = "hand";
			} 
			else if (nameDb.startsWith("h")) 
			{
				table = "head";
			} 
			else if (nameDb.startsWith("f")) 
			{
				table = "func";
			} 
			else if (nameDb.startsWith("o")) 
			{
				table = "operate";
			} 
			else if (nameDb.startsWith("st")) 
			{
				table = "static";
			} 
			else if (nameDb.startsWith("s")) 
			{
				table = "sport";
			} 
			else if (nameDb.startsWith("j")) 
			{
				table = "joint";
			} 
			else if (nameDb.startsWith("m")) 
			{
				table = "mental";
			} 
			else 
			{
				qDebug() << "nameDb " << nameDb << "no table" << endl;
			}
#endif

			//心理数据要过滤掉测量值为-1的记录，功能数据和头部数据要过滤掉测量值为0的记录
			if(!filterSql.isEmpty()){
				sql = "select max(" + nameDb + "),avg(" + nameDb + "), min(" + nameDb + ") ,std(" + nameDb + "),count(" + nameDb +") from " + table + " where " + nameDb + "<9999 " + filter + " and number in(" + filterSql +")";
				sql2 = "select " + nameDb + " from " + table + " where number in(" +filterSql + ") and " + nameDb +  "<9999 " + filter + " order by " + nameDb + " asc ";
			}else{
				sql = "select max(" + nameDb + "),avg(" + nameDb + "), min(" + nameDb + ") ,std(" + nameDb + "),count(" + nameDb +") from " + table + " where " + nameDb + "<9999 " + filter;
				sql2 = "select " + nameDb + " from " + table + " where " + nameDb +  " <9999 " + filter + " order by " + nameDb + " asc ";
			}
		}
		else {
			continue;
		}
		qDebug() << sql << endl;
		qDebug() << sql2 << endl;
		query.prepare(sql);
		query2.prepare(sql2);
		query.exec();
		query2.exec();
		query.next();

		int recordCount = query.value(4).toInt();
		double maxV, minV, avgV;
		maxV = query.value(0).toDouble();
		avgV = query.value(1).toDouble();
		minV = query.value(2).toDouble();
		float sss = (maxV-avgV) / (avgV-minV);
		QTableWidgetItem *itt = new QTableWidgetItem(itemname);
		if (sss > 5 || sss < 0.2) {
			itt->setBackgroundColor(Qt::red);
		}
		ui.tableWidget->setItem(index, 0, itt);		/* 测量项目名称 */
		
		if( 0 == recordCount )
		{
			ui.tableWidget->setItem(index, 1, new QTableWidgetItem(" "));
			ui.tableWidget->setItem(index, 2, new QTableWidgetItem(" "));
			ui.tableWidget->setItem(index, 3, new QTableWidgetItem(" "));
			ui.tableWidget->setItem(index, 4, new QTableWidgetItem(" "));	
			ui.tableWidget->setItem(index, 5, new QTableWidgetItem(" "));
			ui.tableWidget->setItem(index, 6, new QTableWidgetItem(" "));
			ui.tableWidget->setItem(index, 7, new QTableWidgetItem(" "));
			ui.tableWidget->setItem(index, 8, new QTableWidgetItem(" "));
			index++;
		}
		else
		{
			ui.tableWidget->setItem(index, 1, new QTableWidgetItem(D2S(minV)));	/* 最小值 */
			ui.tableWidget->setItem(index, 2, new QTableWidgetItem(D2S(avgV)));	/* 平均值 */		
			ui.tableWidget->setItem(index, 3, new QTableWidgetItem(D2S(maxV)));	/* 最大值 */
			variance = query.value(3).toString().toFloat();
			QTableWidgetItem *it = new QTableWidgetItem( D2S(variance ));
			ui.tableWidget->setItem(index, 4, it);	/* 标准差 */

			//百分位
			double result;
			int per = percentile.remove('%').toInt();
			float percent = (float)per/100;
			int count = query2.size();
			float r = count *  0.05;
			float s = count * 0.5;
			float t = count * 0.95;
			float d = count * percent;
			double value_i0, value_i1;
			int i0, i1;

			//5%分位
			i0 = floor(r);
			i1 = ceil(r);
			query2.seek(i0);
			value_i0 = query2.value(0).toDouble();
			query2.next();
			value_i1 = query2.value(0).toDouble();
			result = (i0 == i1) ? value_i0 : value_i0 * (i1 - r) + value_i1 * (r - i0);
			ui.tableWidget->setItem(index, 5, new QTableWidgetItem( D2S(result)));
			//50%分位
			i0 = (int) floor(s);
			i1 = (int) ceil(s);
			query2.seek(i0);
			value_i0 = query2.value(0).toDouble();
			query2.next();
			value_i1 = query2.value(0).toDouble();
			result = (i0 == i1) ? value_i0 : value_i0 * (i1 - s) + value_i1 * (s - i0);
			ui.tableWidget->setItem(index, 6, new QTableWidgetItem( D2S(result) ));
			//95%分位
			i0 = (int) floor(t);
			i1 = (int) ceil(t);
			if (i0 == (count-1)) {
				i1 = i0;
			}
			query2.seek(i0);
			value_i0 = query2.value(0).toDouble();
			query2.next();
			value_i1 = query2.value(0).toDouble();
			result = (i0 == i1) ? value_i0 : value_i0 * (i1 - t) + value_i1 * (t - i0);
			ui.tableWidget->setItem(index, 7, new QTableWidgetItem( D2S(result) ));
			//自定义百分位
			i0 = (int) floor(d);
			i1 = (int) ceil(d);
			if (i0 == (count-1)) {
				i1 = i0;
			}
			query2.seek(i0);
			value_i0 = query2.value(0).toDouble();
			query2.next();
			value_i1 = query2.value(0).toDouble();
			result = (i0 == i1) ? value_i0 : value_i0 * (i1 - d) + value_i1 * (d - i0);
			ui.tableWidget->setItem(index, 8, new QTableWidgetItem( D2S(result) ));
			index++;
		}

#if 0
		//为每一个字段建立唯一索引
		// create index index_h14 on headtemp(h14);
		QSqlQuery indexQuery;
		QString indexSql = "create index index_" + nameDb + " using btree on " + table + "(" + nameDb + ")";
		qDebug() << indexSql;
		indexQuery.exec(indexSql);
#endif
	}
}
#endif
void StatWidget::on_selectAllButton_clicked()
{
	QList<QListWidgetItem *> list = ui.listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
	for (int i = 0; i < list.size(); ++i) {
		list.at(i)->setCheckState(Qt::Checked);
	}
}

void StatWidget::on_selectNoneButton_clicked()
{
	QList<QListWidgetItem *> list = ui.listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
	for (int i = 0; i < list.size(); ++i) {
		list.at(i)->setCheckState(Qt::Unchecked);
	}
}

const QString  StatWidget::D2S(double data, QString table, enum enum_staType type) //double to string
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
void StatWidget::on_openPushButton_clicked()
{
	QString dirName = QFileDialog::getExistingDirectory(this, tr("选择目录"), "C:\\");
	ui.dirLineEdit->setText(dirName);
}

void StatWidget::on_exportButton_clicked()
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

	int  column = ui.tableWidget->columnCount();

	for (int i = 0; i < row; i++) 
	{	
		for(int j = 0; j < column; j++) 
		{
			out<< ui.tableWidget->item(i, j)->text()<<"\t";
		}
		out<<"\n";
	}

	file.close();
	ui.showLabel->setText(tr("导出成功！"));
}

void StatWidget::on_groupComboBox_currentIndexChanged(int index)
{
	QString group = ui.groupComboBox->itemData(index, Qt::UserRole).toString();
	QString tableName = ui.groupComboBox->currentText();

	if ("全部参数" == tableName)
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("全部");
		return;
	}
	QSqlQuery query;
	QString sql = "select distinct posture from item where category = '";
	sql += tableName + "'";
	query.exec(sql);
	ui.typeComboBox->clear();
	ui.typeComboBox->addItem("全部");

	while (query.next())
	{
		QString type = query.value(0).toString();
		ui.typeComboBox->addItem(type);
	}

}