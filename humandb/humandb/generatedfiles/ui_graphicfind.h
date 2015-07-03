/********************************************************************************
** Form generated from reading ui file 'graphicfind.ui'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_GRAPHICFIND_H
#define UI_GRAPHICFIND_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_GraphicFindClass
{
public:
    QGraphicsView *graphicsView;
    QListWidget *listWidget;
    QLabel *label;
    QPushButton *okBtn;

    void setupUi(QDialog *GraphicFindClass)
    {
        if (GraphicFindClass->objectName().isEmpty())
            GraphicFindClass->setObjectName(QString::fromUtf8("GraphicFindClass"));
        GraphicFindClass->resize(779, 482);
        graphicsView = new QGraphicsView(GraphicFindClass);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(40, 60, 411, 341));
        listWidget = new QListWidget(GraphicFindClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(530, 60, 211, 351));
        label = new QLabel(GraphicFindClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(540, 40, 101, 16));
        okBtn = new QPushButton(GraphicFindClass);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setGeometry(QRect(590, 440, 75, 23));

        retranslateUi(GraphicFindClass);

        QMetaObject::connectSlotsByName(GraphicFindClass);
    } // setupUi

    void retranslateUi(QDialog *GraphicFindClass)
    {
        GraphicFindClass->setWindowTitle(QApplication::translate("GraphicFindClass", "GraphicFind", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GraphicFindClass", "\351\200\211\346\213\251\345\217\202\346\225\260\351\242\204\350\247\210\357\274\232", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("GraphicFindClass", "\347\241\256 \345\256\232", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(GraphicFindClass);
    } // retranslateUi

};

namespace Ui {
    class GraphicFindClass: public Ui_GraphicFindClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICFIND_H
