/****************************************************************************
** Meta object code from reading C++ file 'literalfind.h'
**
** Created: Sun Sep 2 10:30:19 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../literalfind.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'literalfind.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LiteralFind[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      36,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LiteralFind[] = {
    "LiteralFind\0\0on_cancelBtn_clicked()\0"
    "on_findBtn_clicked()\0"
};

const QMetaObject LiteralFind::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LiteralFind,
      qt_meta_data_LiteralFind, 0 }
};

const QMetaObject *LiteralFind::metaObject() const
{
    return &staticMetaObject;
}

void *LiteralFind::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LiteralFind))
        return static_cast<void*>(const_cast< LiteralFind*>(this));
    return QDialog::qt_metacast(_clname);
}

int LiteralFind::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_cancelBtn_clicked(); break;
        case 1: on_findBtn_clicked(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE