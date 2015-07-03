/****************************************************************************
** Meta object code from reading C++ file 'delete_widgt.h'
**
** Created: Sun Sep 2 10:30:22 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../delete_widgt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'delete_widgt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DeleteWidgt[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      43,   12,   12,   12, 0x08,
      80,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DeleteWidgt[] = {
    "DeleteWidgt\0\0on_measureDelButton_clicked()\0"
    "on_comboBox_currentIndexChanged(int)\0"
    "on_deleteButton_clicked()\0"
};

const QMetaObject DeleteWidgt::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DeleteWidgt,
      qt_meta_data_DeleteWidgt, 0 }
};

const QMetaObject *DeleteWidgt::metaObject() const
{
    return &staticMetaObject;
}

void *DeleteWidgt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DeleteWidgt))
        return static_cast<void*>(const_cast< DeleteWidgt*>(this));
    return QWidget::qt_metacast(_clname);
}

int DeleteWidgt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_measureDelButton_clicked(); break;
        case 1: on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: on_deleteButton_clicked(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
