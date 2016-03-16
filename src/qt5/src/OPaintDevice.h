#ifdef MRVN_QT5_OPAINTDEVICE_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OPAINTDEVICE_H
#define MRVN_QT5_OPAINTDEVICE_H
#define MRVN_QT5_OPAINTDEVICE_H__INSIDE

#include "OClass.h"

class QPaintDevice;

class OPaintDevice : public virtual OClass {
public:
    OPaintDevice();
    virtual ~OPaintDevice();
};

#undef MRVN_QT5_OPAINTDEVICE_H__INSIDE
#endif // #ifndef MRVN_QT5_OPAINTDEVICE_H
