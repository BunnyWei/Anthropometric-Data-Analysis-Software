#include "customparameter.h"
#include "query.h"
CustomParameter::CustomParameter(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.paraComboBox1->addItem("全部参数", "all");
	ui.paraComboBox1->addItem("基本尺寸", "static");
	ui.paraComboBox1->addItem("功能尺寸", "func");
	ui.paraComboBox1->addItem("关节转角", "joint");
	ui.paraComboBox1->addItem("操作力", "operate");
	ui.paraComboBox1->addItem("运动生理", "sport");
	ui.paraComboBox1->addItem("心理参数", "mental");

	ui.paraComboBox2->addItem("全部参数", "all");
	ui.paraComboBox2->addItem("基本尺寸", "static");
	ui.paraComboBox2->addItem("功能尺寸", "func");
	ui.paraComboBox2->addItem("关节转角", "joint");
	ui.paraComboBox2->addItem("操作力", "operate");
	ui.paraComboBox2->addItem("运动生理", "sport");
	ui.paraComboBox2->addItem("心理参数", "mental");

	ui.paraComboBox3->addItem("全部参数", "all");
	ui.paraComboBox3->addItem("基本尺寸", "static");
	ui.paraComboBox3->addItem("功能尺寸", "func");
	ui.paraComboBox3->addItem("关节转角", "joint");
	ui.paraComboBox3->addItem("操作力", "operate");
	ui.paraComboBox3->addItem("运动生理", "sport");
	ui.paraComboBox3->addItem("心理参数", "mental");

	ui.groupComboBox->addItem("基本尺寸", "static");
	ui.groupComboBox->addItem("功能尺寸", "func");
	ui.groupComboBox->addItem("关节转角", "joint");
	ui.groupComboBox->addItem("操作力", "operate");
	ui.groupComboBox->addItem("运动生理", "sport");
	ui.groupComboBox->addItem("心理参数", "mental");

	ui.bodyComboBox->addItem("头颈部");
	ui.bodyComboBox->addItem("上肢部+肩关节");
	ui.bodyComboBox->addItem("手部+腕部");
	ui.bodyComboBox->addItem("躯干部");
	ui.bodyComboBox->addItem("下肢部");
	ui.bodyComboBox->addItem("足部+踝关节");
	ui.bodyComboBox->addItem("全身段");

    //添加运算符
	ui.operateComboBox1->addItem("+","add");
	ui.operateComboBox1->addItem("-","decrease");
	ui.operateComboBox1->addItem("*","multiply");
	ui.operateComboBox1->addItem("/","division");
    //添加运算符
	ui.operateComboBox2->addItem("+","add");
	ui.operateComboBox2->addItem("-","decrease");
	ui.operateComboBox2->addItem("*","multiply");
	ui.operateComboBox2->addItem("/","division");

	ui.paraCountComboBox->addItem("2个参数", "2");
	ui.paraCountComboBox->addItem("3个参数", "3");


}

CustomParameter::~CustomParameter()
{

}


void CustomParameter::on_groupComboBox_currentIndexChanged(int index)
{
#if 0
	QString group = ui.groupComboBox->itemData(index, Qt::UserRole).toString();

	if (group == "static")
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("头部参数");
		ui.typeComboBox->addItem("手部参数");
		ui.typeComboBox->addItem("足部参数");
		ui.typeComboBox->addItem("立姿参数");
		ui.typeComboBox->addItem("坐姿参数");
	}
	else if (group == "func")
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("坐姿参数");
		ui.typeComboBox->addItem("姿态修正量");
		ui.typeComboBox->addItem("手足部参数");
		ui.typeComboBox->addItem("立姿参数");
		ui.typeComboBox->addItem("特殊姿态尺寸");
		ui.typeComboBox->addItem("服装修正量");
	}
	else if (group == "joint")
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("未分类");
	}
	else if (group == "operate")
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("左手力量");
		ui.typeComboBox->addItem("右手力量");
		ui.typeComboBox->addItem("脚蹬力");
		ui.typeComboBox->addItem("右手旋力");
		ui.typeComboBox->addItem("食指指拨力");
		ui.typeComboBox->addItem("背力");
	}
	else if (group == "sport")
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("未分类");
	}
	else if (group == "mental")
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("未分类");
	}
	else if (group == "all")
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("未分类");
	}
#endif

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

void CustomParameter::on_paraComboBox1_currentIndexChanged(int index)
{
	ui.listWidget1->clear();
	QString table = ui.paraComboBox1->itemData(index, Qt::UserRole).toString();
	QString group = ui.paraComboBox1->currentText();

	QSqlQuery query;
	QString sql = "select itemname,itemnumber from item ";

	if (table != "all")
	{
		sql += "where category = '" + group + "'";
	}

	//qDebug() << "查找参数SQL: " << sql;

	query.exec(sql);

	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem( itemname );
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		ui.listWidget1->addItem(item);
		//QRadioButton *rBtn = new QRadioButton("");
		//ui.listWidget1->setItemWidget(item, rBtn);
	}
}

void CustomParameter::on_paraComboBox2_currentIndexChanged(int index)
{
    ui.listWidget2->clear();
	QString table = ui.paraComboBox2->itemData(index, Qt::UserRole).toString();
	QString group = ui.paraComboBox2->currentText();

	QSqlQuery query;
	QString sql = "select itemname,itemnumber from item ";

	if (table != "all")
	{
		sql += "where category = '" + group + "'";
	}

	//qDebug() << "查找参数SQL: " << sql;

	query.exec(sql);

	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem( itemname );
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		ui.listWidget2->addItem(item);
	}
}

void CustomParameter::on_paraComboBox3_currentIndexChanged(int index)
{
    ui.listWidget3->clear();
	QString table = ui.paraComboBox3->itemData(index, Qt::UserRole).toString();
	QString group = ui.paraComboBox3->currentText();

	QSqlQuery query;
	QString sql = "select itemname,itemnumber from item ";

	if (table != "all")
	{
		sql += "where category = '" + group + "'";
	}

	//qDebug() << "查找参数SQL: " << sql;

	query.exec(sql);

	while (query.next())
	{
		QString itemname = query.value(0).toString();
		QString itemnumber = query.value(1).toString();
		QListWidgetItem *item = new QListWidgetItem( itemname );
		item->setData(Qt::UserRole, itemnumber);
		item->setCheckState(Qt::Unchecked);
		ui.listWidget3->addItem(item);
	}
}
//得到用户选择字段
void CustomParameter::getSelectedDBName()
{
	QListWidgetItem * item;//下拉列表项
	QString itemname,nameDb;//测量参数
	int count = 0;
	
	for (int i = 0; i < ui.listWidget1->count(); i++) 
	{
		item = ui.listWidget1->item(i);
		if ( item->checkState() == Qt::Checked ) 
		{
			itemname = item->text();	/* 测量项目中文名 */
			dbName1 = item->data(Qt::UserRole).toString();	/* 测量项目数据库字段名 */
			table1 = getTable(dbName1);
		}
	}
		
	for (int i = 0; i < ui.listWidget2->count(); i++) 
	{
		item = ui.listWidget2->item(i);
		if ( item->checkState() == Qt::Checked ) 
		{
			itemname = item->text();	/* 测量项目中文名 */
			dbName2 = item->data(Qt::UserRole).toString();	/* 测量项目数据库字段名 */
			table2 = getTable(dbName2);
		}
	}
	
	for (int i = 0; i < ui.listWidget3->count(); i++) 
	{
		item = ui.listWidget3->item(i);
		if ( item->checkState() == Qt::Checked ) 
		{
			itemname = item->text();	/* 测量项目中文名 */
			dbName3 = item->data(Qt::UserRole).toString();	/* 测量项目数据库字段名 */
			table3 = getTable(dbName3);
		}
	}
	
}

inline QString CustomParameter::getTable(QString  attribute)
{//判断某个属性属于哪个表
	QString table = "";
	if (attribute.startsWith("hand")) 
	{
		table = "hand";
	} 
	else if (attribute.startsWith("h")) 
	{
		table = "head";
	} 
	else if (attribute.startsWith("f")) 
	{
		table = "func";
	} 
	else if (attribute.startsWith("o")) 
	{
		table = "operate";
	} 
	else if (attribute.startsWith("st")) 
	{
		table = "static";
	} 
	else if (attribute.startsWith("s")) 
	{
		table = "sport";
	} 
	else if (attribute.startsWith("j")) 
	{
		table = "joint";
	} 
	else if (attribute.startsWith("m")) 
	{
		table = "mental";
	} 
	else 
	{
		table = "";
	}
	return table;
}


void CustomParameter::on_paraCountComboBox_currentIndexChanged(int index)
{
	QString countStr = ui.paraCountComboBox->itemData(index, Qt::UserRole).toString();

	if (countStr == "2")
	{
		ui.paraComboBox3->setVisible(false);
		ui.operateComboBox2->setVisible(false);
		ui.listWidget3->setVisible(false);
	}
	else if (countStr == "3")
	{
		ui.paraComboBox3->setVisible(true);
		ui.operateComboBox2->setVisible(true);
		ui.listWidget3->setVisible(true);
	}
}

QString CustomParameter::defItemNumber(QString table)
{
    QSqlQuery query;
	QString sql = "select count(itemnumber) from item where category = '" + table + "'";
	query.exec(sql);
	query.next();
	int num = query.value(0).toInt();
	
	QString itemnumber;
	if (table == "基本尺寸") 
	{
		itemnumber = QString("st%1").arg(num+2);
	} 
	else if (table == "功能尺寸") 
	{
		itemnumber = QString("fa%1").arg(num+2);
	} 
	else if (table == "关节转角") 
	{
		itemnumber = QString("j%1").arg(num+2);
	} 
	else if (table == "操作力") 
	{
		itemnumber = QString("o%1").arg(num+2);
	} 
	else if (table == "运动生理") 
	{
		itemnumber = QString("s%1").arg(num+2);
	} 
	else if (table == "心理参数") 
	{
		itemnumber = QString("ma%1").arg(num+2);
	} 
	
	return itemnumber;

}

void CustomParameter::on_addBtn_clicked()
{
	getSelectedDBName();//取得所选参数
	QString itemname = ui.lineEdit->text();
	QString groupStr = ui.groupComboBox->currentText();
	QString table = ui.groupComboBox->itemData( ui.groupComboBox->currentIndex() ).toString();
	QString typeStr = ui.typeComboBox->currentText();
	if (typeStr == "全部") typeStr = "";
	QString definition = ui.defLineEdit->text();
	QString measureStr = ui.measureLineEdit->text();
	QString bodyStr = ui.bodyComboBox->currentText();
	QString operator1 = ui.operateComboBox1->currentText();
	QString operator2 = ui.operateComboBox2->currentText();

	QString itemnumber = defItemNumber(groupStr);

	int paraCount =  ui.paraCountComboBox->itemData( ui.paraCountComboBox->currentIndex() ).toInt();
	if (paraCount == 2)
	{
		if (table1 == ""||table2 == "")
		{
			this->setWindowIcon(QIcon("Resources/参数搜索.png"));
			QMessageBox::warning(this, "提示", "请选择两个参数！", QMessageBox::Ok);
			return ;
		}
	}
	else
	{
		if (table1 == ""||table2 == ""||table3 == "")
		{
			this->setWindowIcon(QIcon("Resources/参数搜索.png"));
			QMessageBox::warning(this, "提示", "请选择三个参数！", QMessageBox::Ok);
			return ;
		}
	}
    //往Item表中添加一条记录，用户自定义参数
	QSqlQuery replaceQuery,insertItemQuery,alterQuery,query;
    QString insertItemSql = "insert into item(itemname,category,itemdefinition,itemmeasure,posture,measurebody,itemnumber) \
							values(?,?,?,?,?,?,?)";
	insertItemQuery.prepare(insertItemSql);//
	insertItemQuery.addBindValue(itemname);
	insertItemQuery.addBindValue(groupStr);
	insertItemQuery.addBindValue(definition);
	insertItemQuery.addBindValue(measureStr);
	insertItemQuery.addBindValue(typeStr);
	insertItemQuery.addBindValue(bodyStr);
	insertItemQuery.addBindValue(itemnumber);
    insertItemQuery.exec();
    //添加用户自定义的字段
	QString alterSql = "alter table " + table + " add " + itemnumber + " float default 9999";
	qDebug() << "alterSql:" << alterSql << endl;
	alterQuery.exec(alterSql);
    //
	//QString sql1 = "select " + table1 + ".number," + dbName1 + "," + dbName2 + " from ";//两个参数时
	QString sql1 = "select " + table1 + ".number," + dbName1 + operator1 + dbName2  + " + 0.0 from ";//两个参数时
	QString sql2 = "select " + table1 + ".number," + dbName1 + operator1 + dbName2 + operator2 + dbName3 + " + 0.0 from ";//三个参数时
	if (paraCount == 2)
	{
		/*if (table1 == ""||table2 == "")
		{
			QMessageBox::warning(this, "提示", "请选择两个参数！", QMessageBox::Ok);
			return ;
		}*/
        if (table1 == table2)
		{
			sql1 += table1 + " where " + dbName1 + "<9999 and " + dbName2 + "<9999";
		}
		else
		{
			sql1 +=table1 + "," + table2 + " where " + table1 + ".number=" + table2 + ".number and "+ dbName1 + "<9999 and " + dbName2 + "<9999";
		}
        qDebug() << "sql1:" << sql1 << endl;
		//添加参数及相应数据
		CustomParameterThread *customParameterThread = new CustomParameterThread(table, sql1, itemnumber, this);
		connect(customParameterThread, SIGNAL(completedCount(int)), ui.progressBar, SLOT(setValue(int)));
		connect(customParameterThread, SIGNAL(finished()), this, SLOT(addParameterDone()));
		customParameterThread->start();
	}
	else
	{
		/*if (table1 == ""||table2 == ""||table3 == "")
		{
			QMessageBox::warning(this, "提示", "请选择三个参数！", QMessageBox::Ok);
			return ;
		}*/

		if ((table1 == table2)&&( table2 == table3))//同一张表
		{
			sql2 += table1 + " where " + dbName1 + "<9999 and " + dbName2 + "<9999 and "+ dbName3 + "<9999";
		}
		else if ((table1 == table2)&&( table2 != table3))//有两张表相同
		{
            sql2 += table1 + "," + table3 + " where " + table1 + ".number=" + table3 + ".number and ";
			sql2 += dbName1 + "<9999 and " + dbName2 + "<9999 and "+ dbName3 + "<9999";
		}
		else if ((table1 == table3)&&( table1 != table2))//有两张表相同
		{
			sql2 += table1 + "," + table2 + " where " + table1 + ".number=" + table2 + ".number and ";
			sql2 += dbName1 + "<9999 and " + dbName2 + "<9999 and "+ dbName3 + "<9999";
		}
		else if ((table2 == table3)&&( table1 != table2))//有两张表相同
		{
			sql2 += table1 + "," + table2 + " where " + table1 + ".number=" + table2 + ".number and ";
			sql2 += dbName1 + "<9999 and " + dbName2 + "<9999 and "+ dbName3 + "<9999";
		}
		else if ((table1 != table2)&&(table1 != table3)&&(table2 != table3))//三张表中
		{
            sql2 += table1 + "," + table2 + "," + table3 ;
			sql2 += " where " + table1 + ".number=" + table2 + ".number and" + table2 + ".number=" + table3 + ".number and ";
			sql2 += dbName1 + "<9999 and " + dbName2 + "<9999 and "+ dbName3 + "<9999";
		}
        qDebug() << "sql2:" << sql2 << endl;

		//添加参数及相应数据
		CustomParameterThread *customParameterThread = new CustomParameterThread(table, sql2, itemnumber, this);
		connect(customParameterThread, SIGNAL(completedCount(int)), ui.progressBar, SLOT(setValue(int)));
		connect(customParameterThread, SIGNAL(finished()), this, SLOT(addParameterDone()));
		customParameterThread->start();
	}
}
//添加参数完成
void CustomParameter::addParameterDone()
{
	Query::freeQuery();
	Query::getQuery();
}