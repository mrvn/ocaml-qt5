#ifdef MRVN_QT5_ORECT_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_ORECT_H
#define MRVN_QT5_ORECT_H
#define MRVN_QT5_ORECT_H__INSIDE

#include <utility>

#include "OClass.h"

class QRect;

class ORect : public virtual OClass {
public:
    ORect();
    virtual ~ORect();
};

class OQRect : public ORect, public QRect {
public:
    OQRect(int x, int y, int w, int h);
    virtual ~OQRect();
};

extern "C" value caml_mrvn_QT5_ORect_alloc(int x, int y, int w, int h);

#undef MRVN_QT5_ORECT_H__INSIDE
#endif // #ifndef MRVN_QT5_ORECT_H
