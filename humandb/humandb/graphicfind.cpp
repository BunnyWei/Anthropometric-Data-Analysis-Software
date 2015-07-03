#include "graphicfind.h"

GraphicFind::GraphicFind(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	QPixmap pm("abc.png");
    QGraphicsScene *gs = new QGraphicsScene();
    gs->addPixmap(pm);

	ui.graphicsView->setStyleSheet("padding-bottom:10px");
	ui.graphicsView->setScene(gs);
}

GraphicFind::~GraphicFind()
{

}
