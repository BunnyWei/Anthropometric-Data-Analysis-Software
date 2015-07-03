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

	ui.groupComboBox->addItem("ȫ������", "all");
	ui.groupComboBox->addItem("�����ߴ�", "static");
	ui.groupComboBox->addItem("���ܳߴ�", "func");
	ui.groupComboBox->addItem("�ؽ�ת��", "joint");
	ui.groupComboBox->addItem("������", "operate");
	ui.groupComboBox->addItem("�˶�����", "sport");
	ui.groupComboBox->addItem("�������", "mental");
	
	ui.bingzhongComboBox->addItem("ȫ��");
	ui.bingzhongComboBox->addItem("������");
	ui.bingzhongComboBox->addItem("װ�ױ�");
	ui.bingzhongComboBox->addItem("���̱�");
	ui.bingzhongComboBox->addItem("�ڱ�");
	ui.bingzhongComboBox->addItem("����");


	ui.districtComboBox->addItem("ȫ��");
	ui.districtComboBox->addItem("������");
	ui.districtComboBox->addItem("������");
	ui.districtComboBox->addItem("������");
	ui.districtComboBox->addItem("������");
	ui.districtComboBox->addItem("������");
	ui.districtComboBox->addItem("������");
	ui.districtComboBox->addItem("������");

	ui.wenhuaComboBox->addItem("ȫ��");
	ui.wenhuaComboBox->addItem("Сѧ");
	ui.wenhuaComboBox->addItem("����");
	ui.wenhuaComboBox->addItem("����");
	ui.wenhuaComboBox->addItem("��ר");
	ui.wenhuaComboBox->addItem("��ר");
	ui.wenhuaComboBox->addItem("����");
	ui.wenhuaComboBox->addItem("˶ʿ");
	ui.wenhuaComboBox->addItem("��ʿ");

	ui.jiguanComboBox->addItem("ȫ��");
	QSqlQuery query("select Province from province order by Province asc");
	query.exec();
	while (query.next()) {
		ui.jiguanComboBox->addItem( query.value(0).toString() );
	}

	ui.junxianComboBox->addItem("ȫ��");
	ui.junxianComboBox->addItem("�б�");
	ui.junxianComboBox->addItem("�ϵȱ�");
	ui.junxianComboBox->addItem("��ʿ");
	ui.junxianComboBox->addItem("��ʿ");
	ui.junxianComboBox->addItem("��ʿ");
	ui.junxianComboBox->addItem("�ļ���ʿ��");
	//ui.junxianComboBox->addItem("�弶ʿ��");
	//ui.junxianComboBox->addItem("����ʿ��");
	ui.junxianComboBox->addItem("��ξ");
	ui.junxianComboBox->addItem("��ξ");
	ui.junxianComboBox->addItem("��ξ");
	ui.junxianComboBox->addItem("��У");
	ui.junxianComboBox->addItem("��У");
    //����Զ���ٷ�λ
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

	tableHeader.append("��������"); 
	tableHeader.append("��Сֵ"); 
	tableHeader.append("���ֵ"); 
	tableHeader.append("ƽ��ֵ"); 
	
	tableHeader.append("��׼��"); 
	tableHeader.append("P5");
	tableHeader.append("P50"); 
	tableHeader.append("P95"); 
	tableHeader.append("�Զ���ٷ�λ"); 
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
	ui.fileNameLineEdit->setText(QString("���������ļ�") + dateStr + ".xls");

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

//ɸѡ�����ȵô�info����ѡ�����������ľ��˱��
void StatWidget::getFilter()
{
	this->filterSql = "";
	this->filter = "";
	QString jiguan = ui.jiguanComboBox->currentText();
	QString district = ui.districtComboBox->currentText();
	QString bingzhong = ui.bingzhongComboBox->currentText();
	QString wenhua = ui.wenhuaComboBox->currentText();
	QString junxian = ui.junxianComboBox->currentText();

    if ("ȫ��" != district) {	/* �е������ */
		filter += " and region='" + district + "'";
	}
	if ("ȫ��" != junxian) {	/* �о��β��� */
		filter += " and junxian='" + junxian + "'";
	}
	if ("ȫ��" != bingzhong) {	/* �б��ֲ��� */
		filter += " and bingzhong='" + bingzhong + "'";
	}
	if ("ȫ��" != jiguan) {	/* �м������ */
		filter += " and jiguan like '" + jiguan + "%'";
	}
	if("ȫ��" != wenhua){ /*��ѧ������*/
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
* �����������Ĳ�����Ŀ��ӵ��б�
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
	// if ("ȫ��" == district) {	/* �е������ */
	//	district="";
	//}
	//if ("ȫ��" == junxian) {	/* �о��β��� */
	//	junxian="";
	//}
	//if ("ȫ��" == bingzhong) {	/* �б��ֲ��� */
	//	bingzhong="";
	//}
	//if ("ȫ��" == jiguan) {	/* �м������ */
	//	jiguan="";
	//}
	//if("ȫ��" == wenhua){ /*��ѧ������*/
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
void StatWidget::on_okButton_clicked()//ȷ��
{
	//getFilter();
	ui.listWidget->clear();
	QString todayStr = QDateTime::currentDateTime().toString("yyyy-MM-dd");
	QString fileName =ui.groupComboBox->currentText() +"ͳ�Ʒ���"+ todayStr + ".xls";
	ui.fileNameLineEdit->setText(fileName);

	QString groupStr = ui.groupComboBox->currentText();
	QString typeStr = ui.typeComboBox->currentText();

	QSqlQuery query;
	QString sql = "select itemname,itemnumber from item ";

	if (groupStr != "ȫ������")
	{
		if (typeStr != "ȫ��")
		{
			sql += "where category = '" + groupStr + "' and posture = '" + typeStr + "'";
		}
		else
		{
			sql += "where category = '" + groupStr + "'";
		}
	}

	//qDebug() << "���Ҳ���SQL: " << sql << endl;

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
	
	QString customPercentile = "P" + ui.percentileComboBox->currentText();//�Զ���ٷ�λ
	tableHeader.removeAt(8);
	tableHeader.append(customPercentile);//ʹ�Զ����ͷ��ʾ�û�ѡ��ٷ�λ
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader); //����б���
	int per = customPercentile.remove('P').toInt();
	float percent = (float)per/100;
	
    QListWidgetItem * item;//�����б���
	QString itemname,nameDb;//��������
	//����
//	QLable  countpeople;
	int index = 0;	/* ������Ŀ�ڱ���е��к� */

	Query *query = Query::getQuery();
	Stat stat;
	QString jiguan = ui.jiguanComboBox->currentText();
	if ("ȫ��" == jiguan)
	{
		jiguan = "";
	}
	QString district = ui.districtComboBox->currentText();
	if ("ȫ��" == district)
	{
		district = "";
	}
	QString bingzhong = ui.bingzhongComboBox->currentText();
	if ("ȫ��" == bingzhong)
	{
		bingzhong = "";
	}
	QString wenhua = ui.wenhuaComboBox->currentText();
	if ("ȫ��" == wenhua)
	{
		wenhua = "";
	}
	QString junxian = ui.junxianComboBox->currentText();
	if ("ȫ��" == junxian)
	{
		junxian = "";
	}
	//QLable countpeople=query->get_people_count;//

	//����������Ŀ�б������ѡ�У���ͳ����������ͳ�ƽ����ʾ�ڱ��
	//query_data(Stat &stat, QString item, QString nativeplace, 
					  // QString district, QString armtype, QString education, QString militaryrank)
	int selectedItem=0;
	for (int i = 0; i < ui.listWidget->count(); i++) 
	{
		item = ui.listWidget->item(i);
		if ( item->checkState() == Qt::Checked ) 
		{
			itemname = item->text();	/* ������Ŀ������ */
			nameDb = item->data(Qt::UserRole).toString();	/* ������Ŀ���ݿ��ֶ��� */
			selectedItem+=1;
			 ui.tableWidget->setRowCount(selectedItem);
	    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
		}
		else
		{
			continue;
		}

		QTableWidgetItem *itt = new QTableWidgetItem(itemname);
		ui.tableWidget->setItem(index, 0, itt);		/* ������Ŀ���� */
       
	  
		query->query_data(stat, nameDb, jiguan, district, bingzhong, wenhua, junxian);
		

		/*qDebug() << "��Сֵ��" << stat.stat_min() <<endl;
		qDebug() << "ƽ��ֵ��" << stat.stat_avg() <<endl;
		qDebug() << "���ֵ��" << stat.stat_max() <<endl;
		qDebug() << "��׼�" << stat.stat_std() <<endl;
		qDebug() << "5%��" << stat.percentile(0.05) <<endl;
		qDebug() << "50%��" << stat.percentile(0.5) <<endl;
		qDebug() << "95%��" << stat.percentile(0.95) <<endl;
		qDebug() << "�Զ���ٷ�λ��" << stat.percentile(percent) <<endl;*/

		if (-1 == stat.stat_min() && -1 == stat.stat_avg() && -1 == stat.stat_std())
		{
			ui.tableWidget->setItem(selectedItem-1, 1, new QTableWidgetItem(""));	/* ��Сֵ */
			ui.tableWidget->setItem(selectedItem-1, 2, new QTableWidgetItem(""));	/* ƽ��ֵ */
			ui.tableWidget->setItem(selectedItem-1, 3, new QTableWidgetItem(""));	/* ���ֵ */
			ui.tableWidget->setItem(selectedItem-1, 4, new QTableWidgetItem(""));	/* %5��λ */
			ui.tableWidget->setItem(selectedItem-1, 5, new QTableWidgetItem(""));	/* %50��λ */
			ui.tableWidget->setItem(selectedItem-1, 6, new QTableWidgetItem(""));	/* %95��λ */
			ui.tableWidget->setItem(selectedItem-1, 7, new QTableWidgetItem(""));	/* ��׼�� */
			ui.tableWidget->setItem(selectedItem-1, 8, new QTableWidgetItem(""));	/* ��׼�� */
		}
		else
		{
			//�õ�tableֵ���ж����precise�е��ֶ��Ƿ���ͬ
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
			ui.tableWidget->setItem(selectedItem-1, 1, new QTableWidgetItem(D2S(stat.stat_min(), table, MIN)));	/* ��Сֵ */
			ui.tableWidget->setItem(selectedItem-1, 2, new QTableWidgetItem(D2S(stat.stat_max(), table, MAX)));	/* ���ֵ */
			ui.tableWidget->setItem(selectedItem-1, 3, new QTableWidgetItem(D2S(stat.stat_avg(), table, AVG)));	/* ƽ��ֵ */
			ui.tableWidget->setItem(selectedItem-1, 4, new QTableWidgetItem(D2S(stat.stat_std(), table, STD)));	/* ��׼�� */
			
			ui.tableWidget->setItem(selectedItem-1, 5, new QTableWidgetItem(D2S(stat.percentile(0.05), table, PER)));	/* %5��λ */
			ui.tableWidget->setItem(selectedItem-1, 6, new QTableWidgetItem(D2S(stat.percentile(0.5), table, PER)));	/* %50��λ */
			ui.tableWidget->setItem(selectedItem-1, 7, new QTableWidgetItem(D2S(stat.percentile(0.95), table, PER)));	/* %95��λ */
			if (percent < 0.0000001){
				ui.tableWidget->setItem(selectedItem-1, 8, new QTableWidgetItem(""));
			}
			else{
				ui.tableWidget->setItem(selectedItem-1, 8, new QTableWidgetItem(D2S(stat.percentile(percent), table, PER)));	/* ��׼�� */
			}
		}
		index++;
	}
	 QString label = QString::number(getcount()) + "����¼";
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
	tableHeader.append(percentile);//ʹ�Զ����ͷ��ʾ�û�ѡ��ٷ�λ
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader); //����б���
	QString filter = "";

	QListWidgetItem * item;//�����б���
	QString itemname,nameDb;//��������
	QSqlQuery query, query2;
	QString sql, sql2;	/* sql���������ֵ����Сֵ������ȣ�sql2������ٷ�λ */
	QString group;
	QString table; //���Ҷ�Ӧ�ı�
	float variance;//����
	int index = 0;	/* ������Ŀ�ڱ���е��к� */

	group = ui.groupComboBox->itemData( ui.groupComboBox->currentIndex(), Qt::UserRole ).toString();
	//����������Ŀ�б������ѡ�У���ͳ����������ͳ�ƽ����ʾ�ڱ��
	for (int i = 0; i < ui.listWidget->count(); i++) {
		item = ui.listWidget->item(i);
		if ( item->checkState() == Qt::Checked ) {
			itemname = item->text();	/* ������Ŀ������ */
			nameDb = item->data(Qt::UserRole).toString();	/* ������Ŀ���ݿ��ֶ��� */
#if 1
            //���ݴ����ҵ��ֶ�������Ҫ���ҵı���
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

			//��������Ҫ���˵�����ֵΪ-1�ļ�¼���������ݺ�ͷ������Ҫ���˵�����ֵΪ0�ļ�¼
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
		ui.tableWidget->setItem(index, 0, itt);		/* ������Ŀ���� */
		
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
			ui.tableWidget->setItem(index, 1, new QTableWidgetItem(D2S(minV)));	/* ��Сֵ */
			ui.tableWidget->setItem(index, 2, new QTableWidgetItem(D2S(avgV)));	/* ƽ��ֵ */		
			ui.tableWidget->setItem(index, 3, new QTableWidgetItem(D2S(maxV)));	/* ���ֵ */
			variance = query.value(3).toString().toFloat();
			QTableWidgetItem *it = new QTableWidgetItem( D2S(variance ));
			ui.tableWidget->setItem(index, 4, it);	/* ��׼�� */

			//�ٷ�λ
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

			//5%��λ
			i0 = floor(r);
			i1 = ceil(r);
			query2.seek(i0);
			value_i0 = query2.value(0).toDouble();
			query2.next();
			value_i1 = query2.value(0).toDouble();
			result = (i0 == i1) ? value_i0 : value_i0 * (i1 - r) + value_i1 * (r - i0);
			ui.tableWidget->setItem(index, 5, new QTableWidgetItem( D2S(result)));
			//50%��λ
			i0 = (int) floor(s);
			i1 = (int) ceil(s);
			query2.seek(i0);
			value_i0 = query2.value(0).toDouble();
			query2.next();
			value_i1 = query2.value(0).toDouble();
			result = (i0 == i1) ? value_i0 : value_i0 * (i1 - s) + value_i1 * (s - i0);
			ui.tableWidget->setItem(index, 6, new QTableWidgetItem( D2S(result) ));
			//95%��λ
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
			//�Զ���ٷ�λ
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
		//Ϊÿһ���ֶν���Ψһ����
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
	QString dirName = QFileDialog::getExistingDirectory(this, tr("ѡ��Ŀ¼"), "C:\\");
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
	ui.showLabel->setText(tr("�����ɹ���"));
}

void StatWidget::on_groupComboBox_currentIndexChanged(int index)
{
	QString group = ui.groupComboBox->itemData(index, Qt::UserRole).toString();
	QString tableName = ui.groupComboBox->currentText();

	if ("ȫ������" == tableName)
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("ȫ��");
		return;
	}
	QSqlQuery query;
	QString sql = "select distinct posture from item where category = '";
	sql += tableName + "'";
	query.exec(sql);
	ui.typeComboBox->clear();
	ui.typeComboBox->addItem("ȫ��");

	while (query.next())
	{
		QString type = query.value(0).toString();
		ui.typeComboBox->addItem(type);
	}

}