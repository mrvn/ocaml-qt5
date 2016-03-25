#ifdef MRVN_QT5_OPIXMAP_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OPIXMAP_H
#define MRVN_QT5_OPIXMAP_H
#define MRVN_QT5_OPIXMAP_H__INSIDE

#include <QSize>

#include <utility>

#include "debug.h"
#include "OClass.h"
#include "OPaintDevice.h"

class OPixmap : public virtual OClass, public virtual OPaintDevice {
public:
    OPixmap();
    virtual ~OPixmap();
};

template<class O, class Q>
class TPixmap : public TClass<O, Q> {
public:
    template<typename ... A>
    TPixmap(int width, int height, A && ... a) : TClass<O, Q>(width, height, std::forward<A>(a) ...) {
	DEBUG("%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TPixmap() {
	DEBUG("%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
};

using OQPixmap = TPixmap<OPixmap, QPixmap>;

#undef MRVN_QT5_OPIXMAP_H__INSIDE
#endif // #ifndef MRVN_QT5_OPIXMAP_H
