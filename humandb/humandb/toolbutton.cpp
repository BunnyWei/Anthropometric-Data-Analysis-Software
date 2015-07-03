#include <QtGui/QPixmap>
#include <QtGui/QBitmap>
#include "toolbutton.h"

ToolButton::ToolButton(QWidget *parent)
	: QToolButton(parent)
{
	ui.setupUi(this);

	 /*
    // ����Ƿǰ�ť�ಿ������ʹ�ô˶δ���
    QPalette p = palette();
    p.setBrush(QPalette::Button, QBrush(QPixmap("toolbutton.png")));
    setPalette(p);
    /*/
    // ����ǰ�ť�ಿ������ʹ�ô˶δ���
    setIcon(QIcon("enter.png"));
    setIconSize(QSize(100, 30));
    //*********************************/
    setMask(QBitmap("enter_mask.png"));
    setFixedSize(100, 30);

}

ToolButton::~ToolButton()
{

}
