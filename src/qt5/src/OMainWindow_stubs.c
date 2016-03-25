#include <QMainWindow>

#include "OMainWindow.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OMainWindow::OMainWindow() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

OMainWindow::~OMainWindow() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

void OMainWindow::removeCentralWidget() {
    QMainWindow *win = dynamic_cast<QMainWindow *>(this);
    assert((win != nullptr) && "OMainWindow not mixed with QMainWindow");
    if (win->centralWidget() != nullptr) { // protect buggy win->takeCentralWidget()
	QWidget *w = win->takeCentralWidget();
	if (w != nullptr) {
	    DEBUG("  has central widget\n");
	    // has a central widget
	    OWidget *o = dynamic_cast<OWidget *>(w);
	    if (o != nullptr) {
		// it's an ocaml widget, lower ref count
		DEBUG("  decrementing\n");
		o->decr();
	    } else {
		DEBUG("  pure QT5 widget, delete\n");
		// pure QT5 widget, delete
		delete w;
	    }
	}
    }
}

void OMainWindow::preDestructor() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
    // remove central widget from main window
    removeCentralWidget();
    OWidget::preDestructor();
}

void OMainWindow::setCentralWidget(OWidget *w) {
    DEBUG("%p->%s(%p)\n", this, __PRETTY_FUNCTION__, w);
    // remove old central widget
    removeCentralWidget();
    // add new central widget
    w->incr();
    QMainWindow *win = dynamic_cast<QMainWindow *>(this);
    assert((win != nullptr) && "OMainWindow not mixed with QMainWindow");
    QWidget *widget = dynamic_cast<QWidget *>(w);
    assert((widget != nullptr) && "OWidget not mixed with QWidget");
    win->setCentralWidget(widget);
}

extern "C" value caml_mrvn_QT5_OMainWindow_make(void) {
    DEBUG("%s()\n", __PRETTY_FUNCTION__);
    OQMainWindow *win = new OQMainWindow();
    assert((win != nullptr) && "OMainWindow not mixed with QMainWindow");
    return value(static_cast<OClass *>(win));
}

/*
extern "C" value caml_mrvn_QT5_OMainWindow_centralWidget(value ml_win) {
  CAMLparam1(ml_win);
  DEBUG("%s()\n", __PRETTY_FUNCTION__);
  Proxy<OMainWindow<QMainWindow> > *proxy = (Proxy<OMainWindow<QMainWindow> > *)Data_custom_val(ml_win);
  OWidget<QWidget> *w = proxy->call<OWidget<QWidget> *>(&OMainWindow<QMainWindow>::centralWidget);
  assert(w != nullptr);
  CAMLreturn(Proxy<OWidget<QWidget> >::make(w, 1));
}

*/

extern "C" value caml_mrvn_QT5_OMainWindow_setCentralWidget(OClass *obj, OClass *w) {
    CAMLparam0();
    DEBUG("%s(obj = %p, widget = %p)\n", __PRETTY_FUNCTION__, obj, w);
    OMainWindow *win = dynamic_cast<OMainWindow *>(obj);
    assert((win != nullptr) && "obj is not a OMainWindow");
    OWidget *widget = dynamic_cast<OWidget *>(w);
    assert((w != nullptr) && "w is not a OWidget");
    win->setCentralWidget(widget);
    CAMLreturn(Val_unit);
}
