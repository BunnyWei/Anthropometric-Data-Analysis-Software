/****************************************************************************
** Meta object code from reading C++ file 'standardwidget.h'
**
** Created: Tue May 29 19:52:24 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../standardwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'standardwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StandardWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_StandardWidget[] = {
    "StandardWidget\0\0on_searchBtn_clicked()\0"
};

const QMetaObject StandardWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StandardWidget,
      qt_meta_data_StandardWidget, 0 }
};

const QMetaObject *StandardWidget::metaObject() const
{
    return &staticMetaObject;
}

void *StandardWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StandardWidget))
        return static_cast<void*>(const_cast< StandardWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int StandardWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_searchBtn_clicked(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
