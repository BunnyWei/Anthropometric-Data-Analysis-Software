/********************************************************************************
** Form generated from reading ui file 'literalfind.ui'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LITERALFIND_H
#define UI_LITERALFIND_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LiteralFindClass
{
public:
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QCheckBox *nameCheckBox;
    QLineEdit *nameLineEdit;
    QCheckBox *defCheckBox;
    QLineEdit *defLineEdit;
    QCheckBox *methodCheckBox;
    QLineEdit *methodLineEdit;
    QCheckBox *meaPointCheckBox;
    QLineEdit *meaPointLineEdit;
    QCheckBox *bodyCheckBox;
    QComboBox *bodyComboBox;
    QPushButton *findBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *LiteralFindClass)
    {
        if (LiteralFindClass->objectName().isEmpty())
            LiteralFindClass->setObjectName(QString::fromUtf8("LiteralFindClass"));
        LiteralFindClass->resize(527, 262);
        layoutWidget = new QWidget(LiteralFindClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 40, 411, 131));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setMargin(11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        nameCheckBox = new QCheckBox(layoutWidget);
        nameCheckBox->setObjectName(QString::fromUtf8("nameCheckBox"));

        formLayout->setWidget(0, QFormLayout::LabelRole, nameCheckBox);

        nameLineEdit = new QLineEdit(layoutWidget);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameLineEdit);

        defCheckBox = new QCheckBox(layoutWidget);
        defCheckBox->setObjectName(QString::fromUtf8("defCheckBox"));

        formLayout->setWidget(1, QFormLayout::LabelRole, defCheckBox);

        defLineEdit = new QLineEdit(layoutWidget);
        defLineEdit->setObjectName(QString::fromUtf8("defLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, defLineEdit);

        methodCheckBox = new QCheckBox(layoutWidget);
        methodCheckBox->setObjectName(QString::fromUtf8("methodCheckBox"));

        formLayout->setWidget(2, QFormLayout::LabelRole, methodCheckBox);

        methodLineEdit = new QLineEdit(layoutWidget);
        methodLineEdit->setObjectName(QString::fromUtf8("methodLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, methodLineEdit);

        meaPointCheckBox = new QCheckBox(layoutWidget);
        meaPointCheckBox->setObjectName(QString::fromUtf8("meaPointCheckBox"));

        formLayout->setWidget(3, QFormLayout::LabelRole, meaPointCheckBox);

        meaPointLineEdit = new QLineEdit(layoutWidget);
        meaPointLineEdit->setObjectName(QString::fromUtf8("meaPointLineEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, meaPointLineEdit);

        bodyCheckBox = new QCheckBox(layoutWidget);
        bodyCheckBox->setObjectName(QString::fromUtf8("bodyCheckBox"));

        formLayout->setWidget(4, QFormLayout::LabelRole, bodyCheckBox);

        bodyComboBox = new QComboBox(layoutWidget);
        bodyComboBox->setObjectName(QString::fromUtf8("bodyComboBox"));

        formLayout->setWidget(4, QFormLayout::FieldRole, bodyComboBox);

        findBtn = new QPushButton(LiteralFindClass);
        findBtn->setObjectName(QString::fromUtf8("findBtn"));
        findBtn->setGeometry(QRect(80, 200, 127, 25));
        cancelBtn = new QPushButton(LiteralFindClass);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(290, 200, 126, 25));

        retranslateUi(LiteralFindClass);

        QMetaObject::connectSlotsByName(LiteralFindClass);
    } // setupUi

    void retranslateUi(QDialog *LiteralFindClass)
    {
        LiteralFindClass->setWindowTitle(QApplication::translate("LiteralFindClass", "\345\217\202\346\225\260\346\220\234\347\264\242", 0, QApplication::UnicodeUTF8));
        nameCheckBox->setText(QApplication::translate("LiteralFindClass", "\345\217\202\346\225\260\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        defCheckBox->setText(QApplication::translate("LiteralFindClass", "\345\217\202\346\225\260\345\256\232\344\271\211\357\274\232", 0, QApplication::UnicodeUTF8));
        methodCheckBox->setText(QApplication::translate("LiteralFindClass", "\346\265\213\351\207\217\346\226\271\346\263\225\357\274\232", 0, QApplication::UnicodeUTF8));
        meaPointCheckBox->setText(QApplication::translate("LiteralFindClass", "\346\265\213 \351\207\217 \347\202\271\357\274\232", 0, QApplication::UnicodeUTF8));
        bodyCheckBox->setText(QApplication::translate("LiteralFindClass", "\344\272\272\344\275\223\351\203\250\344\275\215\357\274\232", 0, QApplication::UnicodeUTF8));
        findBtn->setText(QApplication::translate("LiteralFindClass", "\345\237\272\346\234\254\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("LiteralFindClass", "\351\253\230\347\272\247\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(LiteralFindClass);
    } // retranslateUi

};

namespace Ui {
    class LiteralFindClass: public Ui_LiteralFindClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LITERALFIND_H
