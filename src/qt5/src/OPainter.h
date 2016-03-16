#ifdef MRVN_QT5_OPAINTER_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OPAINTER_H
#define MRVN_QT5_OPAINTER_H
#define MRVN_QT5_OPAINTER_H__INSIDE

#include <utility>

#include "OClass.h"
#include "OPaintDevice.h"

class QPainter;

class OPainter : public virtual OClass {
public:
    OPainter(OPaintDevice *device);
    virtual ~OPainter();
private:
    OPaintDevice *device_;
};

template<class O, class Q>
class TPainter : public virtual O, public Q {
public:
    template<typename ... A>
    TPainter(OPaintDevice *device, A && ... a) : O(device), Q(dynamic_cast<QPaintDevice *>(device), std::forward<A>(a) ...) {
	fprintf(stderr, "%p [0x%lx]->%s(%p)\n", this, O::maybe_obj(), __PRETTY_FUNCTION__, device);
    }
    virtual ~TPainter() {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
};

using OQPainter = TPainter<OPainter, QPainter>;

#undef MRVN_QT5_OPAINTER_H__INSIDE
#endif // #ifndef MRVN_QT5_OPAINTER_H
