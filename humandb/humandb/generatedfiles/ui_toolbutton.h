/********************************************************************************
** Form generated from reading ui file 'toolbutton.ui'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TOOLBUTTON_H
#define UI_TOOLBUTTON_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_ToolButtonClass
{
public:

    void setupUi(QToolButton *ToolButtonClass)
    {
        if (ToolButtonClass->objectName().isEmpty())
            ToolButtonClass->setObjectName(QString::fromUtf8("ToolButtonClass"));
        ToolButtonClass->resize(400, 300);

        retranslateUi(ToolButtonClass);

        QMetaObject::connectSlotsByName(ToolButtonClass);
    } // setupUi

    void retranslateUi(QToolButton *ToolButtonClass)
    {
        ToolButtonClass->setWindowTitle(QApplication::translate("ToolButtonClass", "ToolButton", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ToolButtonClass);
    } // retranslateUi

};

namespace Ui {
    class ToolButtonClass: public Ui_ToolButtonClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLBUTTON_H
