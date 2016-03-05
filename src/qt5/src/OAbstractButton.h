#ifndef MRVN_QT5_OABSTRACTBUTTON_H
#define MRVN_QT5_OABSTRACTBUTTON_H

#include <stdio.h>

#include "OWidget.h"

template<class Q>
class OAbstractButton : public OWidget<Q> {
public:
    template<typename ... A>
    OAbstractButton(A && ... a) : OWidget<Q>(a...) {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, OWidget<Q>::proxy(), __PRETTY_FUNCTION__);
    }
    virtual ~OAbstractButton() {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, OWidget<Q>::proxy(), __PRETTY_FUNCTION__);
    }
private:
};

#endif // #ifndef MRVN_QT5_OABSTRACTBUTTON_H
