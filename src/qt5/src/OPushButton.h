#ifdef MRVN_QT5_OPUSHBUTTON_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OPUSHBUTTON_H
#define MRVN_QT5_OPUSHBUTTON_H
#define MRVN_QT5_OPUSHBUTTON_H__INSIDE

#include "OAbstractButton.h"

class OPushButton : public OAbstractButton {
public:
    OPushButton();
    virtual ~OPushButton();
};

template<class O, class Q>
class TPushButton : public TAbstractButton<O, Q> {
public:
    template<typename ... A>
    TPushButton(QString text, A && ... a) : TAbstractButton<O, Q>(text, std::forward<A>(a) ...) {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TPushButton() {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
};

using OQPushButton = TPushButton<OPushButton, QPushButton>;

#undef MRVN_QT5_OPUSHBUTTON_H__INSIDE
#endif // #ifndef MRVN_QT5_OPUSHBUTTON_H
