#ifdef MRVN_QT5_OABSTRACTBUTTON_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OABSTRACTBUTTON_H
#define MRVN_QT5_OABSTRACTBUTTON_H
#define MRVN_QT5_OABSTRACTBUTTON_H__INSIDE

#include "OWidget.h"

class OAbstractButton : public OWidget {
public:
    OAbstractButton();
    virtual ~OAbstractButton();
};

template<class O, class Q>
class TAbstractButton : public TWidget<O, Q> {
public:
    template<typename ... A>
    TAbstractButton(A && ... a) : TWidget<O, Q>(std::forward<A>(a) ...) {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TAbstractButton() {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
};

using OQAbstractButton = TAbstractButton<OAbstractButton, QAbstractButton>;

#undef MRVN_QT5_OABSTRACTBUTTON_H__INSIDE
#endif // #ifndef MRVN_QT5_OABSTRACTBUTTON_H
