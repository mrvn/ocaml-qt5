#ifdef MRVN_QT5_OMAINWINDOW_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OMAINWINDOW_H
#define MRVN_QT5_OMAINWINDOW_H
#define MRVN_QT5_OMAINWINDOW_H__INSIDE

#include "OWidget.h"

class OMainWindow : public virtual OWidget {
public:
    OMainWindow();
    virtual ~OMainWindow();
    virtual void preDestructor();
    virtual void setCentralWidget(OWidget *w);
private:
    void removeCentralWidget();
};

template<class O, class Q>
class TMainWindow : public TWidget<O, Q> {
public:
    template<typename ... A>
    TMainWindow(A && ... a) : TWidget<O, Q>(std::forward<A>(a) ...) {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TMainWindow() {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
};

using OQMainWindow = TMainWindow<OMainWindow, QMainWindow>;

#undef MRVN_QT5_OMAINWINDOW_H__INSIDE
#endif // #ifndef MRVN_QT5_OMAINWINDOW_H
