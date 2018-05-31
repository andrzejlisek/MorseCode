/****************************************************************************
** Meta object code from reading C++ file 'inputtext.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MorseCode/inputtext.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inputtext.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_InputText_t {
    QByteArrayData data[9];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InputText_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InputText_t qt_meta_stringdata_InputText = {
    {
QT_MOC_LITERAL(0, 0, 9), // "InputText"
QT_MOC_LITERAL(1, 10, 16), // "on_SendB_clicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "KeyPress"
QT_MOC_LITERAL(4, 37, 10), // "QKeyEvent*"
QT_MOC_LITERAL(5, 48, 5), // "event"
QT_MOC_LITERAL(6, 54, 10), // "KeyRelease"
QT_MOC_LITERAL(7, 65, 31), // "on_SendMode_currentIndexChanged"
QT_MOC_LITERAL(8, 97, 5) // "index"

    },
    "InputText\0on_SendB_clicked\0\0KeyPress\0"
    "QKeyEvent*\0event\0KeyRelease\0"
    "on_SendMode_currentIndexChanged\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InputText[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    1,   35,    2, 0x08 /* Private */,
       6,    1,   38,    2, 0x08 /* Private */,
       7,    1,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void InputText::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InputText *_t = static_cast<InputText *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_SendB_clicked(); break;
        case 1: _t->KeyPress((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 2: _t->KeyRelease((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 3: _t->on_SendMode_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject InputText::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InputText.data,
      qt_meta_data_InputText,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *InputText::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InputText::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_InputText.stringdata0))
        return static_cast<void*>(const_cast< InputText*>(this));
    return QDialog::qt_metacast(_clname);
}

int InputText::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
