/****************************************************************************
** Meta object code from reading C++ file 'viewport.h'
**
** Created: Sat Nov 23 15:44:01 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "viewport.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ViewPort[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   10,    9,    9, 0x05,
      35,   31,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,    9,    9,    9, 0x0a,
      57,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ViewPort[] = {
    "ViewPort\0\0text\0angles(QString)\0dim\0"
    "dimen(double)\0reset()\0animate()\0"
};

void ViewPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ViewPort *_t = static_cast<ViewPort *>(_o);
        switch (_id) {
        case 0: _t->angles((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->dimen((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->reset(); break;
        case 3: _t->animate(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ViewPort::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ViewPort::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_ViewPort,
      qt_meta_data_ViewPort, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ViewPort::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ViewPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ViewPort::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ViewPort))
        return static_cast<void*>(const_cast< ViewPort*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int ViewPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ViewPort::angles(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ViewPort::dimen(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
