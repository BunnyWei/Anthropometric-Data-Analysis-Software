/****************************************************************************
** Meta object code from reading C++ file 'stat_widget.h'
**
** Created: Thu May 24 13:14:32 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../stat_widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stat_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StatWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      18,   12,   11,   11, 0x08,
      60,   11,   11,   11, 0x08,
      90,   11,   11,   11, 0x08,
     119,   11,   11,   11, 0x08,
     141,   11,   11,   11, 0x08,
     165,   11,   11,   11, 0x08,
     193,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_StatWidget[] = {
    "StatWidget\0\0index\0"
    "on_groupComboBox_currentIndexChanged(int)\0"
    "on_selectNoneButton_clicked()\0"
    "on_selectAllButton_clicked()\0"
    "on_okButton_clicked()\0on_statButton_clicked()\0"
    "on_openPushButton_clicked()\0"
    "on_exportButton_clicked()\0"
};

const QMetaObject StatWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StatWidget,
      qt_meta_data_StatWidget, 0 }
};

const QMetaObject *StatWidget::metaObject() const
{
    return &staticMetaObject;
}

void *StatWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StatWidget))
        return static_cast<void*>(const_cast< StatWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int StatWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_groupComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: on_selectNoneButton_clicked(); break;
        case 2: on_selectAllButton_clicked(); break;
        case 3: on_okButton_clicked(); break;
        case 4: on_statButton_clicked(); break;
        case 5: on_openPushButton_clicked(); break;
        case 6: on_exportButton_clicked(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
