/****************************************************************************
** Meta object code from reading C++ file 'usermanage.h'
**
** Created: Mon Sep 3 15:59:15 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../usermanage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usermanage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_UserManage[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      41,   11,   11,   11, 0x08,
      65,   11,   11,   11, 0x08,
      94,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_UserManage[] = {
    "UserManage\0\0on_showAllUsersBtn_clicked()\0"
    "on_delUserBtn_clicked()\0"
    "on_modifyAuthorBtn_clicked()\0"
    "on_addUserBtn_clicked()\0"
};

const QMetaObject UserManage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UserManage,
      qt_meta_data_UserManage, 0 }
};

const QMetaObject *UserManage::metaObject() const
{
    return &staticMetaObject;
}

void *UserManage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UserManage))
        return static_cast<void*>(const_cast< UserManage*>(this));
    return QWidget::qt_metacast(_clname);
}

int UserManage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_showAllUsersBtn_clicked(); break;
        case 1: on_delUserBtn_clicked(); break;
        case 2: on_modifyAuthorBtn_clicked(); break;
        case 3: on_addUserBtn_clicked(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
