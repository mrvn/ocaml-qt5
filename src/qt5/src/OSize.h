#ifdef MRVN_QT5_OSIZE_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OSIZE_H
#define MRVN_QT5_OSIZE_H
#define MRVN_QT5_OSIZE_H__INSIDE

#include <utility>

#include "OClass.h"

class QSize;

class OSize : public virtual OClass {
public:
    OSize();
    virtual ~OSize();
};

class OQSize : public OSize, public QSize {
public:
    OQSize(int width, int height);
    virtual ~OQSize();
};

extern "C" value caml_mrvn_QT5_OSize_alloc(int width, int height);

#undef MRVN_QT5_OSIZE_H__INSIDE
#endif // #ifndef MRVN_QT5_OSIZE_H
