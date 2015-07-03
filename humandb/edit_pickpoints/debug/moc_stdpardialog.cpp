/****************************************************************************
** Meta object code from reading C++ file 'stdpardialog.h'
**
** Created: Sun Sep 2 10:27:10 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../humandb/stdpardialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stdpardialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QColorButton[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QColorButton[] = {
    "QColorButton\0\0pickColor()\0"
};

const QMetaObject QColorButton::staticMetaObject = {
    { &QHBoxLayout::staticMetaObject, qt_meta_stringdata_QColorButton,
      qt_meta_data_QColorButton, 0 }
};

const QMetaObject *QColorButton::metaObject() const
{
    return &staticMetaObject;
}

void *QColorButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QColorButton))
        return static_cast<void*>(const_cast< QColorButton*>(this));
    return QHBoxLayout::qt_metacast(_clname);
}

int QColorButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHBoxLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: pickColor(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_AbsPercWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x0a,
      50,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AbsPercWidget[] = {
    "AbsPercWidget\0\0newv\0on_absSB_valueChanged(double)\0"
    "on_percSB_valueChanged(double)\0"
};

const QMetaObject AbsPercWidget::staticMetaObject = {
    { &QGridLayout::staticMetaObject, qt_meta_stringdata_AbsPercWidget,
      qt_meta_data_AbsPercWidget, 0 }
};

const QMetaObject *AbsPercWidget::metaObject() const
{
    return &staticMetaObject;
}

void *AbsPercWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AbsPercWidget))
        return static_cast<void*>(const_cast< AbsPercWidget*>(this));
    return QGridLayout::qt_metacast(_clname);
}

int AbsPercWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGridLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_absSB_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: on_percSB_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_Point3fWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Point3fWidget[] = {
    "Point3fWidget\0\0val\0setValue(vcg::Point3f)\0"
};

const QMetaObject Point3fWidget::staticMetaObject = {
    { &QGridLayout::staticMetaObject, qt_meta_stringdata_Point3fWidget,
      qt_meta_data_Point3fWidget, 0 }
};

const QMetaObject *Point3fWidget::metaObject() const
{
    return &staticMetaObject;
}

void *Point3fWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Point3fWidget))
        return static_cast<void*>(const_cast< Point3fWidget*>(this));
    return QGridLayout::qt_metacast(_clname);
}

int Point3fWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGridLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setValue((*reinterpret_cast< vcg::Point3f(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_DynamicFloatWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      25,   20,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   43,   19,   19, 0x0a,
      62,   19,   19,   19, 0x0a,
      82,   73,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DynamicFloatWidget[] = {
    "DynamicFloatWidget\0\0mask\0valueChanged(int)\0"
    "newv\0setValue(int)\0setValue()\0newValue\0"
    "setValue(float)\0"
};

const QMetaObject DynamicFloatWidget::staticMetaObject = {
    { &QGridLayout::staticMetaObject, qt_meta_stringdata_DynamicFloatWidget,
      qt_meta_data_DynamicFloatWidget, 0 }
};

const QMetaObject *DynamicFloatWidget::metaObject() const
{
    return &staticMetaObject;
}

void *DynamicFloatWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DynamicFloatWidget))
        return static_cast<void*>(const_cast< DynamicFloatWidget*>(this));
    return QGridLayout::qt_metacast(_clname);
}

int DynamicFloatWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGridLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: setValue(); break;
        case 3: setValue((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DynamicFloatWidget::valueChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_StdParFrame[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_StdParFrame[] = {
    "StdParFrame\0\0mask\0dynamicFloatChanged(int)\0"
};

const QMetaObject StdParFrame::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_StdParFrame,
      qt_meta_data_StdParFrame, 0 }
};

const QMetaObject *StdParFrame::metaObject() const
{
    return &staticMetaObject;
}

void *StdParFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StdParFrame))
        return static_cast<void*>(const_cast< StdParFrame*>(this));
    return QFrame::qt_metacast(_clname);
}

int StdParFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: dynamicFloatChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void StdParFrame::dynamicFloatChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_EnumWidget[] = {

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

static const char qt_meta_stringdata_EnumWidget[] = {
    "EnumWidget\0"
};

const QMetaObject EnumWidget::staticMetaObject = {
    { &QHBoxLayout::staticMetaObject, qt_meta_stringdata_EnumWidget,
      qt_meta_data_EnumWidget, 0 }
};

const QMetaObject *EnumWidget::metaObject() const
{
    return &staticMetaObject;
}

void *EnumWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EnumWidget))
        return static_cast<void*>(const_cast< EnumWidget*>(this));
    return QHBoxLayout::qt_metacast(_clname);
}

int EnumWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHBoxLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QVariantListWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      29,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QVariantListWidget[] = {
    "QVariantListWidget\0\0addRow()\0removeRow()\0"
};

const QMetaObject QVariantListWidget::staticMetaObject = {
    { &QHBoxLayout::staticMetaObject, qt_meta_stringdata_QVariantListWidget,
      qt_meta_data_QVariantListWidget, 0 }
};

const QMetaObject *QVariantListWidget::metaObject() const
{
    return &staticMetaObject;
}

void *QVariantListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QVariantListWidget))
        return static_cast<void*>(const_cast< QVariantListWidget*>(this));
    return QHBoxLayout::qt_metacast(_clname);
}

int QVariantListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHBoxLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addRow(); break;
        case 1: removeRow(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_GetFileNameWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GetFileNameWidget[] = {
    "GetFileNameWidget\0\0launchGetFileNameDialog()\0"
};

const QMetaObject GetFileNameWidget::staticMetaObject = {
    { &QVBoxLayout::staticMetaObject, qt_meta_stringdata_GetFileNameWidget,
      qt_meta_data_GetFileNameWidget, 0 }
};

const QMetaObject *GetFileNameWidget::metaObject() const
{
    return &staticMetaObject;
}

void *GetFileNameWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GetFileNameWidget))
        return static_cast<void*>(const_cast< GetFileNameWidget*>(this));
    return QVBoxLayout::qt_metacast(_clname);
}

int GetFileNameWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QVBoxLayout::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: launchGetFileNameDialog(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
static const uint qt_meta_data_GenericParamDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      32,   19,   19,   19, 0x0a,
      45,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GenericParamDialog[] = {
    "GenericParamDialog\0\0getAccept()\0"
    "toggleHelp()\0resetValues()\0"
};

const QMetaObject GenericParamDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_GenericParamDialog,
      qt_meta_data_GenericParamDialog, 0 }
};

const QMetaObject *GenericParamDialog::metaObject() const
{
    return &staticMetaObject;
}

void *GenericParamDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GenericParamDialog))
        return static_cast<void*>(const_cast< GenericParamDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int GenericParamDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: getAccept(); break;
        case 1: toggleHelp(); break;
        case 2: resetValues(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
static const uint qt_meta_data_MeshlabStdDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      31,   17,   17,   17, 0x08,
      44,   17,   17,   17, 0x08,
      58,   17,   17,   17, 0x08,
      71,   17,   17,   17, 0x08,
      87,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MeshlabStdDialog[] = {
    "MeshlabStdDialog\0\0applyClick()\0"
    "closeClick()\0resetValues()\0toggleHelp()\0"
    "togglePreview()\0applyDynamic()\0"
};

const QMetaObject MeshlabStdDialog::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_MeshlabStdDialog,
      qt_meta_data_MeshlabStdDialog, 0 }
};

const QMetaObject *MeshlabStdDialog::metaObject() const
{
    return &staticMetaObject;
}

void *MeshlabStdDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MeshlabStdDialog))
        return static_cast<void*>(const_cast< MeshlabStdDialog*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int MeshlabStdDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: applyClick(); break;
        case 1: closeClick(); break;
        case 2: resetValues(); break;
        case 3: toggleHelp(); break;
        case 4: togglePreview(); break;
        case 5: applyDynamic(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
