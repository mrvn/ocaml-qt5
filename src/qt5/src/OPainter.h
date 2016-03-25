#ifdef MRVN_QT5_OPAINTER_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OPAINTER_H
#define MRVN_QT5_OPAINTER_H
#define MRVN_QT5_OPAINTER_H__INSIDE

#include <utility>

#include "OClass.h"

class QPainter;
class OPaintDevice;

class OPainter : public virtual OClass {
public:
    OPainter();
    virtual ~OPainter();
    bool begin(OPaintDevice *device);
    void end();
private:
    OPaintDevice *device_;
};

template<class O, class Q>
class TPainter : public virtual O, public Q {
public:
    template<typename ... A>
    TPainter(A && ... a) : O(), Q(std::forward<A>(a) ...) {
	fprintf(stderr, "%p [0x%lx]->%s()\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TPainter() {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
};

using OQPainter = TPainter<OPainter, QPainter>;

#undef MRVN_QT5_OPAINTER_H__INSIDE
#endif // #ifndef MRVN_QT5_OPAINTER_H
