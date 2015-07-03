/********************************************************************************
** Form generated from reading ui file 'standardwidget.ui'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STANDARDWIDGET_H
#define UI_STANDARDWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StandardWidgetClass
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *numberLineEdit;
    QLabel *label_3;
    QComboBox *modelComboBox;
    QGraphicsView *graphicsView;
    QPushButton *searchBtn;
    QLabel *infoLabel;

    void setupUi(QWidget *StandardWidgetClass)
    {
        if (StandardWidgetClass->objectName().isEmpty())
            StandardWidgetClass->setObjectName(QString::fromUtf8("StandardWidgetClass"));
        StandardWidgetClass->resize(1032, 633);
        label = new QLabel(StandardWidgetClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 90, 261, 101));
        QFont font;
        font.setFamily(QString::fromUtf8("SimSun"));
        font.setPointSize(30);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        label->setFont(font);
        label_2 = new QLabel(StandardWidgetClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(290, 60, 111, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("SimSun"));
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        label_2->setFont(font1);
        numberLineEdit = new QLineEdit(StandardWidgetClass);
        numberLineEdit->setObjectName(QString::fromUtf8("numberLineEdit"));
        numberLineEdit->setGeometry(QRect(430, 60, 191, 31));
        numberLineEdit->setFont(font1);
        label_3 = new QLabel(StandardWidgetClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(290, 120, 111, 31));
        label_3->setFont(font1);
        modelComboBox = new QComboBox(StandardWidgetClass);
        modelComboBox->setObjectName(QString::fromUtf8("modelComboBox"));
        modelComboBox->setGeometry(QRect(430, 130, 191, 22));
        graphicsView = new QGraphicsView(StandardWidgetClass);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(680, 30, 171, 201));
        searchBtn = new QPushButton(StandardWidgetClass);
        searchBtn->setObjectName(QString::fromUtf8("searchBtn"));
        searchBtn->setGeometry(QRect(370, 180, 121, 31));
        searchBtn->setFont(font1);
        infoLabel = new QLabel(StandardWidgetClass);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));
        infoLabel->setGeometry(QRect(330, 250, 271, 371));

        retranslateUi(StandardWidgetClass);

        QMetaObject::connectSlotsByName(StandardWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *StandardWidgetClass)
    {
        StandardWidgetClass->setWindowTitle(QApplication::translate("StandardWidgetClass", "StandardWidget", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StandardWidgetClass", "\346\240\207\345\207\206\344\272\272\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("StandardWidgetClass", "\350\257\267\350\276\223\345\205\245\347\274\226\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("StandardWidgetClass", "\350\257\267\351\200\211\346\213\251\346\250\241\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        searchBtn->setText(QApplication::translate("StandardWidgetClass", "\346\237\245  \346\211\276", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(StandardWidgetClass);
    } // retranslateUi

};

namespace Ui {
    class StandardWidgetClass: public Ui_StandardWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STANDARDWIDGET_H
