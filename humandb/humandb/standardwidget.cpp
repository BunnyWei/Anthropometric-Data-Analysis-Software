#include "standardwidget.h"
#include "mainwindow.h"

StandardWidget::StandardWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.modelComboBox->addItem("ͷ��ģ��","headmodel");
	ui.modelComboBox->addItem("�ֲ�ģ��","handmodel");
	ui.modelComboBox->addItem("����ģ��","sittingmodel");
	ui.modelComboBox->addItem("����ģ��","standingmodel");
	ui.modelComboBox->addItem("��׼ģ��","standardmodel");
	ui.modelComboBox->addItem("���ģ��","lfmodel");
	ui.modelComboBox->addItem("�ҽ�ģ��","rfmodel");

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
	 QMessageBox::warning(this, "��ʾ", "��ʽ�������");
	}*/
	QRegExp rx;
	rx.setPatternSyntax(QRegExp::RegExp);
	rx.setCaseSensitivity(Qt::CaseSensitive); //��Сд����
	rx.setPattern(QString("^[A-G0-9]+$")); //ƥ�����д�Сд��ĸ��������ɵ��ַ���
	bool b=rx.exactMatch(number); //���ص�ֵΪfalse����Ϊs�к���@�ַ�
	if(b==false || rx.matchedLength() !=5)
	{
		this->setWindowIcon(QIcon("Resources/��׼�˲�ѯ.png"));
	 QMessageBox::warning(this, "��ʾ", "��ʽ�������");
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

	//����ָ����ŵ�ʿ��
	searchQuery.prepare("select number,name,birthday,jointime,bingzhong,people,jiguan,bingyuan,junxian,wenhua,height,weight from info where number = ?");
	searchQuery.addBindValue(number);
	searchQuery.exec();
	searchQuery.next();

	//�Ѹ�ʿ������Ϣ��ʾ������ϣ������ǵ�ǰ������ʿ��
	infoStr = "���\t" + searchQuery.value(0).toString() + "\n\n";
	infoStr += "����\t" + searchQuery.value(1).toString() + "\n\n";
	infoStr += "��������\t" + searchQuery.value(2).toString() + "\n\n";
	infoStr += "����ʱ��\t" + searchQuery.value(3).toString() + "\n\n";
	infoStr += "����\t" + searchQuery.value(4).toString() + "\n\n";
	infoStr += "����\t" + searchQuery.value(5).toString() + "\n\n";
	infoStr += "����\t" + searchQuery.value(6).toString() + "\n\n";
	infoStr += "��Դ\t" + searchQuery.value(7).toString() + "\n\n";
	infoStr += "����\t" + searchQuery.value(8).toString() + "\n\n";
	infoStr += "�Ļ�\t" + searchQuery.value(9).toString() + "\n\n";
	infoStr += "���\t" + searchQuery.value(12).toString() + "\n\n";
	infoStr += "����\t" + searchQuery.value(13).toString();
	ui.infoLabel->setText( infoStr );
	//��ʾģ����Ϣ
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