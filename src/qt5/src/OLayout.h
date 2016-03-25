#ifdef MRVN_QT5_OLAYOUT_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OLAYOUT_H
#define MRVN_QT5_OLAYOUT_H
#define MRVN_QT5_OLAYOUT_H__INSIDE

#include <utility>

#include "debug.h"
#include "OObject.h"
#include "OLayoutItem.h"

class OWidget;

class OLayout : public virtual OObject, public virtual OLayoutItem {
public:
    OLayout();
    virtual ~OLayout();
    virtual void preDestructor();
    void addWidget(OWidget *widget);
};

template<class O, class Q>
class TLayout : public TObject<O, Q> {
public:
    template<typename ... A>
    TLayout(A && ... a) : TObject<O, Q>(std::forward<A>(a) ...) {
	DEBUG("%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TLayout() {
	DEBUG("%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
};

using OQLayout = TLayout<OLayout, QLayout>;

#undef MRVN_QT5_OLAYOUT_H__INSIDE
#endif // #ifndef MRVN_QT5_OLAYOUT_H
