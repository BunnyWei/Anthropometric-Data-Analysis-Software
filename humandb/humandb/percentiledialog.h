#ifndef PERCENTILEDIALOG_H
#define PERCENTILEDIALOG_H

#include <QWidget>
#include <QtGui>
#include <QPainter>
#include <QVector>
#include <QFile>
#include <QPoint>
#include <QMessageBox>
#include <QTextStream>
#include "ui_percentiledialog.h"

typedef QVector<QPointF> pointsVessel;
const double PI = 3.1415926;

class percentileDialog : public QDialog
{
	Q_OBJECT

public:
	percentileDialog(QString itemnum, QString itemName, QMap<QString, QList<float> > &itemMap, QWidget *parent = 0);
	~percentileDialog();

protected:
    void paintEvent(QPaintEvent *event);

private:
	Ui::percentileDialogClass ui;

	double Normal(double u,double t,double x)

	{
		double temp;
		temp=exp((-1)*(x-u)*(x-u)/(2*t*t))/(sqrt(2*PI)*t);
		return temp;
	}

	QVector<QPoint> pVector;
	QMap<QString, QList<float> > itemMap;
	QString itemnum;
	QString itemName;
private slots:
	void on_horizontalSlider_valueChanged(int);
	void drawNormalCurve(QPainter &painter);
};

#endif // PERCENTILEDIALOG_H
