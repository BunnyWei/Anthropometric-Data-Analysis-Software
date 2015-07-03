/********************************************************************************
** Form generated from reading ui file 'chartwidget.ui'
**
** Created: Sun Sep 2 10:30:25 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CHARTWIDGET_H
#define UI_CHARTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ChartWidgetClass
{
public:
    QGraphicsView *graphicsView;

    void setupUi(QDialog *ChartWidgetClass)
    {
        if (ChartWidgetClass->objectName().isEmpty())
            ChartWidgetClass->setObjectName(QString::fromUtf8("ChartWidgetClass"));
        ChartWidgetClass->resize(762, 533);
        graphicsView = new QGraphicsView(ChartWidgetClass);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(30, 20, 711, 501));

        retranslateUi(ChartWidgetClass);

        QMetaObject::connectSlotsByName(ChartWidgetClass);
    } // setupUi

    void retranslateUi(QDialog *ChartWidgetClass)
    {
        ChartWidgetClass->setWindowTitle(QApplication::translate("ChartWidgetClass", "ChartWidget", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ChartWidgetClass);
    } // retranslateUi

};

namespace Ui {
    class ChartWidgetClass: public Ui_ChartWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARTWIDGET_H
