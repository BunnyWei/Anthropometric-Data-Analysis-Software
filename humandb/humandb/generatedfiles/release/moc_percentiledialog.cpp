/****************************************************************************
** Meta object code from reading C++ file 'percentiledialog.h'
**
** Created: Thu May 24 13:14:28 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../percentiledialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'percentiledialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_percentileDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      64,   56,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_percentileDialog[] = {
    "percentileDialog\0\0"
    "on_horizontalSlider_valueChanged(int)\0"
    "painter\0drawNormalCurve(QPainter&)\0"
};

const QMetaObject percentileDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_percentileDialog,
      qt_meta_data_percentileDialog, 0 }
};

const QMetaObject *percentileDialog::metaObject() const
{
    return &staticMetaObject;
}

void *percentileDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_percentileDialog))
        return static_cast<void*>(const_cast< percentileDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int percentileDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_horizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: drawNormalCurve((*reinterpret_cast< QPainter(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
