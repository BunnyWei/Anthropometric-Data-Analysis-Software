#include "customparameter.h"
#include "query.h"
CustomParameter::CustomParameter(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.paraComboBox1->addItem("ȫ������", "all");
	ui.paraComboBox1->addItem("�����ߴ�", "static");
	ui.paraComboBox1->addItem("���ܳߴ�", "func");
	ui.paraComboBox1->addItem("�ؽ�ת��", "joint");
	ui.paraComboBox1->addItem("������", "operate");
	ui.paraComboBox1->addItem("�˶�����", "sport");
	ui.paraComboBox1->addItem("�������", "mental");

	ui.paraComboBox2->addItem("ȫ������", "all");
	ui.paraComboBox2->addItem("�����ߴ�", "static");
	ui.paraComboBox2->addItem("���ܳߴ�", "func");
	ui.paraComboBox2->addItem("�ؽ�ת��", "joint");
	ui.paraComboBox2->addItem("������", "operate");
	ui.paraComboBox2->addItem("�˶�����", "sport");
	ui.paraComboBox2->addItem("�������", "mental");

	ui.paraComboBox3->addItem("ȫ������", "all");
	ui.paraComboBox3->addItem("�����ߴ�", "static");
	ui.paraComboBox3->addItem("���ܳߴ�", "func");
	ui.paraComboBox3->addItem("�ؽ�ת��", "joint");
	ui.paraComboBox3->addItem("������", "operate");
	ui.paraComboBox3->addItem("�˶�����", "sport");
	ui.paraComboBox3->addItem("�������", "mental");

	ui.groupComboBox->addItem("�����ߴ�", "static");
	ui.groupComboBox->addItem("���ܳߴ�", "func");
	ui.groupComboBox->addItem("�ؽ�ת��", "joint");
	ui.groupComboBox->addItem("������", "operate");
	ui.groupComboBox->addItem("�˶�����", "sport");
	ui.groupComboBox->addItem("�������", "mental");

	ui.bodyComboBox->addItem("ͷ����");
	ui.bodyComboBox->addItem("��֫��+��ؽ�");
	ui.bodyComboBox->addItem("�ֲ�+��");
	ui.bodyComboBox->addItem("���ɲ�");
	ui.bodyComboBox->addItem("��֫��");
	ui.bodyComboBox->addItem("�㲿+�׹ؽ�");
	ui.bodyComboBox->addItem("ȫ���");

    //��������
	ui.operateComboBox1->addItem("+","add");
	ui.operateComboBox1->addItem("-","decrease");
	ui.operateComboBox1->addItem("*","multiply");
	ui.operateComboBox1->addItem("/","division");
    //��������
	ui.operateComboBox2->addItem("+","add");
	ui.operateComboBox2->addItem("-","decrease");
	ui.operateComboBox2->addItem("*","multiply");
	ui.operateComboBox2->addItem("/","division");

	ui.paraCountComboBox->addItem("2������", "2");
	ui.paraCountComboBox->addItem("3������", "3");


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
		ui.typeComboBox->addItem("ͷ������");
		ui.typeComboBox->addItem("�ֲ�����");
		ui.typeComboBox->addItem("�㲿����");
		ui.typeComboBox->addItem("���˲���");
		ui.typeComboBox->addItem("���˲���");
	}
	else if (group == "func")
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("���˲���");
		ui.typeComboBox->addItem("��̬������");
		ui.typeComboBox->addItem("���㲿����");
		ui.typeComboBox->addItem("���˲���");
		ui.typeComboBox->addItem("������̬�ߴ�");
		ui.typeComboBox->addItem("��װ������");
	}
	else if (group == "joint")
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("δ����");
	}
	else if (group == "operate")
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("��������");
		ui.typeComboBox->addItem("��������");
		ui.typeComboBox->addItem("�ŵ���");
		ui.typeComboBox->addItem("��������");
		ui.typeComboBox->addItem("ʳָָ����");
		ui.typeComboBox->addItem("����");
	}
	else if (group == "sport")
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("δ����");
	}
	else if (group == "mental")
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("δ����");
	}
	else if (group == "all")
	{
		ui.typeComboBox->clear();
		ui.typeComboBox->addItem("δ����");
	}
#endif

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

	//qDebug() << "���Ҳ���SQL: " << sql;

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

	//qDebug() << "���Ҳ���SQL: " << sql;

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

	//qDebug() << "���Ҳ���SQL: " << sql;

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
//�õ��û�ѡ���ֶ�
void CustomParameter::getSelectedDBName()
{
	QListWidgetItem * item;//�����б���
	QString itemname,nameDb;//��������
	int count = 0;
	
	for (int i = 0; i < ui.listWidget1->count(); i++) 
	{
		item = ui.listWidget1->item(i);
		if ( item->checkState() == Qt::Checked ) 
		{
			itemname = item->text();	/* ������Ŀ������ */
			dbName1 = item->data(Qt::UserRole).toString();	/* ������Ŀ���ݿ��ֶ��� */
			table1 = getTable(dbName1);
		}
	}
		
	for (int i = 0; i < ui.listWidget2->count(); i++) 
	{
		item = ui.listWidget2->item(i);
		if ( item->checkState() == Qt::Checked ) 
		{
			itemname = item->text();	/* ������Ŀ������ */
			dbName2 = item->data(Qt::UserRole).toString();	/* ������Ŀ���ݿ��ֶ��� */
			table2 = getTable(dbName2);
		}
	}
	
	for (int i = 0; i < ui.listWidget3->count(); i++) 
	{
		item = ui.listWidget3->item(i);
		if ( item->checkState() == Qt::Checked ) 
		{
			itemname = item->text();	/* ������Ŀ������ */
			dbName3 = item->data(Qt::UserRole).toString();	/* ������Ŀ���ݿ��ֶ��� */
			table3 = getTable(dbName3);
		}
	}
	
}

inline QString CustomParameter::getTable(QString  attribute)
{//�ж�ĳ�����������ĸ���
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
	if (table == "�����ߴ�") 
	{
		itemnumber = QString("st%1").arg(num+2);
	} 
	else if (table == "���ܳߴ�") 
	{
		itemnumber = QString("fa%1").arg(num+2);
	} 
	else if (table == "�ؽ�ת��") 
	{
		itemnumber = QString("j%1").arg(num+2);
	} 
	else if (table == "������") 
	{
		itemnumber = QString("o%1").arg(num+2);
	} 
	else if (table == "�˶�����") 
	{
		itemnumber = QString("s%1").arg(num+2);
	} 
	else if (table == "�������") 
	{
		itemnumber = QString("ma%1").arg(num+2);
	} 
	
	return itemnumber;

}

void CustomParameter::on_addBtn_clicked()
{
	getSelectedDBName();//ȡ����ѡ����
	QString itemname = ui.lineEdit->text();
	QString groupStr = ui.groupComboBox->currentText();
	QString table = ui.groupComboBox->itemData( ui.groupComboBox->currentIndex() ).toString();
	QString typeStr = ui.typeComboBox->currentText();
	if (typeStr == "ȫ��") typeStr = "";
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
			this->setWindowIcon(QIcon("Resources/��������.png"));
			QMessageBox::warning(this, "��ʾ", "��ѡ������������", QMessageBox::Ok);
			return ;
		}
	}
	else
	{
		if (table1 == ""||table2 == ""||table3 == "")
		{
			this->setWindowIcon(QIcon("Resources/��������.png"));
			QMessageBox::warning(this, "��ʾ", "��ѡ������������", QMessageBox::Ok);
			return ;
		}
	}
    //��Item�������һ����¼���û��Զ������
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
    //����û��Զ�����ֶ�
	QString alterSql = "alter table " + table + " add " + itemnumber + " float default 9999";
	qDebug() << "alterSql:" << alterSql << endl;
	alterQuery.exec(alterSql);
    //
	//QString sql1 = "select " + table1 + ".number," + dbName1 + "," + dbName2 + " from ";//��������ʱ
	QString sql1 = "select " + table1 + ".number," + dbName1 + operator1 + dbName2  + " + 0.0 from ";//��������ʱ
	QString sql2 = "select " + table1 + ".number," + dbName1 + operator1 + dbName2 + operator2 + dbName3 + " + 0.0 from ";//��������ʱ
	if (paraCount == 2)
	{
		/*if (table1 == ""||table2 == "")
		{
			QMessageBox::warning(this, "��ʾ", "��ѡ������������", QMessageBox::Ok);
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
		//��Ӳ�������Ӧ����
		CustomParameterThread *customParameterThread = new CustomParameterThread(table, sql1, itemnumber, this);
		connect(customParameterThread, SIGNAL(completedCount(int)), ui.progressBar, SLOT(setValue(int)));
		connect(customParameterThread, SIGNAL(finished()), this, SLOT(addParameterDone()));
		customParameterThread->start();
	}
	else
	{
		/*if (table1 == ""||table2 == ""||table3 == "")
		{
			QMessageBox::warning(this, "��ʾ", "��ѡ������������", QMessageBox::Ok);
			return ;
		}*/

		if ((table1 == table2)&&( table2 == table3))//ͬһ�ű�
		{
			sql2 += table1 + " where " + dbName1 + "<9999 and " + dbName2 + "<9999 and "+ dbName3 + "<9999";
		}
		else if ((table1 == table2)&&( table2 != table3))//�����ű���ͬ
		{
            sql2 += table1 + "," + table3 + " where " + table1 + ".number=" + table3 + ".number and ";
			sql2 += dbName1 + "<9999 and " + dbName2 + "<9999 and "+ dbName3 + "<9999";
		}
		else if ((table1 == table3)&&( table1 != table2))//�����ű���ͬ
		{
			sql2 += table1 + "," + table2 + " where " + table1 + ".number=" + table2 + ".number and ";
			sql2 += dbName1 + "<9999 and " + dbName2 + "<9999 and "+ dbName3 + "<9999";
		}
		else if ((table2 == table3)&&( table1 != table2))//�����ű���ͬ
		{
			sql2 += table1 + "," + table2 + " where " + table1 + ".number=" + table2 + ".number and ";
			sql2 += dbName1 + "<9999 and " + dbName2 + "<9999 and "+ dbName3 + "<9999";
		}
		else if ((table1 != table2)&&(table1 != table3)&&(table2 != table3))//���ű���
		{
            sql2 += table1 + "," + table2 + "," + table3 ;
			sql2 += " where " + table1 + ".number=" + table2 + ".number and" + table2 + ".number=" + table3 + ".number and ";
			sql2 += dbName1 + "<9999 and " + dbName2 + "<9999 and "+ dbName3 + "<9999";
		}
        qDebug() << "sql2:" << sql2 << endl;

		//��Ӳ�������Ӧ����
		CustomParameterThread *customParameterThread = new CustomParameterThread(table, sql2, itemnumber, this);
		connect(customParameterThread, SIGNAL(completedCount(int)), ui.progressBar, SLOT(setValue(int)));
		connect(customParameterThread, SIGNAL(finished()), this, SLOT(addParameterDone()));
		customParameterThread->start();
	}
}
//��Ӳ������
void CustomParameter::addParameterDone()
{
	Query::freeQuery();
	Query::getQuery();
}