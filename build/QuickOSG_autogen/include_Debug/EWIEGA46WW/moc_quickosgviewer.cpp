/****************************************************************************
** Meta object code from reading C++ file 'quickosgviewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../quickosgviewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quickosgviewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QuickOSGViewer_t {
    QByteArrayData data[21];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QuickOSGViewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QuickOSGViewer_t qt_meta_stringdata_QuickOSGViewer = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QuickOSGViewer"
QT_MOC_LITERAL(1, 15, 16), // "framerateChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 12), // "sceneChanged"
QT_MOC_LITERAL(4, 46, 19), // "hoverEnabledChanged"
QT_MOC_LITERAL(5, 66, 13), // "cameraChanged"
QT_MOC_LITERAL(6, 80, 4), // "home"
QT_MOC_LITERAL(7, 85, 6), // "lookAt"
QT_MOC_LITERAL(8, 92, 3), // "eye"
QT_MOC_LITERAL(9, 96, 6), // "center"
QT_MOC_LITERAL(10, 103, 2), // "up"
QT_MOC_LITERAL(11, 106, 12), // "addOperation"
QT_MOC_LITERAL(12, 119, 15), // "osg::Operation*"
QT_MOC_LITERAL(13, 135, 9), // "operation"
QT_MOC_LITERAL(14, 145, 10), // "clearColor"
QT_MOC_LITERAL(15, 156, 12), // "hoverEnabled"
QT_MOC_LITERAL(16, 169, 5), // "scene"
QT_MOC_LITERAL(17, 175, 10), // "osg::Node*"
QT_MOC_LITERAL(18, 186, 9), // "framerate"
QT_MOC_LITERAL(19, 196, 6), // "camera"
QT_MOC_LITERAL(20, 203, 12) // "osg::Camera*"

    },
    "QuickOSGViewer\0framerateChanged\0\0"
    "sceneChanged\0hoverEnabledChanged\0"
    "cameraChanged\0home\0lookAt\0eye\0center\0"
    "up\0addOperation\0osg::Operation*\0"
    "operation\0clearColor\0hoverEnabled\0"
    "scene\0osg::Node*\0framerate\0camera\0"
    "osg::Camera*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QuickOSGViewer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       5,   64, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,
       5,    0,   52,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       6,    0,   53,    2, 0x02 /* Public */,
       7,    3,   54,    2, 0x02 /* Public */,
      11,    1,   61,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVector3D, QMetaType::QVector3D, QMetaType::QVector3D,    8,    9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,

 // properties: name, type, flags
      14, QMetaType::QColor, 0x00095103,
      15, QMetaType::Bool, 0x00495103,
      16, 0x80000000 | 17, 0x0049510b,
      18, QMetaType::Int, 0x00495103,
      19, 0x80000000 | 20, 0x0049510b,

 // properties: notify_signal_id
       0,
       2,
       1,
       0,
       3,

       0        // eod
};

void QuickOSGViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QuickOSGViewer *_t = static_cast<QuickOSGViewer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->framerateChanged(); break;
        case 1: _t->sceneChanged(); break;
        case 2: _t->hoverEnabledChanged(); break;
        case 3: _t->cameraChanged(); break;
        case 4: _t->home(); break;
        case 5: _t->lookAt((*reinterpret_cast< QVector3D(*)>(_a[1])),(*reinterpret_cast< QVector3D(*)>(_a[2])),(*reinterpret_cast< QVector3D(*)>(_a[3]))); break;
        case 6: _t->addOperation((*reinterpret_cast< osg::Operation*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< osg::Operation* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (QuickOSGViewer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QuickOSGViewer::framerateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QuickOSGViewer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QuickOSGViewer::sceneChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QuickOSGViewer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QuickOSGViewer::hoverEnabledChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QuickOSGViewer::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QuickOSGViewer::cameraChanged)) {
                *result = 3;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< osg::Node* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        QuickOSGViewer *_t = static_cast<QuickOSGViewer *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->clearColor(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->hoverEnabled(); break;
        case 2: *reinterpret_cast< osg::Node**>(_v) = _t->scene(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->framerate(); break;
        case 4: *reinterpret_cast< osg::Camera**>(_v) = _t->camera(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        QuickOSGViewer *_t = static_cast<QuickOSGViewer *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setClearColor(*reinterpret_cast< QColor*>(_v)); break;
        case 1: _t->setHoverEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setScene(*reinterpret_cast< osg::Node**>(_v)); break;
        case 3: _t->setFramerate(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setCamera(*reinterpret_cast< osg::Camera**>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject QuickOSGViewer::staticMetaObject = {
    { &QQuickFramebufferObject::staticMetaObject, qt_meta_stringdata_QuickOSGViewer.data,
      qt_meta_data_QuickOSGViewer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QuickOSGViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QuickOSGViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QuickOSGViewer.stringdata0))
        return static_cast<void*>(this);
    return QQuickFramebufferObject::qt_metacast(_clname);
}

int QuickOSGViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickFramebufferObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QuickOSGViewer::framerateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QuickOSGViewer::sceneChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QuickOSGViewer::hoverEnabledChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void QuickOSGViewer::cameraChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
