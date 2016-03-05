#include <QMainWindow>

#include "OMainWindow.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <features.h>
#include <stdio.h>

#include "Proxy.h"

extern "C" value caml_mrvn_QT5_OMainWindow_make() {
  CAMLparam0();
  OMainWindow<QMainWindow> *win = new OMainWindow<QMainWindow>();
  fprintf(stderr, "%s() @ %p\n", __PRETTY_FUNCTION__, win);
  CAMLreturn(Proxy<OMainWindow<QMainWindow> >::make(win));
}

extern "C" value caml_mrvn_QT5_OMainWindow_centralWidget(value ml_win) {
  CAMLparam1(ml_win);
  fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
  Proxy<OMainWindow<QMainWindow> > *proxy = (Proxy<OMainWindow<QMainWindow> > *)Data_custom_val(ml_win);
  OWidget<QWidget> *w = proxy->call<OWidget<QWidget> *>(&OMainWindow<QMainWindow>::centralWidget);
  assert(w != nullptr);
  CAMLreturn(Proxy<OWidget<QWidget> >::make(w, 1));
}

extern "C" void caml_mrvn_QT5_OMainWindow_setCentralWidget(value ml_win, value ml_widget) {
  CAMLparam2(ml_win, ml_widget);
  fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
  Proxy<OMainWindow<QMainWindow> > *proxy_win = (Proxy<OMainWindow<QMainWindow> > *)Data_custom_val(ml_win);
  fprintf(stderr, "%s(): proxy_win = %p\n", __PRETTY_FUNCTION__, proxy_win);
  Proxy<OWidget<QWidget> > *proxy_widget = (Proxy<OWidget<QWidget> > *)Data_custom_val(ml_widget);
  fprintf(stderr, "%s(): proxy_widget = %p\n", __PRETTY_FUNCTION__, proxy_widget);
  OWidget<QWidget> *w = proxy_widget->obj();
  fprintf(stderr, "%s(): w = %p\n", __PRETTY_FUNCTION__, w);
  assert(w != nullptr);
  proxy_win->call(&OMainWindow<QMainWindow>::setCentralWidget, w);
  CAMLreturn0;
}

extern "C" void caml_mrvn_QT5_OMainWindow_show(value ml_proxy) {
  CAMLparam1(ml_proxy);
  fprintf(stderr, "%s(0x%lx)\n", __PRETTY_FUNCTION__, ml_proxy);
  Proxy<OMainWindow<QMainWindow> > *proxy = (Proxy<OMainWindow<QMainWindow> > *)Data_custom_val(ml_proxy);
  fprintf(stderr, "%s(): proxy = %p\n", __PRETTY_FUNCTION__, proxy);
  proxy->call<void>(&OMainWindow<QMainWindow>::show);
  CAMLreturn0;
}
