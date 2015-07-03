/********************************************************************************
** Form generated from reading ui file 'delete_widgt.ui'
**
** Created: Sun Sep 2 10:30:25 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DELETE_WIDGT_H
#define UI_DELETE_WIDGT_H

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
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DeleteWidgtClass
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QLineEdit *numberLineEdit;
    QPushButton *deleteButton;
    QLabel *fenquLabel;
    QComboBox *fenquComboBox;
    QGroupBox *measureGroupBox;
    QComboBox *measureComboBox;
    QLabel *label_3;
    QPushButton *measureDelButton;

    void setupUi(QWidget *DeleteWidgtClass)
    {
        if (DeleteWidgtClass->objectName().isEmpty())
            DeleteWidgtClass->setObjectName(QString::fromUtf8("DeleteWidgtClass"));
        DeleteWidgtClass->resize(1102, 521);
        groupBox = new QGroupBox(DeleteWidgtClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(90, 60, 341, 351));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 151, 21));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(180, 40, 81, 22));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 100, 151, 16));
        numberLineEdit = new QLineEdit(groupBox);
        numberLineEdit->setObjectName(QString::fromUtf8("numberLineEdit"));
        numberLineEdit->setGeometry(QRect(180, 100, 113, 20));
        deleteButton = new QPushButton(groupBox);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(100, 230, 75, 23));
        fenquLabel = new QLabel(groupBox);
        fenquLabel->setObjectName(QString::fromUtf8("fenquLabel"));
        fenquLabel->setGeometry(QRect(20, 140, 151, 16));
        fenquComboBox = new QComboBox(groupBox);
        fenquComboBox->setObjectName(QString::fromUtf8("fenquComboBox"));
        fenquComboBox->setGeometry(QRect(180, 135, 69, 22));
        measureGroupBox = new QGroupBox(DeleteWidgtClass);
        measureGroupBox->setObjectName(QString::fromUtf8("measureGroupBox"));
        measureGroupBox->setGeometry(QRect(570, 70, 241, 351));
        measureComboBox = new QComboBox(measureGroupBox);
        measureComboBox->setObjectName(QString::fromUtf8("measureComboBox"));
        measureComboBox->setGeometry(QRect(60, 90, 121, 24));
        label_3 = new QLabel(measureGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 40, 201, 16));
        measureDelButton = new QPushButton(measureGroupBox);
        measureDelButton->setObjectName(QString::fromUtf8("measureDelButton"));
        measureDelButton->setGeometry(QRect(60, 220, 121, 24));

        retranslateUi(DeleteWidgtClass);

        QMetaObject::connectSlotsByName(DeleteWidgtClass);
    } // setupUi

    void retranslateUi(QWidget *DeleteWidgtClass)
    {
        DeleteWidgtClass->setWindowTitle(QApplication::translate("DeleteWidgtClass", "DeleteWidgt", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DeleteWidgtClass", "\344\272\272\345\221\230\344\277\241\346\201\257\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DeleteWidgtClass", "\350\257\267\351\200\211\346\213\251\350\246\201\345\210\240\351\231\244\347\232\204\347\261\273\345\236\213\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DeleteWidgtClass", "\350\257\267\351\200\211\346\213\251\350\246\201\345\210\240\351\231\244\347\232\204\347\274\226\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        deleteButton->setText(QApplication::translate("DeleteWidgtClass", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        fenquLabel->setText(QApplication::translate("DeleteWidgtClass", "\350\257\267\351\200\211\346\213\251\350\246\201\345\210\240\351\231\244\347\232\204\345\210\206\345\214\272", 0, QApplication::UnicodeUTF8));
        measureGroupBox->setTitle(QApplication::translate("DeleteWidgtClass", "\346\265\213\351\207\217\344\277\241\346\201\257\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DeleteWidgtClass", "\350\257\267\351\200\211\346\213\251\350\246\201\345\210\240\351\231\244\347\232\204\346\265\213\351\207\217\346\225\260\346\215\256\357\274\232", 0, QApplication::UnicodeUTF8));
        measureDelButton->setText(QApplication::translate("DeleteWidgtClass", "\345\210\240\351\231\244\346\265\213\351\207\217\346\225\260\346\215\256", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DeleteWidgtClass);
    } // retranslateUi

};

namespace Ui {
    class DeleteWidgtClass: public Ui_DeleteWidgtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETE_WIDGT_H
