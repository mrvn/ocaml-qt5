#ifdef MRVN_QT5_OAPPLICATION_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OAPPLICATION_H
#define MRVN_QT5_OAPPLICATION_H
#define MRVN_QT5_OAPPLICATION_H__INSIDE

#include "debug.h"
#include "OObject.h"
#include "StringArray.h"

class OApplication : public virtual OObject {
public:
    OApplication();
    virtual ~OApplication();
};

template<class O, class Q>
class TApplication : public StringArray, public TObject<O, Q> {
public:
    template<typename ... A>
    TApplication(value ml_args, A && ... a) : StringArray(ml_args), TObject<O, Q>(argc_, argv_, std::forward<A>(a) ...) {
	DEBUG("%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TApplication() {
	DEBUG("%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
};

using OQApplication = TApplication<OApplication, QApplication>;

#undef MRVN_QT5_OAPPLICATION_H__INSIDE
#endif // #ifndef MRVN_QT5_OAPPLICATION_H
