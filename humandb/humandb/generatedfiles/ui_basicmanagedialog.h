/********************************************************************************
** Form generated from reading ui file 'basicmanagedialog.ui'
**
** Created: Sun Sep 2 10:30:25 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_BASICMANAGEDIALOG_H
#define UI_BASICMANAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BasicManageDialogClass
{
public:
    QPushButton *pushButton;
    QListWidget *listWidget;
    QProgressBar *progressBar;

    void setupUi(QWidget *BasicManageDialogClass)
    {
        if (BasicManageDialogClass->objectName().isEmpty())
            BasicManageDialogClass->setObjectName(QString::fromUtf8("BasicManageDialogClass"));
        BasicManageDialogClass->resize(655, 587);
        pushButton = new QPushButton(BasicManageDialogClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(220, 20, 111, 41));
        listWidget = new QListWidget(BasicManageDialogClass);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(90, 120, 411, 421));
        progressBar = new QProgressBar(BasicManageDialogClass);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(90, 80, 441, 23));
        progressBar->setValue(0);

        retranslateUi(BasicManageDialogClass);

        QMetaObject::connectSlotsByName(BasicManageDialogClass);
    } // setupUi

    void retranslateUi(QWidget *BasicManageDialogClass)
    {
        BasicManageDialogClass->setWindowTitle(QApplication::translate("BasicManageDialogClass", "BasicManageDialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("BasicManageDialogClass", "\347\224\237\346\210\220\347\273\237\350\256\241\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(BasicManageDialogClass);
    } // retranslateUi

};

namespace Ui {
    class BasicManageDialogClass: public Ui_BasicManageDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASICMANAGEDIALOG_H
