#include <QtGui/QPixmap>
#include <QtGui/QBitmap>
#include "toolbutton.h"

ToolButton::ToolButton(QWidget *parent)
	: QToolButton(parent)
{
	ui.setupUi(this);

	 /*
    // 如果是非按钮类部件，则使用此段代码
    QPalette p = palette();
    p.setBrush(QPalette::Button, QBrush(QPixmap("toolbutton.png")));
    setPalette(p);
    /*/
    // 如果是按钮类部件，则使用此段代码
    setIcon(QIcon("enter.png"));
    setIconSize(QSize(100, 30));
    //*********************************/
    setMask(QBitmap("enter_mask.png"));
    setFixedSize(100, 30);

}

ToolButton::~ToolButton()
{

}
