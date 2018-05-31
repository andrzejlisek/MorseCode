/****************************************************************************
** Meta object code from reading C++ file 'qlabelkey.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MorseCode/qlabelkey.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qlabelkey.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QLabelKey_t {
    QByteArrayData data[10];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QLabelKey_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QLabelKey_t qt_meta_stringdata_QLabelKey = {
    {
QT_MOC_LITERAL(0, 0, 9), // "QLabelKey"
QT_MOC_LITERAL(1, 10, 8), // "KeyPress"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 10), // "QKeyEvent*"
QT_MOC_LITERAL(4, 31, 5), // "event"
QT_MOC_LITERAL(5, 37, 10), // "KeyRelease"
QT_MOC_LITERAL(6, 48, 13), // "keyPressEvent"
QT_MOC_LITERAL(7, 62, 15), // "keyReleaseEvent"
QT_MOC_LITERAL(8, 78, 10), // "paintEvent"
QT_MOC_LITERAL(9, 89, 12) // "QPaintEvent*"

    },
    "QLabelKey\0KeyPress\0\0QKeyEvent*\0event\0"
    "KeyRelease\0keyPressEvent\0keyReleaseEvent\0"
    "paintEvent\0QPaintEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QLabelKey[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   45,    2, 0x0a /* Public */,
       7,    1,   48,    2, 0x0a /* Public */,
       8,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 9,    4,

       0        // eod
};

void QLabelKey::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QLabelKey *_t = static_cast<QLabelKey *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->KeyPress((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 1: _t->KeyRelease((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 2: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 3: _t->keyReleaseEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 4: _t->paintEvent((*reinterpret_cast< QPaintEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QLabelKey::*_t)(QKeyEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QLabelKey::KeyPress)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QLabelKey::*_t)(QKeyEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QLabelKey::KeyRelease)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject QLabelKey::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_QLabelKey.data,
      qt_meta_data_QLabelKey,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QLabelKey::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QLabelKey::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QLabelKey.stringdata0))
        return static_cast<void*>(const_cast< QLabelKey*>(this));
    return QLabel::qt_metacast(_clname);
}

int QLabelKey::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QLabelKey::KeyPress(QKeyEvent * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QLabelKey::KeyRelease(QKeyEvent * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
