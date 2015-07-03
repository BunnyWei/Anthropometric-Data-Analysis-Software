/****************************************************************************
** Meta object code from reading C++ file 'qglobalvar.h'
**
** Created: Thu May 24 13:14:34 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qglobalvar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qglobalvar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QGlobalVar[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_QGlobalVar[] = {
    "QGlobalVar\0"
};

const QMetaObject QGlobalVar::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QGlobalVar,
      qt_meta_data_QGlobalVar, 0 }
};

const QMetaObject *QGlobalVar::metaObject() const
{
    return &staticMetaObject;
}

void *QGlobalVar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QGlobalVar))
        return static_cast<void*>(const_cast< QGlobalVar*>(this));
    return QObject::qt_metacast(_clname);
}

int QGlobalVar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
