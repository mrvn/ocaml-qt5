#include <QMainWindow>

#include "OMainWindow.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OMainWindow::OMainWindow() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OMainWindow::~OMainWindow() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

void OMainWindow::removeCentralWidget() {
    QMainWindow *win = dynamic_cast<QMainWindow *>(this);
    assert((win != nullptr) && "OMainWindow not mixed with QMainWindow");
    QWidget *w = win->takeCentralWidget();
    if (w != nullptr) {
	fprintf(stderr, "  has central widget\n");
	// has a central widget
	OWidget *o = dynamic_cast<OWidget *>(w);
	if (o != nullptr) {
	    // it's an ocaml widget, lower ref count
	    fprintf(stderr, "  decrementing\n");
	    o->decr();
	} else {
	    fprintf(stderr, "  pure QT5 widget, delete\n");
	    // pure QT5 widget, delete
	    delete w;
	}
    }
}

void OMainWindow::preDestructor() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
    // remove central widget from main window
    removeCentralWidget();
    OWidget::preDestructor();
}

void OMainWindow::setCentralWidget(OWidget *w) {
    fprintf(stderr, "%p->%s(%p)\n", this, __PRETTY_FUNCTION__, w);
    w->incr();
    QMainWindow *win = dynamic_cast<QMainWindow *>(this);
    assert((win != nullptr) && "OMainWindow not mixed with QMainWindow");
    QWidget *widget = dynamic_cast<QWidget *>(w);
    assert((widget != nullptr) && "OWidget not mixed with QWidget");
    win->setCentralWidget(widget);
}

class OQMainWindow : public OMainWindow, public QMainWindow {
public:
    OQMainWindow() : OMainWindow(), QMainWindow() {
	fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
    }
    virtual ~OQMainWindow() {
	fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
	preDestructor();
    }
};

extern "C" value caml_mrvn_QT5_OMainWindow_make(void) {
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQMainWindow *win = new OQMainWindow();
    assert((win != nullptr) && "OMainWindow not mixed with QMainWindow");
    return value(static_cast<OClass *>(win));
}

/*
extern "C" value caml_mrvn_QT5_OMainWindow_centralWidget(value ml_win) {
  CAMLparam1(ml_win);
  fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
  Proxy<OMainWindow<QMainWindow> > *proxy = (Proxy<OMainWindow<QMainWindow> > *)Data_custom_val(ml_win);
  OWidget<QWidget> *w = proxy->call<OWidget<QWidget> *>(&OMainWindow<QMainWindow>::centralWidget);
  assert(w != nullptr);
  CAMLreturn(Proxy<OWidget<QWidget> >::make(w, 1));
}

*/

extern "C" void caml_mrvn_QT5_OMainWindow_show(OClass *obj) {
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QMainWindow *win = dynamic_cast<QMainWindow *>(obj);
    assert(win != nullptr);
    win->show();
}

extern "C" void caml_mrvn_QT5_OMainWindow_setCentralWidget(OClass *obj, OClass *w) {
    fprintf(stderr, "%s(obj = %p, widget = %p)\n", __PRETTY_FUNCTION__, obj, w);
    OMainWindow *win = dynamic_cast<OMainWindow *>(obj);
    assert((win != nullptr) && "obj is not a OMainWindow");
    OWidget *widget = dynamic_cast<OWidget *>(w);
    assert((w != nullptr) && "w is not a OWidget");
    win->setCentralWidget(widget);
}
