/****************************************************************************
** Meta object code from reading C++ file 'relativeparameter.h'
**
** Created: Thu May 31 12:51:23 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../relativeparameter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'relativeparameter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RelativeParameter[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      39,   18,   18,   18, 0x08,
      81,   18,   18,   18, 0x08,
     122,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RelativeParameter[] = {
    "RelativeParameter\0\0on_staBtn_clicked()\0"
    "on_tableComboBox_currentIndexChanged(int)\0"
    "on_typeComboBox_currentIndexChanged(int)\0"
    "on_groupComboBox_currentIndexChanged(int)\0"
};

const QMetaObject RelativeParameter::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RelativeParameter,
      qt_meta_data_RelativeParameter, 0 }
};

const QMetaObject *RelativeParameter::metaObject() const
{
    return &staticMetaObject;
}

void *RelativeParameter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RelativeParameter))
        return static_cast<void*>(const_cast< RelativeParameter*>(this));
    return QWidget::qt_metacast(_clname);
}

int RelativeParameter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_staBtn_clicked(); break;
        case 1: on_tableComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: on_typeComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: on_groupComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
