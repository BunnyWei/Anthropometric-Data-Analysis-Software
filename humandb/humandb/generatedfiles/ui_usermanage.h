/********************************************************************************
** Form generated from reading ui file 'usermanage.ui'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_USERMANAGE_H
#define UI_USERMANAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserManageClass
{
public:
    QGroupBox *groupBox;
    QPushButton *addUserBtn;
    QLabel *label;
    QLineEdit *userNameLineEdit;
    QLabel *label_2;
    QComboBox *authorityComboBox;
    QLabel *label_3;
    QLineEdit *newPwdLiEt;
    QLabel *label_4;
    QLineEdit *confirmPwdLiEt;
    QGroupBox *groupBox_3;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *authorComBox;
    QPushButton *modifyAuthorBtn;
    QPushButton *delUserBtn;
    QLineEdit *userLineEdit;
    QTableWidget *tableWidget;
    QPushButton *showAllUsersBtn;

    void setupUi(QWidget *UserManageClass)
    {
        if (UserManageClass->objectName().isEmpty())
            UserManageClass->setObjectName(QString::fromUtf8("UserManageClass"));
        UserManageClass->resize(1144, 618);
        groupBox = new QGroupBox(UserManageClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(400, 70, 341, 441));
        addUserBtn = new QPushButton(groupBox);
        addUserBtn->setObjectName(QString::fromUtf8("addUserBtn"));
        addUserBtn->setGeometry(QRect(100, 330, 88, 24));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(41, 61, 76, 20));
        userNameLineEdit = new QLineEdit(groupBox);
        userNameLineEdit->setObjectName(QString::fromUtf8("userNameLineEdit"));
        userNameLineEdit->setGeometry(QRect(124, 61, 167, 24));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(41, 120, 77, 20));
        authorityComboBox = new QComboBox(groupBox);
        authorityComboBox->setObjectName(QString::fromUtf8("authorityComboBox"));
        authorityComboBox->setGeometry(QRect(124, 120, 167, 24));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(41, 170, 76, 20));
        newPwdLiEt = new QLineEdit(groupBox);
        newPwdLiEt->setObjectName(QString::fromUtf8("newPwdLiEt"));
        newPwdLiEt->setGeometry(QRect(124, 170, 167, 24));
        newPwdLiEt->setEchoMode(QLineEdit::Password);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(41, 230, 75, 20));
        confirmPwdLiEt = new QLineEdit(groupBox);
        confirmPwdLiEt->setObjectName(QString::fromUtf8("confirmPwdLiEt"));
        confirmPwdLiEt->setGeometry(QRect(124, 230, 167, 24));
        confirmPwdLiEt->setEchoMode(QLineEdit::Password);
        groupBox_3 = new QGroupBox(UserManageClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(770, 70, 321, 441));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 120, 72, 16));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 50, 72, 16));
        authorComBox = new QComboBox(groupBox_3);
        authorComBox->setObjectName(QString::fromUtf8("authorComBox"));
        authorComBox->setGeometry(QRect(120, 110, 111, 24));
        modifyAuthorBtn = new QPushButton(groupBox_3);
        modifyAuthorBtn->setObjectName(QString::fromUtf8("modifyAuthorBtn"));
        modifyAuthorBtn->setGeometry(QRect(90, 220, 88, 24));
        delUserBtn = new QPushButton(groupBox_3);
        delUserBtn->setObjectName(QString::fromUtf8("delUserBtn"));
        delUserBtn->setGeometry(QRect(90, 320, 88, 24));
        userLineEdit = new QLineEdit(groupBox_3);
        userLineEdit->setObjectName(QString::fromUtf8("userLineEdit"));
        userLineEdit->setGeometry(QRect(110, 50, 171, 20));
        tableWidget = new QTableWidget(UserManageClass);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(60, 100, 251, 421));
        showAllUsersBtn = new QPushButton(UserManageClass);
        showAllUsersBtn->setObjectName(QString::fromUtf8("showAllUsersBtn"));
        showAllUsersBtn->setGeometry(QRect(110, 40, 141, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("SimSun"));
        font.setPointSize(16);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        showAllUsersBtn->setFont(font);

        retranslateUi(UserManageClass);

        QMetaObject::connectSlotsByName(UserManageClass);
    } // setupUi

    void retranslateUi(QWidget *UserManageClass)
    {
        UserManageClass->setWindowTitle(QApplication::translate("UserManageClass", "UserManage", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("UserManageClass", "\346\267\273\345\212\240\347\224\250\346\210\267", 0, QApplication::UnicodeUTF8));
        addUserBtn->setText(QApplication::translate("UserManageClass", "\346\267\273\345\212\240\347\224\250\346\210\267", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UserManageClass", "\347\224\250 \346\210\267 \345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("UserManageClass", "\346\235\203    \351\231\220\357\274\232", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("UserManageClass", "\346\226\260 \345\257\206 \347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("UserManageClass", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("UserManageClass", "\344\277\256\346\224\271\346\235\203\351\231\220\345\222\214\345\210\240\351\231\244\347\224\250\346\210\267", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("UserManageClass", "\346\235\203    \351\231\220\357\274\232", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("UserManageClass", "\347\224\250 \346\210\267 \345\220\215\357\274\232", 0, QApplication::UnicodeUTF8));
        modifyAuthorBtn->setText(QApplication::translate("UserManageClass", "\344\277\256\346\224\271\346\235\203\351\231\220", 0, QApplication::UnicodeUTF8));
        delUserBtn->setText(QApplication::translate("UserManageClass", "\345\210\240\351\231\244\347\224\250\346\210\267", 0, QApplication::UnicodeUTF8));
        showAllUsersBtn->setText(QApplication::translate("UserManageClass", "\346\230\276\347\244\272\346\211\200\346\234\211\347\224\250\346\210\267", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(UserManageClass);
    } // retranslateUi

};

namespace Ui {
    class UserManageClass: public Ui_UserManageClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMANAGE_H
