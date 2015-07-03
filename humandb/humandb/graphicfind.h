#ifndef GRAPHICFIND_H
#define GRAPHICFIND_H

#include <QDialog>
#include "ui_graphicfind.h"

class GraphicFind : public QDialog
{
	Q_OBJECT

public:
	GraphicFind(QWidget *parent = 0);
	~GraphicFind();

private:
	Ui::GraphicFindClass ui;
};

#endif // GRAPHICFIND_H
