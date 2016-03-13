#ifdef MRVN_QT5_OGRIDLAYOUT_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OGRIDLAYOUT_H
#define MRVN_QT5_OGRIDLAYOUT_H
#define MRVN_QT5_OGRIDLAYOUT_H__INSIDE

#include "OLayout.h"

class OGridLayout : public OLayout {
public:
    OGridLayout();
    virtual ~OGridLayout();
    void addWidgetAt(OWidget *widget, int row, int column, int rowSpan, int columnSpan);
};

template<class O, class Q>
class TGridLayout : public TLayout<O, Q> {
public:
    template<typename ... A>
    TGridLayout(A && ... a) : TLayout<O, Q>(std::forward<A>(a) ...) {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TGridLayout() {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
};

using OQGridLayout = TGridLayout<OGridLayout, QGridLayout>;

#undef MRVN_QT5_OGRIDLAYOUT_H__INSIDE
#endif // #ifndef MRVN_QT5_OGRIDLAYOUT_H
