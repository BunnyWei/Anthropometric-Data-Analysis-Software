/********************************************************************************
** Form generated from reading ui file 'modifypassword.ui'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MODIFYPASSWORD_H
#define UI_MODIFYPASSWORD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModifyPasswordClass
{
public:
    QLabel *currentUser;
    QLabel *label;
    QLineEdit *oldPasswordLineEdit;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *newPasswordLineEdit;
    QLineEdit *confirmLineEdit;
    QPushButton *okBtn;

    void setupUi(QWidget *ModifyPasswordClass)
    {
        if (ModifyPasswordClass->objectName().isEmpty())
            ModifyPasswordClass->setObjectName(QString::fromUtf8("ModifyPasswordClass"));
        ModifyPasswordClass->resize(822, 606);
        currentUser = new QLabel(ModifyPasswordClass);
        currentUser->setObjectName(QString::fromUtf8("currentUser"));
        currentUser->setGeometry(QRect(160, 70, 481, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("SimSun"));
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        currentUser->setFont(font);
        label = new QLabel(ModifyPasswordClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(250, 180, 54, 13));
        oldPasswordLineEdit = new QLineEdit(ModifyPasswordClass);
        oldPasswordLineEdit->setObjectName(QString::fromUtf8("oldPasswordLineEdit"));
        oldPasswordLineEdit->setGeometry(QRect(330, 180, 181, 20));
        oldPasswordLineEdit->setEchoMode(QLineEdit::Password);
        label_2 = new QLabel(ModifyPasswordClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(250, 250, 54, 13));
        label_3 = new QLabel(ModifyPasswordClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(250, 320, 54, 13));
        newPasswordLineEdit = new QLineEdit(ModifyPasswordClass);
        newPasswordLineEdit->setObjectName(QString::fromUtf8("newPasswordLineEdit"));
        newPasswordLineEdit->setGeometry(QRect(330, 250, 181, 20));
        newPasswordLineEdit->setEchoMode(QLineEdit::Password);
        confirmLineEdit = new QLineEdit(ModifyPasswordClass);
        confirmLineEdit->setObjectName(QString::fromUtf8("confirmLineEdit"));
        confirmLineEdit->setGeometry(QRect(330, 320, 181, 20));
        confirmLineEdit->setEchoMode(QLineEdit::Password);
        okBtn = new QPushButton(ModifyPasswordClass);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setGeometry(QRect(320, 420, 75, 23));

        retranslateUi(ModifyPasswordClass);

        QMetaObject::connectSlotsByName(ModifyPasswordClass);
    } // setupUi

    void retranslateUi(QWidget *ModifyPasswordClass)
    {
        ModifyPasswordClass->setWindowTitle(QApplication::translate("ModifyPasswordClass", "ModifyPassword", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ModifyPasswordClass", "\345\216\237 \345\257\206 \347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ModifyPasswordClass", "\346\226\260 \345\257\206 \347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ModifyPasswordClass", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("ModifyPasswordClass", "\347\241\256  \345\256\232", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ModifyPasswordClass);
    } // retranslateUi

};

namespace Ui {
    class ModifyPasswordClass: public Ui_ModifyPasswordClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYPASSWORD_H
