/****************************************************************************
** Meta object code from reading C++ file 'importmodelthread.h'
**
** Created: Mon Sep 3 15:59:25 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../importmodelthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'importmodelthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImportModelThread[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ImportModelThread[] = {
    "ImportModelThread\0\0completedCount(int)\0"
};

const QMetaObject ImportModelThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ImportModelThread,
      qt_meta_data_ImportModelThread, 0 }
};

const QMetaObject *ImportModelThread::metaObject() const
{
    return &staticMetaObject;
}

void *ImportModelThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImportModelThread))
        return static_cast<void*>(const_cast< ImportModelThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ImportModelThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: completedCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ImportModelThread::completedCount(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
