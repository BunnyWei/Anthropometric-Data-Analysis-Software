/********************************************************************************
** Form generated from reading ui file 'percentiledialog.ui'
**
** Created: Sun Sep 2 12:25:04 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PERCENTILEDIALOG_H
#define UI_PERCENTILEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_percentileDialogClass
{
public:
    QSlider *horizontalSlider;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *precentLabel;

    void setupUi(QWidget *percentileDialogClass)
    {
        if (percentileDialogClass->objectName().isEmpty())
            percentileDialogClass->setObjectName(QString::fromUtf8("percentileDialogClass"));
        percentileDialogClass->resize(603, 478);
        percentileDialogClass->setAcceptDrops(true);
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/MainWindow/Resources/58.png")), QIcon::Normal, QIcon::Off);
        percentileDialogClass->setWindowIcon(icon);
        percentileDialogClass->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        horizontalSlider = new QSlider(percentileDialogClass);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(50, 250, 500, 20));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(percentileDialogClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(560, 250, 21, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("SimSun"));
        font.setPointSize(16);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        label_3->setFont(font);
        label_2 = new QLabel(percentileDialogClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 250, 16, 16));
        label_2->setFont(font);
        precentLabel = new QLabel(percentileDialogClass);
        precentLabel->setObjectName(QString::fromUtf8("precentLabel"));
        precentLabel->setGeometry(QRect(270, 270, 51, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("SimSun"));
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        precentLabel->setFont(font1);

        retranslateUi(percentileDialogClass);

        QMetaObject::connectSlotsByName(percentileDialogClass);
    } // setupUi

    void retranslateUi(QWidget *percentileDialogClass)
    {
        percentileDialogClass->setWindowTitle(QApplication::translate("percentileDialogClass", "\350\257\246\347\273\206\347\231\276\345\210\206\344\275\215", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("percentileDialogClass", "+", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("percentileDialogClass", "-", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(percentileDialogClass);
    } // retranslateUi

};

namespace Ui {
    class percentileDialogClass: public Ui_percentileDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERCENTILEDIALOG_H
