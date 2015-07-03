/****************************************************************************
** Meta object code from reading C++ file 'fit_widget.h'
**
** Created: Sun Sep 2 10:30:22 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../fit_widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fit_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FitWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x08,
      37,   10,   10,   10, 0x08,
      63,   10,   10,   10, 0x08,
      89,   10,   10,   10, 0x08,
     132,   10,   10,   10, 0x08,
     178,  175,   10,   10, 0x08,
     211,  175,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FitWidget[] = {
    "FitWidget\0\0on_exportButton_clicked()\0"
    "on_selectButton_clicked()\0"
    "on_deleteButton_clicked()\0"
    "on_xTableComboBox_currentIndexChanged(int)\0"
    "on_yTableComboBox_currentIndexChanged(int)\0"
    "it\0onXItemChanged(QListWidgetItem*)\0"
    "onYItemChanged(QListWidgetItem*)\0"
};

const QMetaObject FitWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FitWidget,
      qt_meta_data_FitWidget, 0 }
};

const QMetaObject *FitWidget::metaObject() const
{
    return &staticMetaObject;
}

void *FitWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FitWidget))
        return static_cast<void*>(const_cast< FitWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int FitWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_exportButton_clicked(); break;
        case 1: on_selectButton_clicked(); break;
        case 2: on_deleteButton_clicked(); break;
        case 3: on_xTableComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: on_yTableComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: onXItemChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: onYItemChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
