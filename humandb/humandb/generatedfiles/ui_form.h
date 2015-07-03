/********************************************************************************
** Form generated from reading ui file 'form.ui'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_FormClass
{
public:

    void setupUi(QDialog *FormClass)
    {
        if (FormClass->objectName().isEmpty())
            FormClass->setObjectName(QString::fromUtf8("FormClass"));
        FormClass->resize(400, 300);

        retranslateUi(FormClass);

        QMetaObject::connectSlotsByName(FormClass);
    } // setupUi

    void retranslateUi(QDialog *FormClass)
    {
        FormClass->setWindowTitle(QApplication::translate("FormClass", "Form", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(FormClass);
    } // retranslateUi

};

namespace Ui {
    class FormClass: public Ui_FormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
