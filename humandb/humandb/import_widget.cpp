#include "import_widget.h"
#include <QSqlQuery>
#include <QFileDialog>
#include <QLabel>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTime>
#include <QDate>
#include <QThread>
#include <QDebug>
#include <QMap>
#include <QListWidget>
#include "QGlobalVar.h"
#include "basicmanagedialog.h"

//导入线程，所有导入的工作都在这个线程完成，同时更新进度条
class ImportThread : public QThread
{
	Q_OBJECT
signals:
	void completedCount(int);
public:
	ImportThread(QString &dowhat, QString &filepath, QObject *parent = 0): QThread(parent)
	{
		this->dowhat = dowhat;
		//打开Excel数据库
		db = QSqlDatabase::addDatabase("QODBC", "excelimport");
		QString dsn = QString("DRIVER={Microsoft Excel Driver (*.xls)};DSN='';FIRSTROWHASNAMES=1;READONLY=1;CREATE_DB=\"%1\";DBQ=%2").arg(filepath).arg(filepath);
		db.setDatabaseName(dsn);
		bool fDBOpen = db.open();
		excelQuery = new QSqlQuery(db);

		tableColumnsHash.insert("功能尺寸", 159);
		tableColumnsHash.insert("关节转角", 40);
		tableColumnsHash.insert("操作力", 79);
		tableColumnsHash.insert("运动生理", 25);
		tableColumnsHash.insert("心理数据", 5);
	};
	~ImportThread() 
	{
	}
	QStringList getSQL(QString dowhat)
	{
		QStringList sqlList;
		QString sql1 = "";
		QString sql2 = "";
		QString sql3 = "";
		if (dowhat == "基本尺寸")
		{			//36个头部字段
			sql1 = "replace into head values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?)";
			//25个手部字段
			sql2 = "replace into hand values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?)";
			//91个基本尺寸字段
			sql3 = "replace into static(number,st1,st2,st3,st4,st5,st6, \
				   st7,st8,st9,st10,st11,st12,st13,st14,st15,st16, \
				   st17,st18,st19,st20,st21,st22,st23,st24,st25, \
				   st26,st27,st28,st29,st30,st31, \
				   st32,st33,st34,st35,st36,st37,st38,st39,st40,st41, \
				   st42,st43,st44,st45,st46,st47,st48,st49,st50, \
				   st51,st52,st53,st54,st55,st56, \
				   st57,st58,st59,st60,st61,st62,st63,st64,st65,st66, \
				   st67,st68,st69,st70,st71,st72,st73,st74,st75, \
				   st76,st77,st78,st79,st80,st81, \
				   st82,st83,st84,st85,st86,st87,st88,st89,st90,st91) values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
				   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
				   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ? )";
		}
		else if (dowhat == "功能尺寸")
		{
			//159个功能尺寸字段
			sql1 = "replace into func(number,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10, \
				   f11,f12,f13,f14,f15,f16,f17,f18,f19,f20, \
				   f21,f22,f23,f24,f25,f26,f27,f28,f29,f30, \
				   f31,f32,f33,f34,f35,f36,f37,f38,f39,f40, \
				   f41,f42,f43,f44,f45,f46,f47,f48,f49,f50, \
				   f51,f52,f53,f54,f55,f56,f57,f58,f59,f60, \
				   f61,f62,f63,f64,f65,f66,f67,f68,f69,f70, f71,f72,f73,f74,f75,f76,f77,f78,f79,f80, \
				   f81,f82,f83,f84,f85,f86,f87,f88,f89,f90,f91,f92,f93,f94,f95,f96,f97,f98,f99,f100, \
				   f101,f102,f103,f104,f105,f106,f107,f108,f109,f110, \
				   f111,f112,f113,f114,f115,f116,f117,f118,f119,f120, \
				   f121,f122,f123,f124,f125,f126,f127,f128,f129,f130, f131,f132,f133,f134,f135,f136,f137,f138,f139,f140, \
                   f141,f142,f143,f144,f145,f146,f147,f148,f149,f150, \
				   f151,f152,f153,f154,f155,f156,f157,f158,f159) values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
						   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
						   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
						   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
						   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
						   ?,?,?,?,?, ?,?,?,?)";
		}
		else if (dowhat == "关节转角")
		{
			//40个关节转角字段
			sql1 = "replace into joint(number,j1,j2,j3,j4,j5,j6,j7,j8,j9,j10, \
				  j11,j12,j13,j14,j15,j16,j17,j18,j19,j20,j21,j22,j23,j24,j25,j26,j27,j28,j29,j30,  j31,j32,j33,j34,j35,j36,j37,j38,j39,j40) \
				  values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
						   ?,?,?,?,?, ?,?,?,?,?)";
		}
		else if (dowhat == "操作力")
		{
			//79个操作力字段
			sql1 = "replace into operate(number,o1,o2,o3,o4,o5,o6,o7,o8,o9,o10, \
				   o11,o12,o13,o14,o15,o16,o17,o18,o19,o20,o21,o22,o23,o24,o25,o26,o27,o28,o29,o30,o31,o32,o33,o34,o35,o36,o37,o38,o39,o40,   \
				   o41,o42,o43,o44,o45,o46,o47,o48,o49,o50,o51,o52,o53,o54,o55,o56,o57,o58,o59,o60, \
				   o61,o62,o63,o64,o65,o66,o67,o68,o69,o70,o71,o72,o73,o74,o75,o76,o77,o78,o79) values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?,\
										   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
                                           ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,? )";
		}
		else if (dowhat == "运动生理")
		{
			//25个运动生理字段
			sql1 = "replace into sport(number,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10, \
				   s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s25) values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,? )";
		}
		else if (dowhat == "心理数据")
		{
			//5个心理数据字段
			sql1 = "replace into mental(number,m1,m2,m3,m4,m5) values(?, ?,?,?,?,? )";
		}
		else if (dowhat == "军人信息")
		{
			//18个军人信息字段
			sql1 = "replace into info values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,? )";
		}
		sqlList.append(sql1);
		sqlList.append(sql2);
		sqlList.append(sql3);

		return sqlList;
	}
	int getItemCount() const
	{
		return this->itemCount;
	}
private:
	QSqlDatabase db;
	QString dowhat;
	QSqlQuery *excelQuery;
	QStringList currentSqlList;
	QHash <QString, int> tableColumnsHash;
	int itemCount;
	void run()
	{
		int count = 0;
		this->itemCount = 0;
		QString excelSql = "SELECT * FROM [Sheet1$]";
		bool f = excelQuery->exec(excelSql);

		currentSqlList = getSQL(dowhat);

		/*if (dowhat != "军人信息")
			excelQuery->next();*/

		while (excelQuery->next())
		{
			if (dowhat == "军人信息")
			{
				QString sql = currentSqlList[0];
				QSqlQuery query;
				query.prepare(sql);
				query.addBindValue(excelQuery->value(0).toString());
				query.addBindValue(excelQuery->value(1).toString());
				query.addBindValue(excelQuery->value(2).toDate());
				query.addBindValue(excelQuery->value(3).toDate());

				query.addBindValue(excelQuery->value(4).toString());
				query.addBindValue(excelQuery->value(5).toString());
				query.addBindValue(excelQuery->value(6).toString());
				query.addBindValue(excelQuery->value(7).toString());
				query.addBindValue(excelQuery->value(8).toString());
				query.addBindValue(excelQuery->value(9).toString());
				query.addBindValue(excelQuery->value(10).toString());
				query.addBindValue(excelQuery->value(11).toString());

				query.addBindValue(excelQuery->value(12).toString().toFloat());
				query.addBindValue(excelQuery->value(13).toString().toFloat());

				query.addBindValue(excelQuery->value(14).toString());
				query.addBindValue(excelQuery->value(15).toString());

				query.addBindValue(excelQuery->value(16).toString().toFloat());
				query.addBindValue(excelQuery->value(17).toString().toFloat());

				query.exec();
			}
			else if (dowhat == "基本尺寸")
			{			
				QString sql1 = currentSqlList[0];
				QString sql2 = currentSqlList[1];
				QString sql3 = currentSqlList[2];
				QSqlQuery query1;
				QSqlQuery query2;
				QSqlQuery query3;

				QString number = excelQuery->value(0).toString();

				query1.prepare(sql1);
				query1.addBindValue(number);
				for (int i = 1; i <= 36; i++)
				{
					QString temp1 = excelQuery->value(i).toString();
					if ("" == temp1 || " " == temp1)
						temp1 = "9999";
					query1.addBindValue(temp1.toFloat());
				}
				bool b1 = query1.exec();

				query2.prepare(sql2);
				query2.addBindValue(number);
				for (int i = 37; i <= 61; i++)
				{
					QString temp2 = excelQuery->value(i).toString();
					if ("" == temp2 || " " == temp2)
						temp2 = "9999";
					query2.addBindValue(temp2.toFloat());
				}
				bool b2 = query2.exec();

				query3.prepare(sql3);
				query3.addBindValue(number);
				for (int i = 62; i <= 152; i++)
				{
					QString temp3 = excelQuery->value(i).toString();
					if ("" == temp3 || " " == temp3)
						temp3 = "9999";
					query3.addBindValue(temp3.toFloat());
				}
				bool b3 = query3.exec();

			}// end if (dowhat == "基本尺寸")
			else 
			{
				QString sql = currentSqlList[0];
				QSqlQuery query;
				query.prepare(sql);
				query.addBindValue(excelQuery->value(0).toString());
				int size = tableColumnsHash[dowhat];
				if (dowhat == "功能尺寸")
				{
					for (int i = 1; i <= size-1; i++)
					{
						QString temp = excelQuery->value(i).toString();
						if ("" == temp)
							temp = "9999";
						query.addBindValue(temp.toFloat());
					}
					QString endStr = excelQuery->value(size).toString();
					query.addBindValue(endStr);
					/*qDebug() << excelQuery->value(size+1).toString();
					qDebug() << excelQuery->value(size+2).toString();
					qDebug() << excelQuery->value(size+3).toString();*/
				}
				else
				{
					for (int i = 1; i <= size; i++)
					{
						QString temp = excelQuery->value(i).toString();
						if ("" == temp)
							temp = "9999";
						query.addBindValue(temp.toFloat());
					}
				}
				
				bool b = query.exec();
			}

			count++;
			//if (count % 10 == 0) 
			{
				emit completedCount(count);
			}
		}//end while
		this->itemCount = count;
		emit completedCount(count);
		/*if (count < 101)
             emit completedCount(100);*/
	};
};



#include "import_widget.moc"

ImportWidget::ImportWidget(QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);
	ui.progressBar->setValue(0);
	ui.statusLabel->setStyleSheet("color: red");
	ui.excelRadioButton->setChecked(true);

	ui.dataComboBox->addItem("军人信息", "info");
	ui.dataComboBox->addItem("基本尺寸", "static");
	ui.dataComboBox->addItem("功能尺寸", "func");
	ui.dataComboBox->addItem("关节转角", "joint");
	ui.dataComboBox->addItem("操作力", "operate");
	ui.dataComboBox->addItem("运动生理", "sport");
	ui.dataComboBox->addItem("心理数据", "mental");

	tableColumnsHash.insert("功能尺寸", 86);
	tableColumnsHash.insert("关节转角", 40);
	tableColumnsHash.insert("操作力", 79);
	tableColumnsHash.insert("运动生理", 25);
	tableColumnsHash.insert("心理数据", 5);

	ui.listWidget->setVisible(false);

	connect(this, SIGNAL(completedCount(int)), ui.progressBar, SLOT(setValue(int)));
	
}

ImportWidget::~ImportWidget()
{

}


void ImportWidget::on_openButton_clicked()
{
	QString fileName;
	if (ui.excelRadioButton->isChecked()) {
		fileName = QFileDialog::getOpenFileName(this, tr("Excel Files"), qApp->applicationDirPath (),
			tr("Excel Files (*.xls)"));
	}
	else if (ui.csvRadioButton->isChecked()){
		fileName = QFileDialog::getOpenFileName(this, tr("CSV Files"), qApp->applicationDirPath (),
			tr("CSV Files (*.csv)"));
	}
	this->ui.fileNameLineEdit->setText(fileName);
}

void ImportWidget::on_importButton_clicked()
{
	//开始导入
	QString filepath = ui.fileNameLineEdit->text();
	QString dowhat = ui.dataComboBox->currentText();

	bool isXls = ui.excelRadioButton->isChecked();
	bool isCsv = ui.csvRadioButton->isChecked();

	ui.progressBar->setValue(0);

	pwdDialog = new PasswordDialog;
	pwdDialog->exec();  
	
	if(pwdDialog->isCancel()) 
	{
		delete pwdDialog;
		return;
	}
	if(pwdDialog->isPasswordCorrect())
	{
		if (isXls)
		{
			QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "excelimport");
			QString dsn = QString("DRIVER={Microsoft Excel Driver (*.xls)};DSN='';FIRSTROWHASNAMES=1;READONLY=1;CREATE_DB=\"%1\";DBQ=%2").arg(filepath).arg(filepath);
			db.setDatabaseName(dsn);
			bool fDBOpen = db.open();
			QSqlQuery *excelQuery = new QSqlQuery(db);

			QString sql = "SELECT count(*) FROM [Sheet1$]";
			bool f = excelQuery->exec(sql);
			excelQuery->next();
			int size = excelQuery->value(0).toInt();
			importThread = new ImportThread(dowhat, filepath, this);
			ui.progressBar->setMaximum(size-1);
			connect(importThread, SIGNAL(completedCount(int)), ui.progressBar, SLOT(setValue(int)));
			connect(importThread, SIGNAL(finished()), this, SLOT(importDone()));
			importThread->start();
			Query::freeQuery();
		}
		else if (isCsv)
		{
			importCSVFile(dowhat, filepath);
			Query::freeQuery();
			Query::getQuery();
		}
	}
	else
	{
		this->setWindowIcon(QIcon("Resources/password.png"));
        QMessageBox::warning(this, "提示", "口令输入错误！");
		return;
	}
}

void ImportWidget::importCSVFile(QString &dowhat, QString &filepath)
{
	QString line;
	int count = 0;
	int size = 0;
	QStringList currentSqlList = getSQL(dowhat);

	QFile file(filepath);
	file.open(QFile::ReadOnly);
	QTextStream in(&file);
	in.setCodec("GBK");

	line = in.readLine();
	if (dowhat != "军人信息")
		in.readLine();
	//while(!line.isEmpty() && !line.startsWith(",")) 
	while(!line.isEmpty()) 
	{
		line = in.readLine();
		size++;
	}
	ui.progressBar->setMaximum(size);

	file.seek(0);
	in.readLine();
	/*if (dowhat != "军人信息")
		in.readLine();*/
	while (!in.atEnd()) 
	{
		line = in.readLine();
		qDebug() << "一行：" << line;
		if (line.startsWith(",")) 
		{
			continue;
		}
		QStringList lineList = line.split(",");
		if (dowhat == "军人信息")
		{
			QString sql = currentSqlList[0];
			QSqlQuery query;
			query.prepare(sql);
			query.addBindValue(lineList[0]);
			query.addBindValue(lineList[1]);
			query.addBindValue(lineList[2]);
			query.addBindValue(lineList[3]);

			query.addBindValue(lineList[4]);
			query.addBindValue(lineList[5]);
			query.addBindValue(lineList[6]);
			query.addBindValue(lineList[7]);
			query.addBindValue(lineList[8]);
			query.addBindValue(lineList[9]);
			query.addBindValue(lineList[10]);
			query.addBindValue(lineList[11]);

			query.addBindValue(lineList[12].toFloat());
			query.addBindValue(lineList[13].toFloat());

			query.addBindValue(lineList[14]);
			query.addBindValue(lineList[15]);

			query.addBindValue(lineList[16].toFloat());
			query.addBindValue(lineList[17].toFloat());

			query.exec();
		}
		else if (dowhat == "基本尺寸")
		{			
			QString sql1 = currentSqlList[0];
			QString sql2 = currentSqlList[1];
			QString sql3 = currentSqlList[2];
			QSqlQuery query1;
			QSqlQuery query2;
			QSqlQuery query3;

			QString number = lineList[0];

			query1.prepare(sql1);
			query1.addBindValue(number);
			for (int i = 1; i <= 36; i++)
			{
				QString temp = lineList[i];
				if ("" == temp)
					temp = "9999";
				query1.addBindValue(temp.toFloat());
			}
			bool b1 = query1.exec();

			query2.prepare(sql2);
			query2.addBindValue(number);
			for (int i = 37; i <= 61; i++)
			{
				QString temp = lineList[i];
				if ("" == temp)
					temp = "9999";
				query2.addBindValue(temp.toFloat());
			}
			bool b2 = query2.exec();

			query3.prepare(sql3);
			query3.addBindValue(number);
			for (int i = 62; i <= 152; i++)
			{
				QString temp = lineList[i];
				if ("" == temp)
					temp = "9999";
				query3.addBindValue(temp.toFloat());
			}
			bool b3 = query3.exec();

		}// end if (dowhat == "基本尺寸")
		else 
		{
			QString sql = currentSqlList[0];
			QSqlQuery query;
			query.prepare(sql);
			query.addBindValue(lineList[0]);
			int size = tableColumnsHash[dowhat];
			if (dowhat == "基本尺寸")
			{
				for (int i = 1; i <= size-1; i++)
				{
					QString temp = lineList[i];
					if ("" == temp)
						temp = "9999";
					query.addBindValue(temp.toFloat());
				}
				QString endStr = lineList[size];
				query.addBindValue(endStr);
			}
			else
			{
				for (int i = 1; i <= size; i++)
				{
					QString temp = lineList[i];
					if ("" == temp)
						temp = "9999";
					query.addBindValue(temp.toFloat());
				}
			}
			for (int i = 1; i <= size; i++)
			{
				QString temp = lineList[i];
				if ("" == temp)
					temp = "9999";
				query.addBindValue(temp.toFloat());
			}
			bool b = query.exec();
		}

		count++;
		if (count % 10 == 0) 
		{
			emit completedCount(count);
		}
	}//end while
	emit completedCount(count+1);

	ui.itemCountLabel->setText(QString("成功导入%1条记录").arg(count));
}

QStringList ImportWidget::getSQL(QString dowhat)
{
	QStringList sqlList;
	QString sql1 = "";
	QString sql2 = "";
	QString sql3 = "";
	if (dowhat == "基本尺寸")
	{
		//36个头部字段
		sql1 = "replace into head values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?)";
			//25个手部字段
			sql2 = "replace into hand values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?)";
			//91个基本尺寸字段
			sql3 = "replace into static(number,st1,st2,st3,st4,st5,st6, \
				   st7,st8,st9,st10,st11,st12,st13,st14,st15,st16, \
				   st17,st18,st19,st20,st21,st22,st23,st24,st25, \
				   st26,st27,st28,st29,st30,st31, \
				   st32,st33,st34,st35,st36,st37,st38,st39,st40,st41, \
				   st42,st43,st44,st45,st46,st47,st48,st49,st50, \
				   st51,st52,st53,st54,st55,st56, \
				   st57,st58,st59,st60,st61,st62,st63,st64,st65,st66, \
				   st67,st68,st69,st70,st71,st72,st73,st74,st75, \
				   st76,st77,st78,st79,st80,st81, \
				   st82,st83,st84,st85,st86,st87,st88,st89,st90,st91) values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
				   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
				   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ? )";
	}
	else if (dowhat == "功能尺寸")
	{
		//159个功能尺寸字段
		sql1 = "replace into func(number,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10, \
				   f11,f12,f13,f14,f15,f16,f17,f18,f19,f20, \
				   f21,f22,f23,f24,f25,f26,f27,f28,f29,f30, \
				   f31,f32,f33,f34,f35,f36,f37,f38,f39,f40, \
				   f41,f42,f43,f44,f45,f46,f47,f48,f49,f50, \
				   f51,f52,f53,f54,f55,f56,f57,f58,f59,f60, \
				   f61,f62,f63,f64,f65,f66,f67,f68,f69,f70, f71,f72,f73,f74,f75,f76,f77,f78,f79,f80, \
				   f81,f82,f83,f84,f85,f86,f87,f88,f89,f90,f91,f92,f93,f94,f95,f96,f97,f98,f99,f100, \
				   f101,f102,f103,f104,f105,f106,f107,f108,f109,f110, \
				   f111,f112,f113,f114,f115,f116,f117,f118,f119,f120, \
				   f121,f122,f123,f124,f125,f126,f127,f128,f129,f130, f131,f132,f133,f134,f135,f136,f137,f138,f139,f140, \
                   f141,f142,f143,f144,f145,f146,f147,f148,f149,f150, \
				   f151,f152,f153,f154,f155,f156,f157,f158,f159) values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
						   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
						   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
						   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
						   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
						   ?,?,?,?,?, ?,?,?,?)";
	}
	else if (dowhat == "关节转角")
	{
		//40个关节转角字段
		sql1 = "replace into joint(number,j1,j2,j3,j4,j5,j6,j7,j8,j9,j10, \
				  j11,j12,j13,j14,j15,j16,j17,j18,j19,j20,j21,j22,j23,j24,j25,j26,j27,j28,j29,j30,  j31,j32,j33,j34,j35,j36,j37,j38,j39,j40) values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
						   ?,?,?,?,?, ?,?,?,?,?)";
	}
	else if (dowhat == "操作力")
	{
		//79个操作力字段
		sql1 = "replace into operate(number,o1,o2,o3,o4,o5,o6,o7,o8,o9,o10, \
				   o11,o12,o13,o14,o15,o16,o17,o18,o19,o20,o21,o22,o23,o24,o25,o26,o27,o28,o29,o30,o31,o32,o33,o34,o35,o36,o37,o38,o39,o40,   \
				   o41,o42,o43,o44,o45,o46,o47,o48,o49,o50,o51,o52,o53,o54,o55,o56,o57,o58,o59,o60, \
				   o61,o62,o63,o64,o65,o66,o67,o68,o69,o70,o71,o72,o73,o74,o75,o76,o77,o78,o79) values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?,\
										   ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, \
                                           ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,? )";
		}
		else if (dowhat == "运动生理")
		{
			//25个运动生理字段
			sql1 = "replace into sport(number,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10, \
				   s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s25) values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,? )";
		}
		else if (dowhat == "心理数据")
		{
			//5个心理数据字段
			sql1 = "replace into mental(number,m1,m2,m3,m4,m5) values(?, ?,?,?,?,? )";
	}
	else if (dowhat == "军人信息")
	{
		//18个军人信息字段
		sql1 = "replace into info values(?, ?,?,?,?,?, ?,?,?,?,?, ?,?,?,?,?, ?,? )";
	}
	sqlList.append(sql1);
	sqlList.append(sql2);
	sqlList.append(sql3);

	return sqlList;
}

//导入线程完成工作后，弹出对话框报告导入的情况
void ImportWidget::importDone()
{
	/*if (errorList.size()) {
		int errorCount = errorList.size();
		int successCount = ui.progressBar->maximum() - errorCount;
		QString errorStr = QString("成功导入%1条记录\n有%2条记录导入出现错误，他们的军人编号为:\n").arg(successCount).arg(errorCount);
		for (int i = 0; i < errorList.size(); i++) {
			errorStr += (errorList[i]+", ");
			if ((i+1)%6 == 0) {
				errorStr += "\n";
			}
		}
		errorStr += "\n请检查他们的信息是否正确";
		if ( successCount == 0) {
			errorStr = "导入出现错误，Excel文件可能被其他程序打开";
		}
		ui.statusLabel->setText(errorStr);
	}
	else */
	{
		ui.itemCountLabel->setText(QString("成功导入%1条记录").arg(importThread->getItemCount()));
		Query::freeQuery();
		Query::getQuery();
	}
}

void ImportWidget::importPhotoDone()
{
}
void ImportWidget::importModelDone()
{
	QMessageBox::about(this, "提示", "导入模型完成！");
}

void ImportWidget::on_imPhotoBtn_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
													 "/home",
													 QFileDialog::ShowDirsOnly
													 | QFileDialog::DontResolveSymlinks);
	if ("" == dir)
		return;
	ImportPhotoThread *importPhotoThread = new ImportPhotoThread(dir, this);
	connect(importPhotoThread, SIGNAL(completedCount(int)), ui.photoProgressBar, SLOT(setValue(int)));
	connect(importPhotoThread, SIGNAL(finished()), this, SLOT(importPhotoDone()));
	importPhotoThread->start();
}

void ImportWidget::on_importModelBtn_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
													 "/home",
													 QFileDialog::ShowDirsOnly
													 | QFileDialog::DontResolveSymlinks);
	if ("" == dir)
		return;
	ImportModelThread *importModelThread = new ImportModelThread(dir, this);
	connect(importModelThread, SIGNAL(completedCount(int)), ui.modelProgressBar, SLOT(setValue(int)));
	connect(importModelThread, SIGNAL(finished()), this, SLOT(importModelDone()));
	importModelThread->start();
}

void ImportWidget::on_dataComboBox_currentIndexChanged(int index)
{
	QString table = ui.dataComboBox->itemData(index, Qt::UserRole).toString();
	QString group = ui.dataComboBox->currentText();

	QSqlQuery query;
	QString sql = "select count(*) from " + table;
	query.exec(sql);
	query.next();
	int count = query.value(0).toInt();
	QString countStr = "当前数据库中有" + QString::number(count) + "条" + group + "记录";
	ui.countLabel->setText(countStr);
}

void ImportWidget::on_listWidget_clicked(const QModelIndex &)
{

}
//************************************************************************************
void ImportWidget::on_pushButton_clicked()
{
	ui.listWidget->clear();
	QSqlQuery itemQuery;
	itemQuery.exec("select item_id, itemnumber, itemname from item");
	ui.statisticProgressBar->setMaximum(itemQuery.size());
	ui.statisticProgressBar->setValue(0);

	WorkThread *workThread = new WorkThread(ui.listWidget);
	connect(workThread, SIGNAL(finished()), this, SLOT(workDone()));
	connect(workThread, SIGNAL(complete_count(int)), ui.statisticProgressBar, SLOT(setValue(int)));
	workThread->start();
	ui.pushButton->setDisabled(true);
}

void ImportWidget::workDone()
{					
	ui.pushButton->setDisabled(false);
	QSqlQuery query;
	query.exec("truncate table statisticmemory");
	query.exec("insert into statisticmemory select * from statistic");
		QListWidgetItem *newItem = new QListWidgetItem;
	ui.listWidget->insertItem(ui.listWidget->count(), newItem);
	newItem->setText(QString("全部计算已完成！"));
}
void ImportWidget::on_VisiblePushButton_clicked()
{
	if (ui.listWidget->isVisible())
	{
		ui.listWidget->setVisible(false);
		ui.VisiblePushButton->setText("显示详细信息");
	}
	else
	{
		ui.listWidget->setVisible(true);
		ui.VisiblePushButton->setText("收起");
	}
}