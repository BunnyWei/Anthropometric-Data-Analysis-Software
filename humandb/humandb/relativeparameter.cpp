#include "relativeparameter.h"
#include "query.h"
#include "statistic.h"

RelativeParameter::RelativeParameter(QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);

	ui.groupComboBox->addItem("ȫ������", "all");
	ui.groupComboBox->addItem("�����ߴ�", "static");
	ui.groupComboBox->addItem("�ؽ�ת��", "joint");
	ui.groupComboBox->addItem("���ܳߴ�", "func");
	ui.groupComboBox->addItem("������", "operate");
	ui.groupComboBox->addItem("�˶�����", "sport");
	ui.groupComboBox->addItem("�������", "mental");

	ui.typeComboBox->addItem("����Χ��ѯ", "scope");
	ui.typeComboBox->addItem("���ٷ�λ��ѯ", "percentile");

	ui.tableComboBox->addItem("ȫ������", "all");
	ui.tableComboBox->addItem("�����ߴ�", "static");
	ui.tableComboBox->addItem("�ؽ�ת��", "joint");
	ui.tableComboBox->addItem("���ܳߴ�", "func");
	ui.tableComboBox->addItem("������", "operate");
	ui.tableComboBox->addItem("�˶�����", "sport");
	ui.tableComboBox->addItem("�������", "mental");


	ui.tableWidget->setColumnCount(8);
	ui.tableWidget->setRowCount(400);
	for (int i = 1; i < 8; i++) {
		ui.tableWidget->setColumnWidth(i, 80);
	}
	for (int i = 0; i < 400; i++) {
		ui.tableWidget->setRowHeight(i, 30);
	}

	tableHeader.append("ͳ����"); 
	tableHeader.append("��Сֵ"); 
	tableHeader.append("���ֵ"); 
	tableHeader.append("ƽ��ֵ"); 
    tableHeader.append("��׼��"); 
	tableHeader.append("5%");
	tableHeader.append("50%"); 
	tableHeader.append("95%"); 
	
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader);

	searchType = 0;//��ѯ����

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

RelativeParameter::~RelativeParameter()
{

}


void RelativeParameter::on_groupComboBox_currentIndexChanged(int index)
{
	ui.parameterComboBox->clear();

	QString groupStr = ui.groupComboBox->currentText();

	QSqlQuery query;
	QString sql = "select itemname,itemnumber from item ";

	if (groupStr != "ȫ������")
	{
		sql += "where category = '" + groupStr + "'";
	}

	query.exec(sql);

	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		ui.parameterComboBox->addItem(itemname, itemnumber);
	}

}

void RelativeParameter::on_typeComboBox_currentIndexChanged(int index)
{
	QString mysetwhere = ui.typeComboBox->currentText();

	if ("���ٷ�λ��ѯ" == mysetwhere)
	{
		ui.minLineEdit->setEnabled(false);
		ui.maxLineEdit->setEnabled(false);
		ui.centileLineEdit->setEnabled(true);
		searchType = 1;
	}
	else
	{
		ui.centileLineEdit->setEnabled(false);
		ui.minLineEdit->setEnabled(true);
		ui.maxLineEdit->setEnabled(true);
		searchType = 2;
	}

}

void RelativeParameter::on_tableComboBox_currentIndexChanged(int index)
{
	ui.listWidget->clear();
	QString groupStr = ui.tableComboBox->currentText();
	QString groupIndex = ui.tableComboBox->itemData(index, Qt::UserRole).toString();

	QSqlQuery query;
	QString sql = "select itemname,itemnumber from item ";

	if (groupIndex != "all")
	{
		sql += "where category = '" + groupStr + "'";
	}

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

void RelativeParameter::on_staBtn_clicked()
{
	Stat stat;
	QListWidgetItem *item;
	int ind = ui.parameterComboBox->currentIndex();
	QString other = ui.parameterComboBox->itemData(ind, Qt::UserRole).toString();
	float min = ui.minLineEdit->text().toFloat();
	float max = ui.maxLineEdit->text().toFloat();
	Query *query = Query::getQuery();

	if (searchType == 1)
	{
		float percent = ui.centileLineEdit->text().toFloat();
		if (percent > 1.0)
		{
			percent = percent/100;
		}	
		Stat perStat;
		query->query_data(perStat, other, "", "", "", "", "");
		double percentile = perStat.percentile(percent);
		min = 0;
		max = static_cast<float>(percentile);
	}


	ui.tableWidget->clear();
	ui.tableWidget->setHorizontalHeaderLabels(tableHeader); 

	int row = 0;
	int selectedItem=0;
	for (int i = 0; i < ui.listWidget->count(); i++) 
	{
		item = ui.listWidget->item(i);
		if ( item->checkState() == Qt::Checked ) 
		{
			QString itemname = item->text();	/* ������Ŀ������ */
			QString itemnumber = item->data(Qt::UserRole).toString();	/* ������Ŀ���ݿ��ֶ��� */
			query->query_data_by_others(stat, itemnumber, other, min, max);
			
			ui.tableWidget->setRowCount(row+1);
			ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
			ui.tableWidget->setItem(row, 0, new QTableWidgetItem(itemname));	/* �������� */

			if (stat.stat_min() == -1 && stat.stat_max() == -1)
			{
				ui.tableWidget->setItem(row, 1, new QTableWidgetItem(""));	/* ��Сֵ */
				ui.tableWidget->setItem(row, 2, new QTableWidgetItem(""));	/* ƽ��ֵ */
				ui.tableWidget->setItem(row, 3, new QTableWidgetItem(""));	/* ���ֵ */
				ui.tableWidget->setItem(row, 4, new QTableWidgetItem(""));	/* %5��λ */
				ui.tableWidget->setItem(row, 5, new QTableWidgetItem(""));	/* %50��λ */
				ui.tableWidget->setItem(row, 6, new QTableWidgetItem(""));	/* %95��λ */
				ui.tableWidget->setItem(row, 7, new QTableWidgetItem(""));	/* ��׼�� */
			}
			else
			{
				//�õ�tableֵ���ж����precise�е��ֶ��Ƿ���ͬ
				QString table;
				if (itemnumber.startsWith("hand")) {
					table = "STATIC";
				} else if (itemnumber.startsWith("h")) {
					table= "STATIC";
				} else if (itemnumber.startsWith("f")) {
					table = "FUNC";
				} else if (itemnumber.startsWith("o")) {
					table = "OPERATE";
				} else if (itemnumber.startsWith("st")) {
					table = "STATIC";
				} else if (itemnumber.startsWith("s"))  {
					table = "SPORT";
				} else if (itemnumber.startsWith("j")) {
					table = "JOINT";
				} else if (itemnumber.startsWith("m")) {
					table = "MENTAL";
				}
				table=table.toLower();
				ui.tableWidget->setItem(row, 1, new QTableWidgetItem(D2S(stat.stat_min(), table, MIN)));	/* ��Сֵ */				
				ui.tableWidget->setItem(row, 2, new QTableWidgetItem(D2S(stat.stat_max(), table, MAX)));	/* ���ֵ */
				ui.tableWidget->setItem(row, 3, new QTableWidgetItem(D2S(stat.stat_avg(), table, AVG)));	/* ƽ��ֵ */
				ui.tableWidget->setItem(row, 4, new QTableWidgetItem(D2S(stat.stat_std(), table, STD)));	/* ��׼�� */
				ui.tableWidget->setItem(row, 5, new QTableWidgetItem(D2S(stat.percentile(0.05), table, PER)));	/* %5��λ */
				ui.tableWidget->setItem(row, 6, new QTableWidgetItem(D2S(stat.percentile(0.5), table, PER)));	/* %50��λ */
				ui.tableWidget->setItem(row, 7, new QTableWidgetItem(D2S(stat.percentile(0.95), table, PER)));	/* %95��λ */				
			}
			row++;
		}
	}	
}

const QString  RelativeParameter::D2S(double data, QString table, enum enum_staType type) //double to string
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
void RelativeParameter::on_listWidget_clicked(const QModelIndex &)
{

}

void RelativeParameter::on_typeComboBox_textChanged(const QString &)
{

}