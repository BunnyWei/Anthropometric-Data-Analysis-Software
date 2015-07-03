/****************************************************************************
** Meta object code from reading C++ file 'form.h'
**
** Created: Sun Sep 2 10:30:21 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../form.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'form.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Form[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x08,
      27,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Form[] = {
    "Form\0\0enterButtonClicked()\0"
    "shutdownButtonClicked()\0"
};

const QMetaObject Form::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Form,
      qt_meta_data_Form, 0 }
};

const QMetaObject *Form::metaObject() const
{
    return &staticMetaObject;
}

void *Form::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Form))
        return static_cast<void*>(const_cast< Form*>(this));
    return QDialog::qt_metacast(_clname);
}

int Form::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: enterButtonClicked(); break;
        case 1: shutdownButtonClicked(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
