/****************************************************************************
** Meta object code from reading C++ file 'import_widget.h'
**
** Created: Sat Jun 30 10:36:22 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../import_widget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'import_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImportWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   13,   13,   13, 0x08,
      62,   13,   13,   13, 0x08,
      86,   13,   13,   13, 0x08,
     112,   13,   13,   13, 0x08,
     136,   13,   13,   13, 0x08,
     149,   13,   13,   13, 0x08,
     167,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ImportWidget[] = {
    "ImportWidget\0\0completedCount(int)\0"
    "on_importModelBtn_clicked()\0"
    "on_imPhotoBtn_clicked()\0"
    "on_importButton_clicked()\0"
    "on_openButton_clicked()\0importDone()\0"
    "importPhotoDone()\0importModelDone()\0"
};

const QMetaObject ImportWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImportWidget,
      qt_meta_data_ImportWidget, 0 }
};

const QMetaObject *ImportWidget::metaObject() const
{
    return &staticMetaObject;
}

void *ImportWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImportWidget))
        return static_cast<void*>(const_cast< ImportWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImportWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: completedCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: on_importModelBtn_clicked(); break;
        case 2: on_imPhotoBtn_clicked(); break;
        case 3: on_importButton_clicked(); break;
        case 4: on_openButton_clicked(); break;
        case 5: importDone(); break;
        case 6: importPhotoDone(); break;
        case 7: importModelDone(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ImportWidget::completedCount(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
