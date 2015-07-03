/********************************************************************************
** Form generated from reading ui file 'pickpointsDialog.ui'
**
** Created: Sun Sep 2 10:27:13 2012
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PICKPOINTSDIALOG_H
#define UI_PICKPOINTSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pickpointsDialog
{
public:
    QFrame *frame;
    QTreeWidget *pickedPointsTreeWidget;
    QGroupBox *groupBox;
    QRadioButton *pickPointModeRadioButton;
    QRadioButton *movePointRadioButton;
    QRadioButton *selectPointRadioButton;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *loadPointsButton;
    QPushButton *saveButton;
    QGroupBox *groupBox_2;
    QCheckBox *defaultTemplateCheckBox;
    QLabel *label;
    QLabel *templateNameLabel;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *saveTemplateButton;
    QPushButton *loadTemplateButton;
    QPushButton *clearTemplateButton;
    QPushButton *addPointToTemplateButton;
    QGroupBox *groupBox_3;
    QCheckBox *showNormalCheckBox;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QRadioButton *pinRadioButton;
    QRadioButton *lineRadioButton;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *renamePointButton;
    QPushButton *clearPointButton;
    QPushButton *removePointButton;
    QPushButton *removeAllPointsButton;
    QPushButton *undoButton;
    QComboBox *groupComboBox;
    QComboBox *parameterComboBox;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *showItemBtn;

    void setupUi(QWidget *pickpointsDialog)
    {
        if (pickpointsDialog->objectName().isEmpty())
            pickpointsDialog->setObjectName(QString::fromUtf8("pickpointsDialog"));
        pickpointsDialog->resize(571, 709);
        frame = new QFrame(pickpointsDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 10, 551, 681));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pickedPointsTreeWidget = new QTreeWidget(frame);
        pickedPointsTreeWidget->setObjectName(QString::fromUtf8("pickedPointsTreeWidget"));
        pickedPointsTreeWidget->setGeometry(QRect(10, 120, 531, 291));
        pickedPointsTreeWidget->setColumnCount(6);
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 321, 51));
        pickPointModeRadioButton = new QRadioButton(groupBox);
        pickPointModeRadioButton->setObjectName(QString::fromUtf8("pickPointModeRadioButton"));
        pickPointModeRadioButton->setGeometry(QRect(10, 20, 131, 23));
        pickPointModeRadioButton->setChecked(true);
        movePointRadioButton = new QRadioButton(groupBox);
        movePointRadioButton->setObjectName(QString::fromUtf8("movePointRadioButton"));
        movePointRadioButton->setGeometry(QRect(100, 20, 91, 23));
        selectPointRadioButton = new QRadioButton(groupBox);
        selectPointRadioButton->setObjectName(QString::fromUtf8("selectPointRadioButton"));
        selectPointRadioButton->setGeometry(QRect(190, 20, 91, 24));
        layoutWidget = new QWidget(frame);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(350, 10, 181, 64));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        loadPointsButton = new QPushButton(layoutWidget);
        loadPointsButton->setObjectName(QString::fromUtf8("loadPointsButton"));

        gridLayout->addWidget(loadPointsButton, 1, 0, 1, 1);

        saveButton = new QPushButton(layoutWidget);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        gridLayout->addWidget(saveButton, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 460, 431, 131));
        defaultTemplateCheckBox = new QCheckBox(groupBox_2);
        defaultTemplateCheckBox->setObjectName(QString::fromUtf8("defaultTemplateCheckBox"));
        defaultTemplateCheckBox->setGeometry(QRect(10, 20, 211, 24));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 100, 111, 18));
        templateNameLabel = new QLabel(groupBox_2);
        templateNameLabel->setObjectName(QString::fromUtf8("templateNameLabel"));
        templateNameLabel->setGeometry(QRect(110, 100, 291, 20));
        QPalette palette;
        QBrush brush(QColor(0, 0, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(127, 125, 123, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        templateNameLabel->setPalette(palette);
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 60, 401, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        saveTemplateButton = new QPushButton(layoutWidget1);
        saveTemplateButton->setObjectName(QString::fromUtf8("saveTemplateButton"));

        horizontalLayout->addWidget(saveTemplateButton);

        loadTemplateButton = new QPushButton(layoutWidget1);
        loadTemplateButton->setObjectName(QString::fromUtf8("loadTemplateButton"));

        horizontalLayout->addWidget(loadTemplateButton);

        clearTemplateButton = new QPushButton(layoutWidget1);
        clearTemplateButton->setObjectName(QString::fromUtf8("clearTemplateButton"));

        horizontalLayout->addWidget(clearTemplateButton);

        addPointToTemplateButton = new QPushButton(layoutWidget1);
        addPointToTemplateButton->setObjectName(QString::fromUtf8("addPointToTemplateButton"));

        horizontalLayout->addWidget(addPointToTemplateButton);

        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 600, 431, 61));
        showNormalCheckBox = new QCheckBox(groupBox_3);
        showNormalCheckBox->setObjectName(QString::fromUtf8("showNormalCheckBox"));
        showNormalCheckBox->setGeometry(QRect(10, 20, 111, 24));
        showNormalCheckBox->setChecked(true);
        layoutWidget2 = new QWidget(groupBox_3);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(170, 20, 181, 26));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        pinRadioButton = new QRadioButton(layoutWidget2);
        pinRadioButton->setObjectName(QString::fromUtf8("pinRadioButton"));
        pinRadioButton->setChecked(true);

        horizontalLayout_4->addWidget(pinRadioButton);

        lineRadioButton = new QRadioButton(layoutWidget2);
        lineRadioButton->setObjectName(QString::fromUtf8("lineRadioButton"));

        horizontalLayout_4->addWidget(lineRadioButton);

        layoutWidget3 = new QWidget(frame);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 420, 431, 41));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        renamePointButton = new QPushButton(layoutWidget3);
        renamePointButton->setObjectName(QString::fromUtf8("renamePointButton"));

        horizontalLayout_2->addWidget(renamePointButton);

        clearPointButton = new QPushButton(layoutWidget3);
        clearPointButton->setObjectName(QString::fromUtf8("clearPointButton"));

        horizontalLayout_2->addWidget(clearPointButton);

        removePointButton = new QPushButton(layoutWidget3);
        removePointButton->setObjectName(QString::fromUtf8("removePointButton"));

        horizontalLayout_2->addWidget(removePointButton);

        removeAllPointsButton = new QPushButton(layoutWidget3);
        removeAllPointsButton->setObjectName(QString::fromUtf8("removeAllPointsButton"));

        horizontalLayout_2->addWidget(removeAllPointsButton);

        undoButton = new QPushButton(frame);
        undoButton->setObjectName(QString::fromUtf8("undoButton"));
        undoButton->setGeometry(QRect(460, 420, 71, 81));
        groupComboBox = new QComboBox(frame);
        groupComboBox->setObjectName(QString::fromUtf8("groupComboBox"));
        groupComboBox->setGeometry(QRect(76, 91, 131, 21));
        parameterComboBox = new QComboBox(frame);
        parameterComboBox->setObjectName(QString::fromUtf8("parameterComboBox"));
        parameterComboBox->setGeometry(QRect(278, 91, 131, 21));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 91, 61, 21));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(213, 91, 61, 21));
        showItemBtn = new QPushButton(frame);
        showItemBtn->setObjectName(QString::fromUtf8("showItemBtn"));
        showItemBtn->setGeometry(QRect(440, 90, 101, 23));

        retranslateUi(pickpointsDialog);

        QMetaObject::connectSlotsByName(pickpointsDialog);
    } // setupUi

    void retranslateUi(QWidget *pickpointsDialog)
    {
        pickpointsDialog->setWindowTitle(QApplication::translate("pickpointsDialog", "Form", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = pickedPointsTreeWidget->headerItem();
        ___qtreewidgetitem->setText(5, QApplication::translate("pickpointsDialog", "6", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(4, QApplication::translate("pickpointsDialog", "5", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(3, QApplication::translate("pickpointsDialog", "4", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(2, QApplication::translate("pickpointsDialog", "3", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("pickpointsDialog", "2", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("pickpointsDialog", "1", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("pickpointsDialog", "Mode: ", 0, QApplication::UnicodeUTF8));
        pickPointModeRadioButton->setText(QApplication::translate("pickpointsDialog", "Pick Point", 0, QApplication::UnicodeUTF8));
        movePointRadioButton->setText(QApplication::translate("pickpointsDialog", "Move Point", 0, QApplication::UnicodeUTF8));
        selectPointRadioButton->setText(QApplication::translate("pickpointsDialog", "Select Point", 0, QApplication::UnicodeUTF8));
        loadPointsButton->setText(QApplication::translate("pickpointsDialog", "\346\230\276\347\244\272\346\211\200\346\234\211\345\217\202\346\225\260\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("pickpointsDialog", "\344\277\235\345\255\230\345\210\260\346\225\260\346\215\256\345\272\223", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("pickpointsDialog", "Template Controls", 0, QApplication::UnicodeUTF8));
        defaultTemplateCheckBox->setText(QApplication::translate("pickpointsDialog", "Save this as your default template", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("pickpointsDialog", "Template Name:", 0, QApplication::UnicodeUTF8));
        templateNameLabel->setText(QApplication::translate("pickpointsDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        saveTemplateButton->setText(QApplication::translate("pickpointsDialog", "Save", 0, QApplication::UnicodeUTF8));
        loadTemplateButton->setText(QApplication::translate("pickpointsDialog", "Load", 0, QApplication::UnicodeUTF8));
        clearTemplateButton->setText(QApplication::translate("pickpointsDialog", "Clear", 0, QApplication::UnicodeUTF8));
        addPointToTemplateButton->setText(QApplication::translate("pickpointsDialog", "Add Point", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("pickpointsDialog", "Normal Options", 0, QApplication::UnicodeUTF8));
        showNormalCheckBox->setText(QApplication::translate("pickpointsDialog", "Show Normal?", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("pickpointsDialog", "Draw as a:  ", 0, QApplication::UnicodeUTF8));
        pinRadioButton->setText(QApplication::translate("pickpointsDialog", "Pin", 0, QApplication::UnicodeUTF8));
        lineRadioButton->setText(QApplication::translate("pickpointsDialog", "Line", 0, QApplication::UnicodeUTF8));
        renamePointButton->setText(QApplication::translate("pickpointsDialog", "Rename Point", 0, QApplication::UnicodeUTF8));
        clearPointButton->setText(QApplication::translate("pickpointsDialog", "Clear Point", 0, QApplication::UnicodeUTF8));
        removePointButton->setText(QApplication::translate("pickpointsDialog", "\345\210\240\351\231\244\347\202\271", 0, QApplication::UnicodeUTF8));
        removeAllPointsButton->setText(QApplication::translate("pickpointsDialog", "Remove All Points", 0, QApplication::UnicodeUTF8));
        undoButton->setText(QApplication::translate("pickpointsDialog", "Undo\n"
"last\n"
"move", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("pickpointsDialog", "\351\200\211\346\213\251\345\210\206\347\273\204\357\274\232", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("pickpointsDialog", "\351\200\211\346\213\251\345\217\202\346\225\260\357\274\232", 0, QApplication::UnicodeUTF8));
        showItemBtn->setText(QApplication::translate("pickpointsDialog", "\346\230\276\347\244\272\345\217\202\346\225\260\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(pickpointsDialog);
    } // retranslateUi

};

namespace Ui {
    class pickpointsDialog: public Ui_pickpointsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICKPOINTSDIALOG_H
