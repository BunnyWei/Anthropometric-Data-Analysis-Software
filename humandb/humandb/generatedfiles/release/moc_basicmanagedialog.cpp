/****************************************************************************
** Meta object code from reading C++ file 'basicmanagedialog.h'
**
** Created: Thu May 24 13:14:47 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../basicmanagedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basicmanagedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BasicManageDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      30,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_BasicManageDialog[] = {
    "BasicManageDialog\0\0workDone()\0"
    "on_pushButton_clicked()\0"
};

const QMetaObject BasicManageDialog::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_BasicManageDialog,
      qt_meta_data_BasicManageDialog, 0 }
};

const QMetaObject *BasicManageDialog::metaObject() const
{
    return &staticMetaObject;
}

void *BasicManageDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BasicManageDialog))
        return static_cast<void*>(const_cast< BasicManageDialog*>(this));
    return QWidget::qt_metacast(_clname);
}

int BasicManageDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: workDone(); break;
        case 1: on_pushButton_clicked(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
