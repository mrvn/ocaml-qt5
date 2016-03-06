#ifndef MRVN_QT5_OWIDGET_H
#define MRVN_QT5_OWIDGET_H

#include <QWidget>
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
    virtual void keyPressEvent(QKeyEvent * event) {
	fprintf(stderr, "%p <0x%lx>->%s(%p)\n", this, OWidget<Q>::proxy(), __PRETTY_FUNCTION__, event);
	Q::keyPressEvent(event);
    }
private:
};

#endif // #ifndef MRVN_QT5_OWIDGET_H
