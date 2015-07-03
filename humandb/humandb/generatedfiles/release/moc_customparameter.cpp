/****************************************************************************
** Meta object code from reading C++ file 'customparameter.h'
**
** Created: Thu May 24 13:14:45 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../customparameter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'customparameter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CustomParameter[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      37,   16,   16,   16, 0x08,
      83,   16,   16,   16, 0x08,
     125,   16,   16,   16, 0x08,
     167,   16,   16,   16, 0x08,
     209,   16,   16,   16, 0x08,
     251,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CustomParameter[] = {
    "CustomParameter\0\0on_addBtn_clicked()\0"
    "on_paraCountComboBox_currentIndexChanged(int)\0"
    "on_paraComboBox3_currentIndexChanged(int)\0"
    "on_paraComboBox2_currentIndexChanged(int)\0"
    "on_paraComboBox1_currentIndexChanged(int)\0"
    "on_groupComboBox_currentIndexChanged(int)\0"
    "addParameterDone()\0"
};

const QMetaObject CustomParameter::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CustomParameter,
      qt_meta_data_CustomParameter, 0 }
};

const QMetaObject *CustomParameter::metaObject() const
{
    return &staticMetaObject;
}

void *CustomParameter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CustomParameter))
        return static_cast<void*>(const_cast< CustomParameter*>(this));
    return QWidget::qt_metacast(_clname);
}

int CustomParameter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_addBtn_clicked(); break;
        case 1: on_paraCountComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: on_paraComboBox3_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: on_paraComboBox2_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: on_paraComboBox1_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: on_groupComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: addParameterDone(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
