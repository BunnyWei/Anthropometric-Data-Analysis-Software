#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	QPixmap pm("data.png");
    QGraphicsScene *gs = new QGraphicsScene();
    gs->addPixmap(pm);

	ui.graphicsView->setStyleSheet("padding-bottom:10px");
	ui.graphicsView->setScene(gs);
}

ChartWidget::~ChartWidget()
{

}
