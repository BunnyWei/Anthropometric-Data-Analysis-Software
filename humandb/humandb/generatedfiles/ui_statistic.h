/********************************************************************************
** Form generated from reading ui file 'statistic.ui'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STATISTIC_H
#define UI_STATISTIC_H

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
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatisticClass
{
public:
    QListWidget *listWidget;
    QComboBox *tableComboBox;
    QComboBox *socialComboBox;
    QLabel *percentLabel;
    QTableWidget *tableWidget;
    QPushButton *addButton;
    QListWidget *percentListWidget;
    QPushButton *statButton;
    QPushButton *selectAllButton;
    QPushButton *selectNoneButton;
    QLabel *itemLabel;
    QPushButton *clearButton;
    QLabel *showLabel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *fileNameLineEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QPushButton *openPushButton;
    QLineEdit *dirLineEdit;
    QPushButton *exportButton;

    void setupUi(QWidget *StatisticClass)
    {
        if (StatisticClass->objectName().isEmpty())
            StatisticClass->setObjectName(QString::fromUtf8("StatisticClass"));
        StatisticClass->resize(1253, 522);
        listWidget = new QListWidget(StatisticClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 50, 211, 401));
        tableComboBox = new QComboBox(StatisticClass);
        tableComboBox->setObjectName(QString::fromUtf8("tableComboBox"));
        tableComboBox->setGeometry(QRect(10, 10, 211, 31));
        socialComboBox = new QComboBox(StatisticClass);
        socialComboBox->setObjectName(QString::fromUtf8("socialComboBox"));
        socialComboBox->setGeometry(QRect(270, 10, 91, 31));
        percentLabel = new QLabel(StatisticClass);
        percentLabel->setObjectName(QString::fromUtf8("percentLabel"));
        percentLabel->setGeometry(QRect(500, 330, 41, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("SimSun"));
        font.setPointSize(16);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        percentLabel->setFont(font);
        tableWidget = new QTableWidget(StatisticClass);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(270, 50, 681, 401));
        addButton = new QPushButton(StatisticClass);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(500, 10, 51, 31));
        percentListWidget = new QListWidget(StatisticClass);
        percentListWidget->setObjectName(QString::fromUtf8("percentListWidget"));
        percentListWidget->setGeometry(QRect(1070, 80, 121, 521));
        statButton = new QPushButton(StatisticClass);
        statButton->setObjectName(QString::fromUtf8("statButton"));
        statButton->setGeometry(QRect(370, 10, 81, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("SimSun"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setUnderline(false);
        font1.setWeight(50);
        font1.setStrikeOut(false);
        statButton->setFont(font1);
        selectAllButton = new QPushButton(StatisticClass);
        selectAllButton->setObjectName(QString::fromUtf8("selectAllButton"));
        selectAllButton->setGeometry(QRect(10, 460, 81, 31));
        selectNoneButton = new QPushButton(StatisticClass);
        selectNoneButton->setObjectName(QString::fromUtf8("selectNoneButton"));
        selectNoneButton->setGeometry(QRect(110, 460, 81, 31));
        itemLabel = new QLabel(StatisticClass);
        itemLabel->setObjectName(QString::fromUtf8("itemLabel"));
        itemLabel->setGeometry(QRect(980, 50, 111, 21));
        clearButton = new QPushButton(StatisticClass);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(580, 10, 51, 31));
        showLabel = new QLabel(StatisticClass);
        showLabel->setObjectName(QString::fromUtf8("showLabel"));
        showLabel->setGeometry(QRect(850, 610, 81, 21));
        layoutWidget = new QWidget(StatisticClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(271, 460, 281, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setMargin(11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        fileNameLineEdit = new QLineEdit(layoutWidget);
        fileNameLineEdit->setObjectName(QString::fromUtf8("fileNameLineEdit"));

        horizontalLayout_2->addWidget(fileNameLineEdit);

        layoutWidget1 = new QWidget(StatisticClass);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(560, 460, 446, 27));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setMargin(11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        openPushButton = new QPushButton(layoutWidget1);
        openPushButton->setObjectName(QString::fromUtf8("openPushButton"));

        horizontalLayout_3->addWidget(openPushButton);

        dirLineEdit = new QLineEdit(layoutWidget1);
        dirLineEdit->setObjectName(QString::fromUtf8("dirLineEdit"));

        horizontalLayout_3->addWidget(dirLineEdit);

        exportButton = new QPushButton(layoutWidget1);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));
        exportButton->setIconSize(QSize(13, 13));

        horizontalLayout_3->addWidget(exportButton);

        exportButton->raise();
        label_5->raise();
        openPushButton->raise();
        dirLineEdit->raise();

        retranslateUi(StatisticClass);

        QMetaObject::connectSlotsByName(StatisticClass);
    } // setupUi

    void retranslateUi(QWidget *StatisticClass)
    {
        StatisticClass->setWindowTitle(QApplication::translate("StatisticClass", "Statistic", 0, QApplication::UnicodeUTF8));
        percentLabel->setText(QApplication::translate("StatisticClass", "0%", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("StatisticClass", "\346\267\273\345\212\240>>", 0, QApplication::UnicodeUTF8));
        statButton->setText(QApplication::translate("StatisticClass", "\347\273\237\350\256\241", 0, QApplication::UnicodeUTF8));
        selectAllButton->setText(QApplication::translate("StatisticClass", "\345\205\250\351\200\211", 0, QApplication::UnicodeUTF8));
        selectNoneButton->setText(QApplication::translate("StatisticClass", "\345\205\250\344\270\215\351\200\211", 0, QApplication::UnicodeUTF8));
        clearButton->setText(QApplication::translate("StatisticClass", "<< \346\270\205\347\251\272", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("StatisticClass", "\350\256\276\347\275\256\346\226\207\344\273\266\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("StatisticClass", "\351\200\211\346\213\251\345\257\274\345\207\272\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        openPushButton->setText(QApplication::translate("StatisticClass", "..\346\265\217\350\247\210", 0, QApplication::UnicodeUTF8));
        exportButton->setText(QApplication::translate("StatisticClass", "\345\257\274\345\207\272", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(StatisticClass);
    } // retranslateUi

};

namespace Ui {
    class StatisticClass: public Ui_StatisticClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTIC_H
