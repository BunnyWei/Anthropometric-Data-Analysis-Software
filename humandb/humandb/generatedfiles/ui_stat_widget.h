/********************************************************************************
** Form generated from reading ui file 'stat_widget.ui'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_STAT_WIDGET_H
#define UI_STAT_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatWidgetClass
{
public:
    QPushButton *statButton;
    QLabel *showLabel;
    QLabel *label_12;
    QFrame *frame;
    QListWidget *listWidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *selectAllButton;
    QPushButton *selectNoneButton;
    QSplitter *splitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *groupComboBox;
    QComboBox *typeComboBox;
    QPushButton *okButton;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLineEdit *fileNameLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QPushButton *openPushButton;
    QLineEdit *dirLineEdit;
    QPushButton *exportButton;
    QTableWidget *tableWidget;
    QLabel *label_7;
    QComboBox *districtComboBox;
    QComboBox *jiguanComboBox;
    QLabel *label_8;
    QLabel *label_9;
    QComboBox *bingzhongComboBox;
    QLabel *label_10;
    QComboBox *wenhuaComboBox;
    QLabel *junxianLabel;
    QComboBox *junxianComboBox;
    QLabel *label_count;
    QLabel *label_3;
    QComboBox *percentileComboBox;

    void setupUi(QWidget *StatWidgetClass)
    {
        if (StatWidgetClass->objectName().isEmpty())
            StatWidgetClass->setObjectName(QString::fromUtf8("StatWidgetClass"));
        StatWidgetClass->resize(1124, 539);
        statButton = new QPushButton(StatWidgetClass);
        statButton->setObjectName(QString::fromUtf8("statButton"));
        statButton->setGeometry(QRect(220, 240, 51, 23));
        statButton->setMaximumSize(QSize(100, 16777215));
        showLabel = new QLabel(StatWidgetClass);
        showLabel->setObjectName(QString::fromUtf8("showLabel"));
        showLabel->setGeometry(QRect(980, 470, 81, 21));
        label_12 = new QLabel(StatWidgetClass);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(310, 23, 16, 29));
        frame = new QFrame(StatWidgetClass);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, -10, 211, 501));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        listWidget = new QListWidget(frame);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 70, 201, 381));
        layoutWidget = new QWidget(frame);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(3, 10, 120, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setMargin(11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        layoutWidget1 = new QWidget(frame);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 460, 158, 27));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setMargin(11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        selectAllButton = new QPushButton(layoutWidget1);
        selectAllButton->setObjectName(QString::fromUtf8("selectAllButton"));

        horizontalLayout_5->addWidget(selectAllButton);

        selectNoneButton = new QPushButton(layoutWidget1);
        selectNoneButton->setObjectName(QString::fromUtf8("selectNoneButton"));

        horizontalLayout_5->addWidget(selectNoneButton);

        splitter = new QSplitter(frame);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(100, 96, 9, 5));
        splitter->setOrientation(Qt::Horizontal);
        verticalLayoutWidget = new QWidget(splitter);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        splitter->addWidget(verticalLayoutWidget);
        verticalLayoutWidget_2 = new QWidget(splitter);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setMargin(11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        splitter->addWidget(verticalLayoutWidget_2);
        groupComboBox = new QComboBox(frame);
        groupComboBox->setObjectName(QString::fromUtf8("groupComboBox"));
        groupComboBox->setGeometry(QRect(2, 36, 71, 21));
        typeComboBox = new QComboBox(frame);
        typeComboBox->setObjectName(QString::fromUtf8("typeComboBox"));
        typeComboBox->setGeometry(QRect(79, 36, 81, 21));
        okButton = new QPushButton(frame);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(160, 35, 43, 23));
        okButton->setMaximumSize(QSize(43, 16777215));
        layoutWidget2 = new QWidget(StatWidgetClass);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(271, 450, 789, 29));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setMargin(11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(layoutWidget2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        fileNameLineEdit = new QLineEdit(layoutWidget2);
        fileNameLineEdit->setObjectName(QString::fromUtf8("fileNameLineEdit"));

        horizontalLayout_2->addWidget(fileNameLineEdit);


        horizontalLayout_7->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        openPushButton = new QPushButton(layoutWidget2);
        openPushButton->setObjectName(QString::fromUtf8("openPushButton"));

        horizontalLayout_3->addWidget(openPushButton);

        dirLineEdit = new QLineEdit(layoutWidget2);
        dirLineEdit->setObjectName(QString::fromUtf8("dirLineEdit"));

        horizontalLayout_3->addWidget(dirLineEdit);

        exportButton = new QPushButton(layoutWidget2);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));
        exportButton->setIconSize(QSize(13, 13));

        horizontalLayout_3->addWidget(exportButton);


        horizontalLayout_7->addLayout(horizontalLayout_3);

        tableWidget = new QTableWidget(StatWidgetClass);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(271, 60, 789, 381));
        label_7 = new QLabel(StatWidgetClass);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(272, 25, 45, 21));
        districtComboBox = new QComboBox(StatWidgetClass);
        districtComboBox->setObjectName(QString::fromUtf8("districtComboBox"));
        districtComboBox->setGeometry(QRect(300, 25, 69, 21));
        jiguanComboBox = new QComboBox(StatWidgetClass);
        jiguanComboBox->setObjectName(QString::fromUtf8("jiguanComboBox"));
        jiguanComboBox->setGeometry(QRect(410, 25, 69, 21));
        label_8 = new QLabel(StatWidgetClass);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(378, 25, 44, 21));
        label_9 = new QLabel(StatWidgetClass);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(490, 25, 45, 21));
        bingzhongComboBox = new QComboBox(StatWidgetClass);
        bingzhongComboBox->setObjectName(QString::fromUtf8("bingzhongComboBox"));
        bingzhongComboBox->setGeometry(QRect(520, 25, 69, 21));
        label_10 = new QLabel(StatWidgetClass);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(599, 25, 44, 21));
        wenhuaComboBox = new QComboBox(StatWidgetClass);
        wenhuaComboBox->setObjectName(QString::fromUtf8("wenhuaComboBox"));
        wenhuaComboBox->setGeometry(QRect(630, 25, 69, 21));
        junxianLabel = new QLabel(StatWidgetClass);
        junxianLabel->setObjectName(QString::fromUtf8("junxianLabel"));
        junxianLabel->setGeometry(QRect(714, 25, 45, 21));
        junxianComboBox = new QComboBox(StatWidgetClass);
        junxianComboBox->setObjectName(QString::fromUtf8("junxianComboBox"));
        junxianComboBox->setGeometry(QRect(740, 25, 69, 21));
        label_count = new QLabel(StatWidgetClass);
        label_count->setObjectName(QString::fromUtf8("label_count"));
        label_count->setGeometry(QRect(820, 20, 101, 21));
        label_3 = new QLabel(StatWidgetClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(934, 26, 61, 21));
        percentileComboBox = new QComboBox(StatWidgetClass);
        percentileComboBox->setObjectName(QString::fromUtf8("percentileComboBox"));
        percentileComboBox->setGeometry(QRect(1001, 26, 51, 21));

        retranslateUi(StatWidgetClass);

        QMetaObject::connectSlotsByName(StatWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *StatWidgetClass)
    {
        StatWidgetClass->setWindowTitle(QApplication::translate("StatWidgetClass", "StatWidget", 0, QApplication::UnicodeUTF8));
        statButton->setText(QApplication::translate("StatWidgetClass", "\347\273\237\350\256\241>>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StatWidgetClass", "\345\210\206\347\273\204:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("StatWidgetClass", "\347\261\273\345\210\253\357\274\232", 0, QApplication::UnicodeUTF8));
        selectAllButton->setText(QApplication::translate("StatWidgetClass", "\345\205\250\351\200\211", 0, QApplication::UnicodeUTF8));
        selectNoneButton->setText(QApplication::translate("StatWidgetClass", "\345\205\250\344\270\215\351\200\211", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("StatWidgetClass", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("StatWidgetClass", "\350\256\276\347\275\256\346\226\207\344\273\266\345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("StatWidgetClass", "\351\200\211\346\213\251\345\257\274\345\207\272\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        openPushButton->setText(QApplication::translate("StatWidgetClass", "..\346\265\217\350\247\210", 0, QApplication::UnicodeUTF8));
        exportButton->setText(QApplication::translate("StatWidgetClass", "\345\257\274\345\207\272", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("StatWidgetClass", "\345\234\260\345\237\237", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("StatWidgetClass", "\347\261\215\350\264\257", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("StatWidgetClass", "\345\205\265\347\247\215", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("StatWidgetClass", "\345\255\246\345\216\206", 0, QApplication::UnicodeUTF8));
        junxianLabel->setText(QApplication::translate("StatWidgetClass", "\345\206\233\350\241\224", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("StatWidgetClass", "\347\231\276\345\210\206\344\275\215\357\274\232P", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(StatWidgetClass);
    } // retranslateUi

};

namespace Ui {
    class StatWidgetClass: public Ui_StatWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAT_WIDGET_H
