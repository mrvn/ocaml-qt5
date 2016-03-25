#ifdef MRVN_QT5_OFRAME_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OFRAME_H
#define MRVN_QT5_OFRAME_H
#define MRVN_QT5_OFRAME_H__INSIDE

#include <utility>

#include "debug.h"
#include "OWidget.h"

class OFrame : public OWidget {
public:
    OFrame();
    virtual ~OFrame();
};

template<class O, class Q>
class TFrame : public TWidget<O, Q> {
public:
    template<typename ... A>
    TFrame(A && ... a) : TWidget<O, Q>(std::forward<A>(a) ...) {
	DEBUG("%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TFrame() {
	DEBUG("%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
};

using OQFrame = TFrame<OFrame, QFrame>;

#undef MRVN_QT5_OFRAME_H__INSIDE
#endif // #ifndef MRVN_QT5_OFRAME_H
