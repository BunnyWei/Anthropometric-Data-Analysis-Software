/****************************************************************************
** Meta object code from reading C++ file 'basic_manage_thread.h'
**
** Created: Sun Sep 2 10:30:24 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../basic_manage_thread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basic_manage_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WorkThread[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_WorkThread[] = {
    "WorkThread\0\0complete_count(int)\0"
};

const QMetaObject WorkThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_WorkThread,
      qt_meta_data_WorkThread, 0 }
};

const QMetaObject *WorkThread::metaObject() const
{
    return &staticMetaObject;
}

void *WorkThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WorkThread))
        return static_cast<void*>(const_cast< WorkThread*>(this));
    return QThread::qt_metacast(_clname);
}

int WorkThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: complete_count((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void WorkThread::complete_count(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
