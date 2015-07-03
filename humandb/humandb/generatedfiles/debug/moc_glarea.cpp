/****************************************************************************
** Meta object code from reading C++ file 'glarea.h'
**
** Created: Mon Sep 3 15:59:28 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../glarea.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glarea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLArea[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      41,   32,    7,    7, 0x05,
      79,   32,    7,    7, 0x05,
     117,   32,    7,    7, 0x05,
     158,   32,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     198,    7,    7,    7, 0x0a,
     219,  214,    7,    7, 0x0a,
     251,  214,    7,    7, 0x0a,
     285,  214,    7,    7, 0x0a,
     323,    7,    7,    7, 0x0a,
     341,  333,    7,    7, 0x0a,
     369,    7,    7,    7, 0x0a,
     396,  389,    7,    7, 0x0a,
     430,  425,    7,    7, 0x0a,
     451,  425,    7,    7, 0x0a,
     475,  425,    7,    7, 0x0a,
     496,  425,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GLArea[] = {
    "GLArea\0\0updateMainWindowMenus()\0"
    "name,dir\0transmitViewDir(QString,vcg::Point3f)\0"
    "transmitViewPos(QString,vcg::Point3f)\0"
    "transmitSurfacePos(QString,vcg::Point3f)\0"
    "transmitCameraPos(QString,vcg::Point3f)\0"
    "updateTexture()\0mode\0"
    "setDrawMode(vcg::GLW::DrawMode)\0"
    "setColorMode(vcg::GLW::ColorMode)\0"
    "setTextureMode(vcg::GLW::TextureMode)\0"
    "endEdit()\0enabled\0setSelectionRendering(bool)\0"
    "suspendEditToggle()\0meshId\0"
    "setCurrentlyActiveLayer(int)\0name\0"
    "sendViewPos(QString)\0sendSurfacePos(QString)\0"
    "sendViewDir(QString)\0sendCameraPos(QString)\0"
};

const QMetaObject GLArea::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GLArea,
      qt_meta_data_GLArea, 0 }
};

const QMetaObject *GLArea::metaObject() const
{
    return &staticMetaObject;
}

void *GLArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLArea))
        return static_cast<void*>(const_cast< GLArea*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GLArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateMainWindowMenus(); break;
        case 1: transmitViewDir((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< vcg::Point3f(*)>(_a[2]))); break;
        case 2: transmitViewPos((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< vcg::Point3f(*)>(_a[2]))); break;
        case 3: transmitSurfacePos((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< vcg::Point3f(*)>(_a[2]))); break;
        case 4: transmitCameraPos((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< vcg::Point3f(*)>(_a[2]))); break;
        case 5: updateTexture(); break;
        case 6: setDrawMode((*reinterpret_cast< vcg::GLW::DrawMode(*)>(_a[1]))); break;
        case 7: setColorMode((*reinterpret_cast< vcg::GLW::ColorMode(*)>(_a[1]))); break;
        case 8: setTextureMode((*reinterpret_cast< vcg::GLW::TextureMode(*)>(_a[1]))); break;
        case 9: endEdit(); break;
        case 10: setSelectionRendering((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: suspendEditToggle(); break;
        case 12: setCurrentlyActiveLayer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: sendViewPos((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: sendSurfacePos((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: sendViewDir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: sendCameraPos((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void GLArea::updateMainWindowMenus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GLArea::transmitViewDir(QString _t1, vcg::Point3f _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GLArea::transmitViewPos(QString _t1, vcg::Point3f _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GLArea::transmitSurfacePos(QString _t1, vcg::Point3f _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GLArea::transmitCameraPos(QString _t1, vcg::Point3f _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
