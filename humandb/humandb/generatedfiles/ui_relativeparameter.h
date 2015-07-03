/********************************************************************************
** Form generated from reading ui file 'relativeparameter.ui'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_RELATIVEPARAMETER_H
#define UI_RELATIVEPARAMETER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RelativeParameterClass
{
public:
    QPushButton *staBtn;
    QTableWidget *tableWidget;
    QLabel *label_8;
    QGroupBox *groupBox;
    QComboBox *tableComboBox;
    QLabel *label_5;
    QListWidget *listWidget;
    QGroupBox *groupBox_2;
    QComboBox *groupComboBox;
    QComboBox *parameterComboBox;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *typeComboBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *minLineEdit;
    QLabel *label;
    QLineEdit *maxLineEdit;
    QLabel *label_4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QLineEdit *centileLineEdit;

    void setupUi(QWidget *RelativeParameterClass)
    {
        if (RelativeParameterClass->objectName().isEmpty())
            RelativeParameterClass->setObjectName(QString::fromUtf8("RelativeParameterClass"));
        RelativeParameterClass->resize(1077, 566);
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        RelativeParameterClass->setFont(font);
        staBtn = new QPushButton(RelativeParameterClass);
        staBtn->setObjectName(QString::fromUtf8("staBtn"));
        staBtn->setGeometry(QRect(240, 330, 51, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        staBtn->setFont(font1);
        tableWidget = new QTableWidget(RelativeParameterClass);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(300, 150, 711, 381));
        label_8 = new QLabel(RelativeParameterClass);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 10, 551, 17));
        QFont font2;
        font2.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font2.setPointSize(11);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setUnderline(false);
        font2.setWeight(50);
        font2.setStrikeOut(false);
        label_8->setFont(font2);
        groupBox = new QGroupBox(RelativeParameterClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 140, 201, 401));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Agency FB"));
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setUnderline(false);
        font3.setWeight(75);
        font3.setStrikeOut(false);
        groupBox->setFont(font3);
        tableComboBox = new QComboBox(groupBox);
        tableComboBox->setObjectName(QString::fromUtf8("tableComboBox"));
        tableComboBox->setGeometry(QRect(79, 31, 111, 23));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Agency FB"));
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setUnderline(false);
        font4.setWeight(50);
        font4.setStrikeOut(false);
        tableComboBox->setFont(font4);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(11, 31, 71, 23));
        label_5->setFont(font4);
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 70, 181, 331));
        groupBox_2 = new QGroupBox(RelativeParameterClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 40, 851, 101));
        QFont font5;
        font5.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font5.setPointSize(10);
        font5.setBold(true);
        font5.setItalic(false);
        font5.setUnderline(false);
        font5.setWeight(75);
        font5.setStrikeOut(false);
        groupBox_2->setFont(font5);
        groupComboBox = new QComboBox(groupBox_2);
        groupComboBox->setObjectName(QString::fromUtf8("groupComboBox"));
        groupComboBox->setGeometry(QRect(80, 31, 112, 23));
        groupComboBox->setFont(font1);
        parameterComboBox = new QComboBox(groupBox_2);
        parameterComboBox->setObjectName(QString::fromUtf8("parameterComboBox"));
        parameterComboBox->setGeometry(QRect(80, 60, 112, 23));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Felix Titling"));
        font6.setPointSize(10);
        font6.setBold(false);
        font6.setItalic(false);
        font6.setUnderline(false);
        font6.setWeight(50);
        font6.setStrikeOut(false);
        parameterComboBox->setFont(font6);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(13, 31, 65, 21));
        label_2->setFont(font1);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(13, 60, 65, 21));
        label_3->setFont(font1);
        typeComboBox = new QComboBox(groupBox_2);
        typeComboBox->setObjectName(QString::fromUtf8("typeComboBox"));
        typeComboBox->setGeometry(QRect(380, 50, 112, 23));
        typeComboBox->setFont(font1);
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(510, 30, 251, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setMargin(11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);

        horizontalLayout_2->addWidget(label_6);

        minLineEdit = new QLineEdit(layoutWidget);
        minLineEdit->setObjectName(QString::fromUtf8("minLineEdit"));
        minLineEdit->setFont(font1);

        horizontalLayout_2->addWidget(minLineEdit);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        maxLineEdit = new QLineEdit(layoutWidget);
        maxLineEdit->setObjectName(QString::fromUtf8("maxLineEdit"));
        maxLineEdit->setFont(font1);

        horizontalLayout_2->addWidget(maxLineEdit);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(283, 50, 91, 21));
        label_4->setFont(font1);
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(510, 70, 151, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setMargin(11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font1);

        horizontalLayout->addWidget(label_7);

        centileLineEdit = new QLineEdit(layoutWidget1);
        centileLineEdit->setObjectName(QString::fromUtf8("centileLineEdit"));
        centileLineEdit->setFont(font1);

        horizontalLayout->addWidget(centileLineEdit);


        retranslateUi(RelativeParameterClass);

        QMetaObject::connectSlotsByName(RelativeParameterClass);
    } // setupUi

    void retranslateUi(QWidget *RelativeParameterClass)
    {
        RelativeParameterClass->setWindowTitle(QApplication::translate("RelativeParameterClass", "RelativeParameter", 0, QApplication::UnicodeUTF8));
        staBtn->setText(QApplication::translate("RelativeParameterClass", "\347\273\237\350\256\241>>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("RelativeParameterClass", "\345\212\237\350\203\275\346\217\220\347\244\272\357\274\232\346\240\271\346\215\256\346\237\220\344\270\252\345\217\202\346\225\260\347\232\204\350\214\203\345\233\264\346\210\226\350\200\205\347\231\276\345\210\206\344\275\215\346\225\260\346\237\245\350\257\242\345\205\266\344\273\226\345\217\202\346\225\260\347\232\204\347\273\237\350\256\241\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("RelativeParameterClass", "\351\200\211\346\213\251\345\276\205\346\237\245\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("RelativeParameterClass", "\351\200\211\346\213\251\345\210\206\347\273\204\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("RelativeParameterClass", "\351\200\211\346\213\251\351\231\220\345\210\266\346\235\241\344\273\266", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("RelativeParameterClass", "\351\200\211\346\213\251\345\210\206\347\273\204\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("RelativeParameterClass", "\351\200\211\346\213\251\345\217\202\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("RelativeParameterClass", "\345\217\202\346\225\260\350\214\203\345\233\264\357\274\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RelativeParameterClass", "----", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("RelativeParameterClass", "\351\200\211\346\213\251\346\237\245\350\257\242\347\261\273\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("RelativeParameterClass", "\347\231\276 \345\210\206 \344\275\215\357\274\232P", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(RelativeParameterClass);
    } // retranslateUi

};

namespace Ui {
    class RelativeParameterClass: public Ui_RelativeParameterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RELATIVEPARAMETER_H
