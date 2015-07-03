#include <QtGui/QPixmap>
#include <QtGui/QBitmap>
#include "shutdown.h"

Shutdown::Shutdown(QWidget *parent)
	: QToolButton(parent)
{
	ui.setupUi(this);


	setIcon(QIcon("shutdown.png"));
    setIconSize(QSize(100, 30));
    //*********************************/
    setMask(QBitmap("shutdown_mask.png"));
    setFixedSize(100, 30);

}

Shutdown::~Shutdown()
{

}
