/********************************************************************************
** Form generated from reading ui file 'fit_widget.ui'
**
** Created: Sun Sep 2 12:29:29 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FIT_WIDGET_H
#define UI_FIT_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FitWidgetClass
{
public:
    QListWidget *xListWidget;
    QListWidget *yListWidget;
    QGraphicsView *graphicsView;
    QLabel *xLabel;
    QComboBox *xTableComboBox;
    QLabel *xLabel_2;
    QLabel *yLabfel;
    QLabel *label;
    QListWidget *rListWidget;
    QLineEdit *aLineEdit;
    QLineEdit *bLineEdit;
    QComboBox *yTableComboBox;
    QLabel *sizeLabel;
    QLabel *yLabel;
    QLineEdit *lineEdit;
    QLabel *xLabel_3;
    QLabel *xLabel_4;
    QLabel *label_2;

    void setupUi(QWidget *FitWidgetClass)
    {
        if (FitWidgetClass->objectName().isEmpty())
            FitWidgetClass->setObjectName(QString::fromUtf8("FitWidgetClass"));
        FitWidgetClass->resize(1003, 542);
        QFont font;
        font.setFamily(QString::fromUtf8("SimSun"));
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        FitWidgetClass->setFont(font);
        xListWidget = new QListWidget(FitWidgetClass);
        xListWidget->setObjectName(QString::fromUtf8("xListWidget"));
        xListWidget->setGeometry(QRect(20, 120, 131, 411));
        yListWidget = new QListWidget(FitWidgetClass);
        yListWidget->setObjectName(QString::fromUtf8("yListWidget"));
        yListWidget->setGeometry(QRect(820, 120, 131, 411));
        graphicsView = new QGraphicsView(FitWidgetClass);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(160, 120, 651, 411));
        xLabel = new QLabel(FitWidgetClass);
        xLabel->setObjectName(QString::fromUtf8("xLabel"));
        xLabel->setGeometry(QRect(290, 40, 111, 21));
        xLabel->setStyleSheet(QString::fromUtf8("color:red"));
        xTableComboBox = new QComboBox(FitWidgetClass);
        xTableComboBox->setObjectName(QString::fromUtf8("xTableComboBox"));
        xTableComboBox->setGeometry(QRect(20, 90, 131, 22));
        xLabel_2 = new QLabel(FitWidgetClass);
        xLabel_2->setObjectName(QString::fromUtf8("xLabel_2"));
        xLabel_2->setGeometry(QRect(240, 40, 31, 21));
        yLabfel = new QLabel(FitWidgetClass);
        yLabfel->setObjectName(QString::fromUtf8("yLabfel"));
        yLabfel->setGeometry(QRect(600, 40, 31, 16));
        label = new QLabel(FitWidgetClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(220, 60, 601, 21));
        rListWidget = new QListWidget(FitWidgetClass);
        rListWidget->setObjectName(QString::fromUtf8("rListWidget"));
        rListWidget->setGeometry(QRect(970, 90, 51, 81));
        aLineEdit = new QLineEdit(FitWidgetClass);
        aLineEdit->setObjectName(QString::fromUtf8("aLineEdit"));
        aLineEdit->setGeometry(QRect(432, 90, 151, 20));
        bLineEdit = new QLineEdit(FitWidgetClass);
        bLineEdit->setObjectName(QString::fromUtf8("bLineEdit"));
        bLineEdit->setGeometry(QRect(622, 90, 151, 20));
        yTableComboBox = new QComboBox(FitWidgetClass);
        yTableComboBox->setObjectName(QString::fromUtf8("yTableComboBox"));
        yTableComboBox->setGeometry(QRect(820, 90, 131, 22));
        sizeLabel = new QLabel(FitWidgetClass);
        sizeLabel->setObjectName(QString::fromUtf8("sizeLabel"));
        sizeLabel->setGeometry(QRect(430, 40, 131, 21));
        yLabel = new QLabel(FitWidgetClass);
        yLabel->setObjectName(QString::fromUtf8("yLabel"));
        yLabel->setGeometry(QRect(630, 40, 101, 21));
        yLabel->setStyleSheet(QString::fromUtf8("color:red"));
        lineEdit = new QLineEdit(FitWidgetClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(222, 90, 161, 20));
        xLabel_3 = new QLabel(FitWidgetClass);
        xLabel_3->setObjectName(QString::fromUtf8("xLabel_3"));
        xLabel_3->setGeometry(QRect(60, 50, 71, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(16);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        xLabel_3->setFont(font1);
        xLabel_4 = new QLabel(FitWidgetClass);
        xLabel_4->setObjectName(QString::fromUtf8("xLabel_4"));
        xLabel_4->setGeometry(QRect(860, 50, 71, 31));
        xLabel_4->setFont(font1);
        label_2 = new QLabel(FitWidgetClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 10, 451, 17));

        retranslateUi(FitWidgetClass);

        QMetaObject::connectSlotsByName(FitWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *FitWidgetClass)
    {
        FitWidgetClass->setWindowTitle(QApplication::translate("FitWidgetClass", "FitWidget", 0, QApplication::UnicodeUTF8));
        xLabel_2->setText(QApplication::translate("FitWidgetClass", "X\350\275\264:", 0, QApplication::UnicodeUTF8));
        yLabfel->setText(QApplication::translate("FitWidgetClass", "Y\350\275\264:", 0, QApplication::UnicodeUTF8));
        xLabel_3->setText(QApplication::translate("FitWidgetClass", "X \350\275\264", 0, QApplication::UnicodeUTF8));
        xLabel_4->setText(QApplication::translate("FitWidgetClass", "Y \350\275\264", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FitWidgetClass", "\345\212\237\350\203\275\346\217\220\347\244\272\357\274\232\345\205\210\351\200\211\346\213\251X\350\275\264\345\217\202\346\225\260\357\274\214\345\206\215\351\200\211\346\213\251Y\350\275\264\345\217\202\346\225\260\357\274\214\344\270\255\351\227\264\345\214\272\345\237\237\345\260\206\346\230\276\347\244\272\346\225\260\346\215\256\345\233\236\345\275\222\346\250\241\345\236\213\343\200\202", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(FitWidgetClass);
    } // retranslateUi

};

namespace Ui {
    class FitWidgetClass: public Ui_FitWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIT_WIDGET_H
