#ifdef MRVN_QT5_OOBJECT_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OOBJECT_H
#define MRVN_QT5_OOBJECT_H
#define MRVN_QT5_OOBJECT_H__INSIDE

#include "OClass.h"

class QObject;

class OObject : public OClass {
public:
    OObject();
    virtual ~OObject();
    virtual void preDestructor();
    virtual bool event(QEvent *event);
};

class OQObject : public OObject, public QObject {
public:
    virtual ~OQObject();
};

#undef MRVN_QT5_OOBJECT_H__INSIDE
#endif // #ifndef MRVN_QT5_OOBJECT_H
