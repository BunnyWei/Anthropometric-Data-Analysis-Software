/****************************************************************************
** Meta object code from reading C++ file 'statistic.h'
**
** Created: Fri Jun 15 11:27:27 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../statistic.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'statistic.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Statistic[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      37,   10,   10,   10, 0x08,
      65,   10,   10,   10, 0x08,
      90,   10,   10,   10, 0x08,
     126,   10,   10,   10, 0x08,
     150,   10,   10,   10, 0x08,
     180,   10,   10,   10, 0x08,
     209,   10,   10,   10, 0x08,
     232,   10,   10,   10, 0x08,
     291,  274,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Statistic[] = {
    "Statistic\0\0on_exportButton_clicked()\0"
    "on_openPushButton_clicked()\0"
    "on_clearButton_clicked()\0"
    "on_tableWidget_pressed(QModelIndex)\0"
    "on_statButton_clicked()\0"
    "on_selectNoneButton_clicked()\0"
    "on_selectAllButton_clicked()\0"
    "on_addButton_clicked()\0"
    "on_tableComboBox_currentIndexChanged(int)\0"
    "itemnum,itemName\0showPercentileDialog(QString,QString)\0"
};

const QMetaObject Statistic::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Statistic,
      qt_meta_data_Statistic, 0 }
};

const QMetaObject *Statistic::metaObject() const
{
    return &staticMetaObject;
}

void *Statistic::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Statistic))
        return static_cast<void*>(const_cast< Statistic*>(this));
    return QWidget::qt_metacast(_clname);
}

int Statistic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_exportButton_clicked(); break;
        case 1: on_openPushButton_clicked(); break;
        case 2: on_clearButton_clicked(); break;
        case 3: on_tableWidget_pressed((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: on_statButton_clicked(); break;
        case 5: on_selectNoneButton_clicked(); break;
        case 6: on_selectAllButton_clicked(); break;
        case 7: on_addButton_clicked(); break;
        case 8: on_tableComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: showPercentileDialog((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE