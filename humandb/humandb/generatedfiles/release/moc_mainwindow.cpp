/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Jun 18 17:30:02 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      30,   17,   12,   11, 0x0a,
      61,   52,   12,   11, 0x2a,
      75,   11,   12,   11, 0x2a,
      89,   82,   11,   11, 0x0a,
     122,   11,   11,   11, 0x0a,
     142,   11,   11,   11, 0x0a,
     155,   11,   11,   11, 0x0a,
     172,   11,   11,   11, 0x0a,
     185,   11,   11,   11, 0x0a,
     199,   11,   11,   11, 0x0a,
     216,   11,   11,   11, 0x0a,
     226,   11,   11,   11, 0x0a,
     242,   11,   11,   11, 0x0a,
     258,   11,   11,   11, 0x0a,
     271,   11,   11,   11, 0x0a,
     286,   11,   11,   11, 0x0a,
     303,   11,   11,   11, 0x0a,
     320,   11,   11,   11, 0x0a,
     337,   11,   11,   11, 0x0a,
     359,   11,   11,   11, 0x0a,
     375,   11,   11,   11, 0x0a,
     391,   11,   11,   11, 0x0a,
     398,   11,   11,   11, 0x0a,
     408,   11,   11,   11, 0x0a,
     427,   11,   11,   11, 0x0a,
     444,   11,   11,   11, 0x0a,
     458,   11,   11,   11, 0x0a,
     474,   11,   11,   11, 0x0a,
     488,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0bool\0fileName,gla\0"
    "open(QString,GLArea*)\0fileName\0"
    "open(QString)\0open()\0window\0"
    "wrapSetActiveSubWindow(QWidget*)\0"
    "createControlDock()\0exitWindow()\0"
    "modifyPassword()\0userManage()\0"
    "basicManage()\0originalManage()\0delData()\0"
    "literalSearch()\0graphicSearch()\0"
    "staticSize()\0allParameter()\0"
    "standardPerson()\0indirectSearch()\0"
    "relativeSearch()\0correlationAnalysis()\0"
    "centileSearch()\0applyEditMode()\0help()\0"
    "showGLA()\0staticSizeSearch()\0"
    "functionSearch()\0jointSearch()\0"
    "operateSearch()\0sportSearch()\0"
    "mentalSearch()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

const QMetaObject *MainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "MainWindowInterface"))
        return static_cast< MainWindowInterface*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = open((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< GLArea*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = open((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = open();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: wrapSetActiveSubWindow((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 4: createControlDock(); break;
        case 5: exitWindow(); break;
        case 6: modifyPassword(); break;
        case 7: userManage(); break;
        case 8: basicManage(); break;
        case 9: originalManage(); break;
        case 10: delData(); break;
        case 11: literalSearch(); break;
        case 12: graphicSearch(); break;
        case 13: staticSize(); break;
        case 14: allParameter(); break;
        case 15: standardPerson(); break;
        case 16: indirectSearch(); break;
        case 17: relativeSearch(); break;
        case 18: correlationAnalysis(); break;
        case 19: centileSearch(); break;
        case 20: applyEditMode(); break;
        case 21: help(); break;
        case 22: showGLA(); break;
        case 23: staticSizeSearch(); break;
        case 24: functionSearch(); break;
        case 25: jointSearch(); break;
        case 26: operateSearch(); break;
        case 27: sportSearch(); break;
        case 28: mentalSearch(); break;
        default: ;
        }
        _id -= 29;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
