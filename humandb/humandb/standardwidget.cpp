#include "standardwidget.h"
#include "mainwindow.h"

StandardWidget::StandardWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.modelComboBox->addItem("头部模型","headmodel");
	ui.modelComboBox->addItem("手部模型","handmodel");
	ui.modelComboBox->addItem("坐姿模型","sittingmodel");
	ui.modelComboBox->addItem("立姿模型","standingmodel");
	ui.modelComboBox->addItem("标准模型","standardmodel");
	ui.modelComboBox->addItem("左脚模型","lfmodel");
	ui.modelComboBox->addItem("右脚模型","rfmodel");

	ui.graphicsView->resize(180, 220);
}

StandardWidget::~StandardWidget()
{

}


void StandardWidget::on_searchBtn_clicked()
{
	QString number = ui.numberLineEdit->text();
	QSqlQuery photoQuery;
	/*QString numdown="A0000";
	QString numup="G9999";
	if(numdown > number || number >numup)
	{
	 QMessageBox::warning(this, "提示", "格式输入错误！");
	}*/
	QRegExp rx;
	rx.setPatternSyntax(QRegExp::RegExp);
	rx.setCaseSensitivity(Qt::CaseSensitive); //大小写敏感
	rx.setPattern(QString("^[A-G0-9]+$")); //匹配所有大小写字母和数字组成的字符串
	bool b=rx.exactMatch(number); //返回的值为false，因为s中含有@字符
	if(b==false || rx.matchedLength() !=5)
	{
		this->setWindowIcon(QIcon("Resources/标准人查询.png"));
	 QMessageBox::warning(this, "提示", "格式输入错误！");
	 return;
	}
	QString photoSql = "select path from photoinfo where number = '";
	photoSql += number + "'";
	photoQuery.exec(photoSql);
	photoQuery.next();
	QString photoPath = photoQuery.value(0).toString();
	QPixmap originalPhoto(photoPath);
	QPixmap photo = originalPhoto.scaled(150, 200);
    QGraphicsScene *gs = new QGraphicsScene();
    gs->addPixmap(photo);
	ui.graphicsView->setStyleSheet("padding-bottom:10px");
	ui.graphicsView->setScene(gs);

	QSqlQuery searchQuery;
	QString infoStr;

	//查找指定编号的士兵
	searchQuery.prepare("select number,name,birthday,jointime,bingzhong,people,jiguan,bingyuan,junxian,wenhua,height,weight from info where number = ?");
	searchQuery.addBindValue(number);
	searchQuery.exec();
	searchQuery.next();

	//把该士兵的信息显示在面板上，他就是当前测量的士兵
	infoStr = "编号\t" + searchQuery.value(0).toString() + "\n\n";
	infoStr += "姓名\t" + searchQuery.value(1).toString() + "\n\n";
	infoStr += "出生日期\t" + searchQuery.value(2).toString() + "\n\n";
	infoStr += "入伍时间\t" + searchQuery.value(3).toString() + "\n\n";
	infoStr += "兵种\t" + searchQuery.value(4).toString() + "\n\n";
	infoStr += "名族\t" + searchQuery.value(5).toString() + "\n\n";
	infoStr += "籍贯\t" + searchQuery.value(6).toString() + "\n\n";
	infoStr += "兵源\t" + searchQuery.value(7).toString() + "\n\n";
	infoStr += "军衔\t" + searchQuery.value(8).toString() + "\n\n";
	infoStr += "文化\t" + searchQuery.value(9).toString() + "\n\n";
	infoStr += "身高\t" + searchQuery.value(12).toString() + "\n\n";
	infoStr += "体重\t" + searchQuery.value(13).toString();
	ui.infoLabel->setText( infoStr );
	//显示模型信息
	QString table = ui.modelComboBox->itemData(ui.modelComboBox->currentIndex(), Qt::UserRole).toString();
	QSqlQuery modelQuery;
	QString modelSql = "select path from " + table + " where number = '";
	modelSql += number + "'";
	modelQuery.exec(modelSql);
	modelQuery.next();
	QString modelPath = modelQuery.value(0).toString();
	MainWindow *mainWin = MainWindow::instance();
	GLArea *glArea = mainWin->GLA();
	if(glArea == NULL)
		return;
	bool bOpenMesh = mainWin->open(modelPath, glArea);

	if (bOpenMesh)
		glArea->showID = 2;
	else
		glArea->showID = 3;
}