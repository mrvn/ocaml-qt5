#ifndef MRVN_QT5_OWIDGET_H
#define MRVN_QT5_OWIDGET_H

#include <QObject>
#include <stdio.h>

#include "OObject.h"

template<class Q>
class OWidget : public OObject<Q> {
public:
    template<typename ... A>
    OWidget(A && ... a) : OObject<Q>(a...) {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, OObject<Q>::proxy(), __PRETTY_FUNCTION__);
    }
    virtual ~OWidget() {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, OObject<Q>::proxy(), __PRETTY_FUNCTION__);
    }
private:
};

#endif // #ifndef MRVN_QT5_OWIDGET_H
