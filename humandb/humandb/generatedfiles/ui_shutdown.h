/********************************************************************************
** Form generated from reading ui file 'shutdown.ui'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SHUTDOWN_H
#define UI_SHUTDOWN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_ShutdownClass
{
public:

    void setupUi(QToolButton *ShutdownClass)
    {
        if (ShutdownClass->objectName().isEmpty())
            ShutdownClass->setObjectName(QString::fromUtf8("ShutdownClass"));
        ShutdownClass->resize(400, 300);

        retranslateUi(ShutdownClass);

        QMetaObject::connectSlotsByName(ShutdownClass);
    } // setupUi

    void retranslateUi(QToolButton *ShutdownClass)
    {
        ShutdownClass->setWindowTitle(QApplication::translate("ShutdownClass", "Shutdown", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(ShutdownClass);
    } // retranslateUi

};

namespace Ui {
    class ShutdownClass: public Ui_ShutdownClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHUTDOWN_H
