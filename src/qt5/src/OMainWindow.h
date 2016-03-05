#ifndef MRVN_QT5_OMAINWINDOW_H
#define MRVN_QT5_OMAINWINDOW_H

#include <stdio.h>
#include <cassert>
#include <caml/memory.h>

#include "OWidget.h"

template<class O>
class OMainWindow : public OWidget<O> {
public:
    template<typename ... A>
    OMainWindow(A && ... a) : OWidget<O>(a...) {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, OWidget<O>::proxy(), __PRETTY_FUNCTION__);
    }
    virtual ~OMainWindow() {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, OWidget<O>::proxy(), __PRETTY_FUNCTION__);
	QWidget *w = O::centralWidget();
	fprintf(stderr, "%p <0x%lx>->%s(): w = %p\n", this, OWidget<O>::proxy(), __PRETTY_FUNCTION__, w);
	if (w != nullptr) {
	    OClass *o = dynamic_cast<OClass *>(w);
	    assert(o != nullptr);
	    o->decr();
	}
    }
    virtual OWidget<QWidget> * centralWidget() {
	QWidget *o = O::centralWidget();
	OWidget<QWidget> *w = dynamic_cast<OWidget<QWidget> *>(o);
	assert(w != nullptr);
	return w;
    }
    template<class T>
    void setCentralWidget(OWidget<T> *w) {
	w->incr();
	O::setCentralWidget(w);
    }
private:
};

#endif // #ifndef MRVN_QT5_OMAINWINDOW_H
