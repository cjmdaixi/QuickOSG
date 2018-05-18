/****************************************************************************
** Meta object code from reading C++ file 'appglobal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../appglobal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appglobal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AppGlobal_t {
    QByteArrayData data[20];
    char stringdata0[209];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AppGlobal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AppGlobal_t qt_meta_stringdata_AppGlobal = {
    {
QT_MOC_LITERAL(0, 0, 9), // "AppGlobal"
QT_MOC_LITERAL(1, 10, 17), // "fontFamilyChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "minimize"
QT_MOC_LITERAL(4, 38, 8), // "maximize"
QT_MOC_LITERAL(5, 47, 7), // "tryQuit"
QT_MOC_LITERAL(6, 55, 4), // "quit"
QT_MOC_LITERAL(7, 60, 16), // "sceneNodeChanged"
QT_MOC_LITERAL(8, 77, 13), // "loadModelFile"
QT_MOC_LITERAL(9, 91, 10), // "osg::Node*"
QT_MOC_LITERAL(10, 102, 8), // "filePath"
QT_MOC_LITERAL(11, 111, 8), // "iconText"
QT_MOC_LITERAL(12, 120, 8), // "iconName"
QT_MOC_LITERAL(13, 129, 11), // "fontAwesome"
QT_MOC_LITERAL(14, 141, 10), // "fontFamily"
QT_MOC_LITERAL(15, 152, 12), // "majorVersion"
QT_MOC_LITERAL(16, 165, 12), // "minorVersion"
QT_MOC_LITERAL(17, 178, 12), // "patchVersion"
QT_MOC_LITERAL(18, 191, 7), // "version"
QT_MOC_LITERAL(19, 199, 9) // "sceneNode"

    },
    "AppGlobal\0fontFamilyChanged\0\0minimize\0"
    "maximize\0tryQuit\0quit\0sceneNodeChanged\0"
    "loadModelFile\0osg::Node*\0filePath\0"
    "iconText\0iconName\0fontAwesome\0fontFamily\0"
    "majorVersion\0minorVersion\0patchVersion\0"
    "version\0sceneNode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AppGlobal[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       7,   66, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,
       6,    0,   58,    2, 0x06 /* Public */,
       7,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   60,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      11,    1,   63,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    0x80000000 | 9, QMetaType::QString,   10,

 // methods: parameters
    QMetaType::QString, QMetaType::QString,   12,

 // properties: name, type, flags
      13, QMetaType::QString, 0x00095401,
      14, QMetaType::QString, 0x00495003,
      15, QMetaType::Int, 0x00095401,
      16, QMetaType::Int, 0x00095401,
      17, QMetaType::Int, 0x00095401,
      18, QMetaType::QString, 0x00095401,
      19, 0x80000000 | 9, 0x00495009,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       0,
       0,
       5,

       0        // eod
};

void AppGlobal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AppGlobal *_t = static_cast<AppGlobal *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fontFamilyChanged(); break;
        case 1: _t->minimize(); break;
        case 2: _t->maximize(); break;
        case 3: _t->tryQuit(); break;
        case 4: _t->quit(); break;
        case 5: _t->sceneNodeChanged(); break;
        case 6: { osg::Node* _r = _t->loadModelFile((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< osg::Node**>(_a[0]) = std::move(_r); }  break;
        case 7: { QString _r = _t->iconText((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (AppGlobal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppGlobal::fontFamilyChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AppGlobal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppGlobal::minimize)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AppGlobal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppGlobal::maximize)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (AppGlobal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppGlobal::tryQuit)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (AppGlobal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppGlobal::quit)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (AppGlobal::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppGlobal::sceneNodeChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        AppGlobal *_t = static_cast<AppGlobal *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->fontAwesome(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->m_fontFamily; break;
        case 2: *reinterpret_cast< int*>(_v) = _t->majorVersion(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->minorVersion(); break;
        case 4: *reinterpret_cast< int*>(_v) = _t->patchVersion(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->version(); break;
        case 6: *reinterpret_cast< osg::Node**>(_v) = _t->sceneNode(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        AppGlobal *_t = static_cast<AppGlobal *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 1:
            if (_t->m_fontFamily != *reinterpret_cast< QString*>(_v)) {
                _t->m_fontFamily = *reinterpret_cast< QString*>(_v);
                Q_EMIT _t->fontFamilyChanged();
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject AppGlobal::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AppGlobal.data,
      qt_meta_data_AppGlobal,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AppGlobal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppGlobal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AppGlobal.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AppGlobal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AppGlobal::fontFamilyChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AppGlobal::minimize()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AppGlobal::maximize()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AppGlobal::tryQuit()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void AppGlobal::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void AppGlobal::sceneNodeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
