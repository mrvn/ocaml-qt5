#ifdef MRVN_QT5_OLCDNUMBER_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OLCDNUMBER_H
#define MRVN_QT5_OLCDNUMBER_H
#define MRVN_QT5_OLCDNUMBER_H__INSIDE

#include <utility>

#include "debug.h"
#include "OFrame.h"

class OLCDNumber : public OFrame {
public:
    OLCDNumber();
    virtual ~OLCDNumber();
};

template<class O, class Q>
class TLCDNumber : public TFrame<O, Q> {
public:
    template<typename ... A>
    TLCDNumber(int numDigits, A && ... a) : TFrame<O, Q>(numDigits, std::forward<A>(a) ...) {
	DEBUG("%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TLCDNumber() {
	DEBUG("%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
};

using OQLCDNumber = TLCDNumber<OLCDNumber, QLCDNumber>;

#undef MRVN_QT5_OLCDNUMBER_H__INSIDE
#endif // #ifndef MRVN_QT5_OLCDNUMBER_H
