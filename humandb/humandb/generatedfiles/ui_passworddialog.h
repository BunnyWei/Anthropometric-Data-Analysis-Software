/********************************************************************************
** Form generated from reading ui file 'passworddialog.ui'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PASSWORDDIALOG_H
#define UI_PASSWORDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PasswordDialogClass
{
public:
    QLineEdit *pwdLineEdit;
    QLabel *label;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *PasswordDialogClass)
    {
        if (PasswordDialogClass->objectName().isEmpty())
            PasswordDialogClass->setObjectName(QString::fromUtf8("PasswordDialogClass"));
        PasswordDialogClass->resize(400, 300);
        pwdLineEdit = new QLineEdit(PasswordDialogClass);
        pwdLineEdit->setObjectName(QString::fromUtf8("pwdLineEdit"));
        pwdLineEdit->setGeometry(QRect(152, 120, 141, 20));
        pwdLineEdit->setEchoMode(QLineEdit::Password);
        label = new QLabel(PasswordDialogClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 120, 81, 16));
        okButton = new QPushButton(PasswordDialogClass);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(90, 210, 75, 23));
        cancelButton = new QPushButton(PasswordDialogClass);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(210, 210, 75, 23));

        retranslateUi(PasswordDialogClass);
        QObject::connect(cancelButton, SIGNAL(clicked()), PasswordDialogClass, SLOT(reject()));
        QObject::connect(okButton, SIGNAL(clicked()), PasswordDialogClass, SLOT(close()));

        QMetaObject::connectSlotsByName(PasswordDialogClass);
    } // setupUi

    void retranslateUi(QDialog *PasswordDialogClass)
    {
        PasswordDialogClass->setWindowTitle(QApplication::translate("PasswordDialogClass", "PasswordDialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PasswordDialogClass", "\350\257\267\350\276\223\345\205\245\345\217\243\344\273\244\357\274\232", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("PasswordDialogClass", "\347\241\256 \345\256\232", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("PasswordDialogClass", "\345\217\226 \346\266\210", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(PasswordDialogClass);
    } // retranslateUi

};

namespace Ui {
    class PasswordDialogClass: public Ui_PasswordDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSWORDDIALOG_H
