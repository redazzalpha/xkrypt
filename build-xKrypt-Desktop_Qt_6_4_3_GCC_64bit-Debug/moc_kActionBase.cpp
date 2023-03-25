/****************************************************************************
** Meta object code from reading C++ file 'kActionBase.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../kActionBase.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kActionBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_KActionBase_t {
    uint offsetsAndSizes[14];
    char stringdata0[12];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[5];
    char stringdata5[5];
    char stringdata6[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_KActionBase_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_KActionBase_t qt_meta_stringdata_KActionBase = {
    {
        QT_MOC_LITERAL(0, 11),  // "KActionBase"
        QT_MOC_LITERAL(12, 12),  // "setStackPage"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 4),  // "Page"
        QT_MOC_LITERAL(31, 4),  // "page"
        QT_MOC_LITERAL(36, 4),  // "quit"
        QT_MOC_LITERAL(41, 13)   // "onActionClick"
    },
    "KActionBase",
    "setStackPage",
    "",
    "Page",
    "page",
    "quit",
    "onActionClick"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_KActionBase[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x06,    1 /* Public */,
       5,    0,   35,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   36,    2, 0x0a,    4 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject KActionBase::staticMetaObject = { {
    QMetaObject::SuperData::link<QAction::staticMetaObject>(),
    qt_meta_stringdata_KActionBase.offsetsAndSizes,
    qt_meta_data_KActionBase,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_KActionBase_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<KActionBase, std::true_type>,
        // method 'setStackPage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<Page, std::false_type>,
        // method 'quit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onActionClick'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void KActionBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<KActionBase *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setStackPage((*reinterpret_cast< std::add_pointer_t<Page>>(_a[1]))); break;
        case 1: _t->quit(); break;
        case 2: _t->onActionClick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (KActionBase::*)(Page );
            if (_t _q_method = &KActionBase::setStackPage; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (KActionBase::*)();
            if (_t _q_method = &KActionBase::quit; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *KActionBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KActionBase::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KActionBase.stringdata0))
        return static_cast<void*>(this);
    return QAction::qt_metacast(_clname);
}

int KActionBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void KActionBase::setStackPage(Page _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KActionBase::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
