/********************************************************************************
** Form generated from reading ui file 'import_widget.ui'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_IMPORT_WIDGET_H
#define UI_IMPORT_WIDGET_H

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
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImportWidgetClass
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *fileNameLineEdit;
    QPushButton *openButton;
    QPushButton *importButton;
    QProgressBar *progressBar;
    QComboBox *dataComboBox;
    QLabel *statusLabel;
    QLabel *countLabel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QRadioButton *excelRadioButton;
    QRadioButton *csvRadioButton;
    QLabel *itemCountLabel;
    QGroupBox *groupBox_3;
    QProgressBar *modelProgressBar;
    QPushButton *importModelBtn;
    QGroupBox *groupBox_2;
    QPushButton *imPhotoBtn;
    QProgressBar *photoProgressBar;
    QPushButton *pushButton;
    QProgressBar *statisticProgressBar;
    QListWidget *listWidget;
    QPushButton *VisiblePushButton;

    void setupUi(QWidget *ImportWidgetClass)
    {
        if (ImportWidgetClass->objectName().isEmpty())
            ImportWidgetClass->setObjectName(QString::fromUtf8("ImportWidgetClass"));
        ImportWidgetClass->resize(1015, 462);
        groupBox = new QGroupBox(ImportWidgetClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 20, 411, 251));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 30, 41, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 30, 61, 21));
        fileNameLineEdit = new QLineEdit(groupBox);
        fileNameLineEdit->setObjectName(QString::fromUtf8("fileNameLineEdit"));
        fileNameLineEdit->setGeometry(QRect(80, 140, 241, 20));
        openButton = new QPushButton(groupBox);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setGeometry(QRect(20, 140, 51, 23));
        importButton = new QPushButton(groupBox);
        importButton->setObjectName(QString::fromUtf8("importButton"));
        importButton->setGeometry(QRect(20, 180, 75, 23));
        progressBar = new QProgressBar(groupBox);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(100, 180, 221, 23));
        progressBar->setValue(0);
        dataComboBox = new QComboBox(groupBox);
        dataComboBox->setObjectName(QString::fromUtf8("dataComboBox"));
        dataComboBox->setGeometry(QRect(90, 30, 151, 22));
        statusLabel = new QLabel(groupBox);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(40, 410, 291, 41));
        statusLabel->setTextFormat(Qt::PlainText);
        countLabel = new QLabel(groupBox);
        countLabel->setObjectName(QString::fromUtf8("countLabel"));
        countLabel->setGeometry(QRect(20, 70, 221, 17));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 100, 221, 23));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setMargin(11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        excelRadioButton = new QRadioButton(layoutWidget);
        excelRadioButton->setObjectName(QString::fromUtf8("excelRadioButton"));

        horizontalLayout->addWidget(excelRadioButton);

        csvRadioButton = new QRadioButton(layoutWidget);
        csvRadioButton->setObjectName(QString::fromUtf8("csvRadioButton"));

        horizontalLayout->addWidget(csvRadioButton);

        itemCountLabel = new QLabel(groupBox);
        itemCountLabel->setObjectName(QString::fromUtf8("itemCountLabel"));
        itemCountLabel->setGeometry(QRect(30, 220, 231, 17));
        groupBox_3 = new QGroupBox(ImportWidgetClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(470, 20, 421, 121));
        modelProgressBar = new QProgressBar(groupBox_3);
        modelProgressBar->setObjectName(QString::fromUtf8("modelProgressBar"));
        modelProgressBar->setGeometry(QRect(60, 70, 341, 23));
        modelProgressBar->setValue(0);
        importModelBtn = new QPushButton(groupBox_3);
        importModelBtn->setObjectName(QString::fromUtf8("importModelBtn"));
        importModelBtn->setGeometry(QRect(160, 30, 101, 23));
        groupBox_2 = new QGroupBox(ImportWidgetClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 290, 411, 121));
        imPhotoBtn = new QPushButton(groupBox_2);
        imPhotoBtn->setObjectName(QString::fromUtf8("imPhotoBtn"));
        imPhotoBtn->setGeometry(QRect(120, 30, 121, 23));
        photoProgressBar = new QProgressBar(groupBox_2);
        photoProgressBar->setObjectName(QString::fromUtf8("photoProgressBar"));
        photoProgressBar->setGeometry(QRect(30, 70, 351, 23));
        photoProgressBar->setValue(0);
        pushButton = new QPushButton(ImportWidgetClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(630, 150, 111, 41));
        statisticProgressBar = new QProgressBar(ImportWidgetClass);
        statisticProgressBar->setObjectName(QString::fromUtf8("statisticProgressBar"));
        statisticProgressBar->setGeometry(QRect(500, 200, 441, 23));
        statisticProgressBar->setValue(0);
        listWidget = new QListWidget(ImportWidgetClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(500, 260, 411, 161));
        VisiblePushButton = new QPushButton(ImportWidgetClass);
        VisiblePushButton->setObjectName(QString::fromUtf8("VisiblePushButton"));
        VisiblePushButton->setGeometry(QRect(500, 227, 101, 31));

        retranslateUi(ImportWidgetClass);

        QMetaObject::connectSlotsByName(ImportWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *ImportWidgetClass)
    {
        ImportWidgetClass->setWindowTitle(QApplication::translate("ImportWidgetClass", "ImportWidget", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ImportWidgetClass", "\346\265\213\351\207\217\346\225\260\346\215\256\345\257\274\345\205\245", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ImportWidgetClass", "\345\257\274\345\205\245\351\241\271\347\233\256:", 0, QApplication::UnicodeUTF8));
        openButton->setText(QApplication::translate("ImportWidgetClass", "\346\265\217\350\247\210...", 0, QApplication::UnicodeUTF8));
        importButton->setText(QApplication::translate("ImportWidgetClass", "\345\274\200\345\247\213\345\257\274\345\205\245", 0, QApplication::UnicodeUTF8));
        countLabel->setText(QApplication::translate("ImportWidgetClass", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ImportWidgetClass", "\346\240\274\345\274\217", 0, QApplication::UnicodeUTF8));
        excelRadioButton->setText(QApplication::translate("ImportWidgetClass", "Excel", 0, QApplication::UnicodeUTF8));
        csvRadioButton->setText(QApplication::translate("ImportWidgetClass", "CSV", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("ImportWidgetClass", "\344\270\211\347\273\264\347\202\271\344\272\221\346\250\241\345\236\213\345\257\274\345\205\245", 0, QApplication::UnicodeUTF8));
        importModelBtn->setText(QApplication::translate("ImportWidgetClass", "\345\257\274\345\205\245\346\250\241\345\236\213...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ImportWidgetClass", "\347\205\247\347\211\207\345\257\274\345\205\245", 0, QApplication::UnicodeUTF8));
        imPhotoBtn->setText(QApplication::translate("ImportWidgetClass", "\345\257\274\345\205\245\347\205\247\347\211\207...", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ImportWidgetClass", "\347\224\237\346\210\220\347\273\237\350\256\241\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        VisiblePushButton->setText(QApplication::translate("ImportWidgetClass", "\346\230\276\347\244\272\350\257\246\347\273\206\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ImportWidgetClass);
    } // retranslateUi

};

namespace Ui {
    class ImportWidgetClass: public Ui_ImportWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORT_WIDGET_H
