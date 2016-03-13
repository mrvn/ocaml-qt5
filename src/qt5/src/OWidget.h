#ifdef MRVN_QT5_OWIDGET_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OWIDGET_H
#define MRVN_QT5_OWIDGET_H
#define MRVN_QT5_OWIDGET_H__INSIDE

#include "OObject.h"

class OLayout;

class OWidget : public virtual OObject {
public:
    OWidget();
    virtual ~OWidget();
    void setLayout(OLayout *layout);
    /*
    virtual void keyPressEvent(QKeyEvent * event) {
	fprintf(stderr, "%p <0x%lx>->%s(%p)\n", this, OWidget<Q>::proxy(), __PRETTY_FUNCTION__, event);
	Q::keyPressEvent(event);
    }
    */
};

template<class O, class Q>
class TWidget : public TObject<O, Q> {
public:
    template<typename ... A>
    TWidget(A && ... a) : TObject<O, Q>(std::forward<A>(a) ...) {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TWidget() {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
};

using OQWidget = TWidget<OWidget, QWidget>;

#undef MRVN_QT5_OWIDGET_H__INSIDE
#endif // #ifndef MRVN_QT5_OWIDGET_H
