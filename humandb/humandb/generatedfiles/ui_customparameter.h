/********************************************************************************
** Form generated from reading ui file 'customparameter.ui'
**
** Created: Sun Sep 2 10:30:25 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CUSTOMPARAMETER_H
#define UI_CUSTOMPARAMETER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomParameterClass
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QComboBox *paraComboBox1;
    QComboBox *paraComboBox2;
    QComboBox *paraComboBox3;
    QListWidget *listWidget1;
    QListWidget *listWidget2;
    QListWidget *listWidget3;
    QComboBox *operateComboBox1;
    QComboBox *operateComboBox2;
    QLineEdit *defLineEdit;
    QPushButton *addBtn;
    QLabel *label_5;
    QLineEdit *measureLineEdit;
    QComboBox *typeComboBox;
    QLabel *label_6;
    QProgressBar *progressBar;
    QLabel *label_7;
    QLabel *label_3;
    QComboBox *bodyComboBox;
    QLabel *label_8;
    QLabel *label_4;
    QComboBox *groupComboBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_9;
    QComboBox *paraCountComboBox;

    void setupUi(QWidget *CustomParameterClass)
    {
        if (CustomParameterClass->objectName().isEmpty())
            CustomParameterClass->setObjectName(QString::fromUtf8("CustomParameterClass"));
        CustomParameterClass->resize(1087, 533);
        label = new QLabel(CustomParameterClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 150, 51, 16));
        lineEdit = new QLineEdit(CustomParameterClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(100, 150, 171, 20));
        label_2 = new QLabel(CustomParameterClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(280, 150, 54, 13));
        QFont font;
        font.setFamily(QString::fromUtf8("SimSun"));
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        label_2->setFont(font);
        paraComboBox1 = new QComboBox(CustomParameterClass);
        paraComboBox1->setObjectName(QString::fromUtf8("paraComboBox1"));
        paraComboBox1->setGeometry(QRect(340, 60, 141, 22));
        paraComboBox2 = new QComboBox(CustomParameterClass);
        paraComboBox2->setObjectName(QString::fromUtf8("paraComboBox2"));
        paraComboBox2->setGeometry(QRect(540, 60, 141, 22));
        paraComboBox3 = new QComboBox(CustomParameterClass);
        paraComboBox3->setObjectName(QString::fromUtf8("paraComboBox3"));
        paraComboBox3->setGeometry(QRect(740, 60, 141, 22));
        listWidget1 = new QListWidget(CustomParameterClass);
        listWidget1->setObjectName(QString::fromUtf8("listWidget1"));
        listWidget1->setGeometry(QRect(340, 90, 141, 381));
        listWidget2 = new QListWidget(CustomParameterClass);
        listWidget2->setObjectName(QString::fromUtf8("listWidget2"));
        listWidget2->setGeometry(QRect(540, 90, 141, 381));
        listWidget3 = new QListWidget(CustomParameterClass);
        listWidget3->setObjectName(QString::fromUtf8("listWidget3"));
        listWidget3->setGeometry(QRect(740, 90, 141, 381));
        operateComboBox1 = new QComboBox(CustomParameterClass);
        operateComboBox1->setObjectName(QString::fromUtf8("operateComboBox1"));
        operateComboBox1->setGeometry(QRect(490, 150, 41, 22));
        operateComboBox1->setFont(font);
        operateComboBox2 = new QComboBox(CustomParameterClass);
        operateComboBox2->setObjectName(QString::fromUtf8("operateComboBox2"));
        operateComboBox2->setGeometry(QRect(690, 150, 41, 22));
        operateComboBox2->setFont(font);
        defLineEdit = new QLineEdit(CustomParameterClass);
        defLineEdit->setObjectName(QString::fromUtf8("defLineEdit"));
        defLineEdit->setGeometry(QRect(100, 290, 171, 20));
        addBtn = new QPushButton(CustomParameterClass);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));
        addBtn->setGeometry(QRect(120, 440, 75, 23));
        label_5 = new QLabel(CustomParameterClass);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(41, 250, 77, 23));
        measureLineEdit = new QLineEdit(CustomParameterClass);
        measureLineEdit->setObjectName(QString::fromUtf8("measureLineEdit"));
        measureLineEdit->setGeometry(QRect(100, 320, 171, 20));
        typeComboBox = new QComboBox(CustomParameterClass);
        typeComboBox->setObjectName(QString::fromUtf8("typeComboBox"));
        typeComboBox->setGeometry(QRect(99, 250, 101, 23));
        label_6 = new QLabel(CustomParameterClass);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 290, 54, 13));
        progressBar = new QProgressBar(CustomParameterClass);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(50, 400, 231, 23));
        progressBar->setValue(0);
        label_7 = new QLabel(CustomParameterClass);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(40, 320, 54, 13));
        label_3 = new QLabel(CustomParameterClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 60, 261, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(16);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        label_3->setFont(font1);
        bodyComboBox = new QComboBox(CustomParameterClass);
        bodyComboBox->setObjectName(QString::fromUtf8("bodyComboBox"));
        bodyComboBox->setGeometry(QRect(100, 360, 91, 22));
        label_8 = new QLabel(CustomParameterClass);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(40, 360, 54, 13));
        label_4 = new QLabel(CustomParameterClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(41, 210, 77, 23));
        groupComboBox = new QComboBox(CustomParameterClass);
        groupComboBox->setObjectName(QString::fromUtf8("groupComboBox"));
        groupComboBox->setGeometry(QRect(99, 210, 101, 23));
        layoutWidget = new QWidget(CustomParameterClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(341, 20, 372, 35));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setMargin(11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("SimSun"));
        font2.setPointSize(14);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(50);
        font2.setStrikeOut(false);
        label_9->setFont(font2);

        horizontalLayout->addWidget(label_9);

        paraCountComboBox = new QComboBox(layoutWidget);
        paraCountComboBox->setObjectName(QString::fromUtf8("paraCountComboBox"));
        paraCountComboBox->setFont(font2);

        horizontalLayout->addWidget(paraCountComboBox);


        retranslateUi(CustomParameterClass);

        QMetaObject::connectSlotsByName(CustomParameterClass);
    } // setupUi

    void retranslateUi(QWidget *CustomParameterClass)
    {
        CustomParameterClass->setWindowTitle(QApplication::translate("CustomParameterClass", "CustomParameter", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CustomParameterClass", "\345\217\202\346\225\260\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CustomParameterClass", " =", 0, QApplication::UnicodeUTF8));
        addBtn->setText(QApplication::translate("CustomParameterClass", "\346\267\273  \345\212\240", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("CustomParameterClass", "\347\261\273  \345\236\213:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("CustomParameterClass", "\345\256\232  \344\271\211:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("CustomParameterClass", "\346\265\213\351\207\217\346\226\271\346\263\225:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CustomParameterClass", "\346\267\273\345\212\240\345\217\202\346\225\260\347\232\204\347\233\270\345\205\263\344\277\241\346\201\257:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("CustomParameterClass", "\346\211\200\345\261\236\351\203\250\344\275\215:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("CustomParameterClass", "\345\210\206  \347\273\204:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("CustomParameterClass", "\350\257\267\351\200\211\346\213\251\347\273\204\345\220\210\345\217\202\346\225\260\347\232\204\344\270\252\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CustomParameterClass);
    } // retranslateUi

};

namespace Ui {
    class CustomParameterClass: public Ui_CustomParameterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMPARAMETER_H
