#ifdef MRVN_QT5_OPAINTDEVICE_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OPAINTDEVICE_H
#define MRVN_QT5_OPAINTDEVICE_H
#define MRVN_QT5_OPAINTDEVICE_H__INSIDE

#include "OClass.h"

class QPaintDevice;
class OPainter;

class OPaintDevice : public virtual OClass {
public:
    OPaintDevice();
    virtual ~OPaintDevice();
    void registerPainter(OPainter *painter);
    void unregisterPainter(OPainter *painter);
private:
    OPainter *painter_;
};

#undef MRVN_QT5_OPAINTDEVICE_H__INSIDE
#endif // #ifndef MRVN_QT5_OPAINTDEVICE_H
