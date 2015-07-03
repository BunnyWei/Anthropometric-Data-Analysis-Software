#include "percentiledialog.h"

percentileDialog::percentileDialog(QString itemnum, QString itemName, QMap<QString, QList<float> > &itemMap, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
   
	this->itemnum = itemnum;
	this->itemName = itemName;
	this->itemMap = itemMap;
	int pStart = 50;
	int pEnd = 550;

	for (int i = pStart; i <= pEnd; i++)
	{
		QPoint point;
		point.setX(i);
		int y = 200 - 20000 * Normal(0, 80.0, (double)(i-300) ); 
		point.setY(y);
		pVector.push_back(point);
	}
	ui.horizontalSlider->setSliderPosition(50);
	connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(update()));
}

percentileDialog::~percentileDialog()
{

}

void percentileDialog::paintEvent(QPaintEvent *event)
{
	QPainter painter( this );
	
	painter.drawLine(50, 250, 550, 250); 
	painter.drawLine(300, 50, 300, 250);
//painter.setPen(Qt::blue);
	/*QWidget *widget;
	QPalette palette;
	palette.setBrush(widget->backgroundRole(),QBrush(":/Resources/58.png"));
	widget->setPalette(palette);*/
	QPalette palette;
    palette.setColor(QPalette::Active, QPalette::Base, QColor(50, 50, 50));
    
	//横线
	int t=50;
	painter.setPen(QPen(QBrush(Qt::darkGray), 3, Qt::SolidLine));
	painter.drawLine(t, 300, 550, 300);
	painter.drawLine(t, 350, 550, 350);
	painter.drawLine(t, 400, 550, 400);
	//竖线
	painter.drawLine(t, 300, t, 400);
	//painter.drawLine(250, 300, 250, 400);
	//painter.drawLine(350, 300, 350, 400);
	painter.drawLine(230, 300, 230, 400);
	painter.drawLine(390, 300, 390, 400);
    painter.drawLine(550, 300, 550, 400);
	painter.setBrush(Qt::gray);
	painter.drawRect(t,300,180,50);
    painter.setBrush(Qt::gray);
	painter.drawRect(230,300,160,50);
	painter.setBrush(Qt::gray);
	painter.drawRect(390,300,160,50);
	painter.setBrush(Qt::white);
	painter.drawRect(t,350,180,50);
	painter.setBrush(Qt::white);
	painter.drawRect(230,350,160,50);
	painter.setBrush(Qt::white);
	painter.drawRect(390,350,160,50);
	painter.setFont(QFont("time new roman", 16));
	//painter.setFont("Arial",16,QFont::Bold,true);
	painter.setPen(Qt::blue);
	painter.drawText(90,330, "参数名称");
	//painter.drawText(275,325, "标准差");
	painter.drawText(270,330, "数  值");
	painter.drawText(420,330,"百分位");
	//显示参数值itemMap.find(itemnumber).value()
	painter.drawText(100,380, QString("%1").arg(itemName));
	int pos = ui.horizontalSlider->value();
	float p = itemMap.find(itemnum).value()[pos-1];	
	QFont font("Arial",16,QFont::Bold,true);
	painter.setFont(font);
	painter.drawText(270,380, QString("%1").arg(p));
	painter.drawText(420,380, QString("%1").arg(pos));
	drawNormalCurve(painter);

    /*painter.setPen(Qt::red); 
    painter.drawRect(10, 10, 100, 400); 
    painter.setPen(QPen(Qt::green, 5)); 
    painter.setBrush(Qt::blue); 
    painter.drawEllipse(50, 150, 400, 200); */
}

void percentileDialog::drawNormalCurve(QPainter &painter)
{
	painter.setPen(QPen(Qt::red, 12, Qt::SolidLine));
	int pos = ui.horizontalSlider->value();
	for (int i = 0; i < 5*pos-4; i++)
	{
		painter.drawPoint(pVector[i]);
	}
}


void percentileDialog::on_horizontalSlider_valueChanged(int value)
{
	QString perStr = QString("%1%").arg(value);
	ui.precentLabel->setText(perStr);
}
