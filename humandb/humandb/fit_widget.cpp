#include "fit_widget.h"
#include "query.h"
#include <math.h>
#include <QFileDialog>
#include <QThread>
#include "exportFitThread.h"
//#include "fit_widget.moc"

FitWidget::FitWidget(QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);

    //添加X轴参数表
	ui.xTableComboBox->addItem("全部参数", "all");
	ui.xTableComboBox->addItem("基本尺寸", "static");
	ui.xTableComboBox->addItem("功能尺寸", "func");
	ui.xTableComboBox->addItem("关节转角", "joint");
	ui.xTableComboBox->addItem("操作力", "operate");
	ui.xTableComboBox->addItem("运动生理", "sport");
	ui.xTableComboBox->addItem("心理参数", "mental");

    //添加Y轴参数表
	ui.yTableComboBox->addItem("全部参数", "all");
	ui.yTableComboBox->addItem("基本尺寸", "static");
	ui.yTableComboBox->addItem("功能尺寸", "func");
	ui.yTableComboBox->addItem("关节转角", "joint");
	ui.yTableComboBox->addItem("操作力", "operate");
	ui.yTableComboBox->addItem("运动生理", "sport");
	ui.yTableComboBox->addItem("心理参数", "mental");

    //添加X，Y下拉表
	QSqlQuery entryQuery("select itemname, itemnumber from item");
	entryQuery.exec();
	while (entryQuery.next())
	{
        QString itemname = entryQuery.value(0).toString();
		QString itemnumber = entryQuery.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem( itemname );
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		ui.xListWidget->addItem(item);
		ui.yListWidget->addItem(item);
	}


	connect(ui.xListWidget,SIGNAL(itemClicked( QListWidgetItem *)), this, SLOT(onXItemChanged(QListWidgetItem *)) );
	connect(ui.yListWidget,SIGNAL(itemClicked( QListWidgetItem *)), this, SLOT(onYItemChanged(QListWidgetItem *)) );

	ui.rListWidget->setVisible(false);
	
}

FitWidget::~FitWidget()
{

}

void FitWidget::on_xTableComboBox_currentIndexChanged(int ind)
{
	ui.xLabel->clear();//X轴的选项
	QString table = ui.xTableComboBox->itemData( ind ).toString();
	QString group = ui.xTableComboBox->currentText();
	//在itemListWidget上生成测量项目的复选框
	ui.xListWidget->clear();

	QSqlQuery query;
	QString sql = "select itemname,itemnumber from item ";

	if (table != "all")
	{
		sql += "where category = '" + group + "'";
	}

	//qDebug() << "查找参数SQL: " << sql << endl;

	query.exec(sql);

	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem( itemname );
		item->setData(Qt::UserRole, itemnumber);
		ui.xListWidget->addItem(item);
	}
	
    
}

void FitWidget::on_yTableComboBox_currentIndexChanged(int ind)
{
	ui.yLabel->clear();//Y轴的选项
	QString table = ui.yTableComboBox->itemData( ind ).toString();
    QString group = ui.yTableComboBox->currentText();
	//在itemListWidget上生成测量项目的复选框
	ui.yListWidget->clear();

	QSqlQuery query;
	QString sql = "select itemname,itemnumber from item ";

	if (table != "all")
	{
		sql += "where category = '" + group + "'";
	}

	//qDebug() << "查找参数SQL: " << sql << endl;

	query.exec(sql);

	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem( itemname );
		item->setData(Qt::UserRole, itemnumber);
		ui.yListWidget->addItem(item);
	}

}

void FitWidget::onXItemChanged(QListWidgetItem *it)
{	
	QString nameEn = it->data(Qt::UserRole).toString();
	QString nameZh = it->text();
	ui.xLabel->setText(nameZh);
	dbX = nameEn;//dbX赋值
}

void FitWidget::onYItemChanged(QListWidgetItem *it)
{
	currentItem = it;

	QString nameEn = it->data(Qt::UserRole).toString();
	QString nameZh = it->text();
	ui.yLabel->setText(nameZh);
	dbY = nameEn;//dbY赋值
	Query *query = Query::getQuery();

	int npeople = query->get_people_count();
	QString *number = new QString[npeople];
	double *dataX = new double[npeople];
	double *dataY = new double[npeople];
	double *diff = new double[npeople];
	int size = query->select_data(dbX, dbY, dataX, dataY, number);
		
	ui.sizeLabel->setText(QString("总共%1条记录").arg(size));

	/* ############ 使用ChartDirector画出拟合直线 ############ */
	XYChart *c = new XYChart(700, 420);

	c->setPlotArea(55, 50, 550, 320, 0xffffff, -1, 0xc0c0c0, 0xc0c0c0, -1);

	c->addLegend(50, 30, false, "timesbi.ttf", 12)->setBackground(Chart::Transparent);

	c->xAxis()->setTitle(ui.xLabel->text().toUtf8().data(), "simsun.ttc", 10);
	c->yAxis()->setTitle(ui.yLabel->text().toUtf8().data(), "simsun.ttc", 10);

	c->yAxis()->setWidth(1);
	c->xAxis()->setWidth(1);
	//画点
	c->addScatterLayer(DoubleArray(dataX, size), DoubleArray(dataY, size), " ", Chart::GlassSphere2Shape, 2, 0xff0000);
	//画直线
	c->addTrendLayer(DoubleArray(dataX, size), DoubleArray(dataY, size), 0x008000)->setLineWidth(2);

	c->makeChart("fit.png");

	QPixmap pm("fit.png");
	QGraphicsScene *gs = new QGraphicsScene();
	gs->addPixmap(pm);
	ui.graphicsView->setScene(gs);

	/* ############ 最小二乘法拟合曲线 ############ */

	double		a, b, a1, b1, a2, b2, c1, c2, l, s, t, r;
	double		average_x, average_y;

	average_x = average_y = a1 = b1 = a2 = b2 = c1 = c2 = 0;
	for (int i = 0; i < size; i++) {
		a1 += dataX[i]*dataX[i];
		b1 += dataX[i];
		a2 = b1;
		b2++;
		c1 += dataX[i]*dataY[i];
		c2 += dataY[i];
	}
	average_x = b1/size;
	average_y = c2/size;
	//求线性相关系数r，r为负表示负相关，为正表示正相关， r越接近1或者-1，则线性关系越明显
	l = s = t = 0;
	for (i = 0; i < size; i++) {
		l += (dataX[i]-average_x) * (dataY[i]-average_y);
		s += (dataX[i]-average_x)*(dataX[i]-average_x);
		t += (dataY[i]-average_y)*(dataY[i]-average_y);
	}
	r = l/sqrt(s*t);

	//计算直线方程的参数
	a =( b2*c1-c2*b1)/(a1*b2-a2*b1);
	b =( a1*c2-a2*c1)/(a1*b2-a2*b1);

	QString labelStr;
	if (b > 0) {
		labelStr = QString("线性相关系数为 r = <font color=red>%1</font>, 回归方程为 Y = <font color=red>%2</font>X<font color=red>+%3</font>").arg(r).arg(a).arg(b);
	} else {
		labelStr = QString("线性相关系数为 r = <font color=red>%1</font>, 回归方程为 Y = <font color=red>%2</font>X<font color=red>%3</font>").arg(r).arg(a).arg(b);
	}
	ui.label->setText(labelStr);
	ui.lineEdit->setText(QString("r = %1").arg(r));
	ui.aLineEdit->setText(QString("k = %1").arg(a));
	ui.bLineEdit->setText(QString("b = %1").arg(b));

	for (i = 0; i < size; i++) 
	{// 使用插入法从小到大对误差排序 
		double difference = a*dataX[i]+b-dataY[i] ;
		QString num = number[i];
		double  y = dataY[i];
		if (difference < 0) difference = difference*(-1);
		for (int j = i-1; j >= 0 && diff[j] > difference; j--) {
			diff[j+1] = diff[j];
			number[j+1] = number[j];
			dataY[j+1] = dataY[j];
		}
		diff[j+1] = difference;
		number[j+1] = num;
		dataY[j+1] = y;
	}

	ui.rListWidget->clear();
	ui.rListWidget->addItem("编号\t测量值\t偏离程度(mm)");
	for (i = 0; i < size; i++) {
		//qDebug() << number[i] << dataY[i] << " " << diff[i] ;
		QListWidgetItem *item = new QListWidgetItem( number[i]+QString("\t%1\t").arg(dataY[i])+QString::number(diff[i], 'g', 5) );
		item->setData(Qt::UserRole, nameEn);
		item->setCheckState(Qt::Unchecked);
		ui.rListWidget->addItem(item);
	}

	/* ############ 最小二乘法拟合曲线结束 ############ */

	delete c;
	delete dataX;
	delete dataY;
	//delete number;
	delete diff;
}

/* 删除用户选中的数据， 只需把该数据的值置为0或者-1即可 */
void FitWidget::on_deleteButton_clicked()
{
	/*if ( QGlobalVar::userType == 2 )
	{
		QMessageBox::warning(this, "提示", "操作受限！", QMessageBox::Ok);
		return;
	}*/
	QListWidgetItem * item;
	QString nameDb, nameZh, number;
	QString sql;
	QSqlQuery query;
	QList<int> deleteRows;
	QString table = ui.yTableComboBox->itemData( ui.yTableComboBox->currentIndex() ).toString();

	for (int i = 0; i < ui.rListWidget->count(); i++) {
		item = ui.rListWidget->item(i);
		if ( item->checkState() == Qt::Checked ) {
			deviationList << item->text();
			number = item->text().split("\t")[0];	
			nameDb = item->data(Qt::UserRole).toString();	/* 测量项目数据库字段名 */
			sql = "update " + table + " set " + nameDb + "= 9999 where number = '" + number + "'";
			if (query.exec(sql)) {
				int row = ui.rListWidget->row(item);
				deleteRows << row;
			}
		}
	}
	for (int i = 0; i < deleteRows.size(); i++) {
		ui.rListWidget->takeItem(deleteRows[i]);
	}
	onYItemChanged(currentItem);
}

void FitWidget::on_selectButton_clicked()
{
    QString dirName=QFileDialog::getExistingDirectory(this,tr("选择目录"),"D:\\");
	//ui.DirLineEdit->setText(dirName);
	QString timeStr=QDateTime::currentDateTime().toString("yyyy-MM-dd");
	//ui.nameLineEdit->setText(timeStr+"偏离信息导出文件.xls");
}

void FitWidget::on_exportButton_clicked()
{
	/*if ( QGlobalVar::userType == 2 )
	{
		QMessageBox::warning(this, "提示", "操作受限！", QMessageBox::Ok);
		return;
	}*/
	/*QListWidgetItem * item;
	for (int i = 0; i < ui.rListWidget->count(); i++) 
	{
		item = ui.rListWidget->item(i);
		if ( item->checkState() == Qt::Checked ) 
		{
			deviationList << item->text();
			
		}
	}


    QString filePath="";
	filePath=ui.DirLineEdit->text()+"/"+ui.nameLineEdit->text();
	ExportFitThread *exportFitThread=new ExportFitThread(filePath, deviationList, this);
	connect(exportFitThread, SIGNAL(completedCount(int)), ui.progressBar, SLOT(setValue(int)));
	exportFitThread->start();

	QMessageBox::warning(this, "提示", QString("共导出%1条记录").arg(deviationList.size()), QMessageBox::Ok);*/
}