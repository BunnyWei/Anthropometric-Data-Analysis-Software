#include "perbutton.h"

PerButton::PerButton(const QString &itemnumber, const QString & text, QWidget *parent)
	: QPushButton(text, parent)
{
	this->itemnumber = itemnumber;
	this->itemName = text;
}

PerButton::~PerButton()
{

}
void PerButton::showItem()
{
	emit clickItem(itemnumber, itemName);
}
