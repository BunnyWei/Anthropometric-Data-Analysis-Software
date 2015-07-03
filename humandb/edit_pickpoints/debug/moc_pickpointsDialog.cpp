/****************************************************************************
** Meta object code from reading C++ file 'pickpointsDialog.h'
**
** Created: Sun Sep 2 10:27:11 2012
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pickpointsDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pickpointsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PickPointsDialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      33,   17,   17,   17, 0x08,
      58,   17,   17,   17, 0x08,
     100,   17,   17,   17, 0x08,
     125,   17,   17,   17, 0x08,
     150,   17,   17,   17, 0x08,
     182,  174,   17,   17, 0x08,
     203,  174,   17,   17, 0x08,
     224,  174,   17,   17, 0x08,
     247,   17,   17,   17, 0x08,
     266,   17,   17,   17, 0x08,
     296,   17,   17,   17, 0x08,
     323,   17,   17,   17, 0x08,
     343,   17,   17,   17, 0x08,
     375,   17,   17,   17, 0x08,
     404,   17,   17,   17, 0x08,
     425,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PickPointsDialog[] = {
    "PickPointsDialog\0\0redrawPoints()\0"
    "on_showItemBtn_clicked()\0"
    "on_groupComboBox_currentIndexChanged(int)\0"
    "removeHighlightedPoint()\0"
    "renameHighlightedPoint()\0"
    "clearHighlightedPoint()\0checked\0"
    "togglePickMode(bool)\0toggleMoveMode(bool)\0"
    "toggleSelectMode(bool)\0savePointsToFile()\0"
    "askUserForFileAndLoadPoints()\0"
    "clearPointsButtonClicked()\0"
    "savePointTemplate()\0askUserForFileAndloadTemplate()\0"
    "clearTemplateButtonClicked()\0"
    "addPointToTemplate()\0undo()\0"
};

const QMetaObject PickPointsDialog::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_PickPointsDialog,
      qt_meta_data_PickPointsDialog, 0 }
};

const QMetaObject *PickPointsDialog::metaObject() const
{
    return &staticMetaObject;
}

void *PickPointsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PickPointsDialog))
        return static_cast<void*>(const_cast< PickPointsDialog*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int PickPointsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: redrawPoints(); break;
        case 1: on_showItemBtn_clicked(); break;
        case 2: on_groupComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: removeHighlightedPoint(); break;
        case 4: renameHighlightedPoint(); break;
        case 5: clearHighlightedPoint(); break;
        case 6: togglePickMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: toggleMoveMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: toggleSelectMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: savePointsToFile(); break;
        case 10: askUserForFileAndLoadPoints(); break;
        case 11: clearPointsButtonClicked(); break;
        case 12: savePointTemplate(); break;
        case 13: askUserForFileAndloadTemplate(); break;
        case 14: clearTemplateButtonClicked(); break;
        case 15: addPointToTemplate(); break;
        case 16: undo(); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}
static const uint qt_meta_data_TreeCheckBox[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      22,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TreeCheckBox[] = {
    "TreeCheckBox\0\0checked\0toggleAndDraw(bool)\0"
};

const QMetaObject TreeCheckBox::staticMetaObject = {
    { &QCheckBox::staticMetaObject, qt_meta_stringdata_TreeCheckBox,
      qt_meta_data_TreeCheckBox, 0 }
};

const QMetaObject *TreeCheckBox::metaObject() const
{
    return &staticMetaObject;
}

void *TreeCheckBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TreeCheckBox))
        return static_cast<void*>(const_cast< TreeCheckBox*>(this));
    return QCheckBox::qt_metacast(_clname);
}

int TreeCheckBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCheckBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: toggleAndDraw((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
