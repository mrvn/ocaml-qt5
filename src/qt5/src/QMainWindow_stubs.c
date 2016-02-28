#include <QWidget>
#include <QMainWindow>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <features.h>
#include <stdio.h>

#include "Proxy_stubs.h"

__BEGIN_DECLS

value caml_mrvn_QT5_QMainWindow_create() {
  CAMLparam0();
  QMainWindow *win = new QMainWindow();
  fprintf(stderr, "QMainWindow::QMainWindow() @ %p\n", win);
  CAMLreturn(Proxy<QMainWindow>::create(win));
}

value caml_mrvn_QT5_QMainWindow_centralWidget(value ml_win) {
  CAMLparam1(ml_win);
  fprintf(stderr, "QMainWindow::centralWidget()\n");
  Proxy<QMainWindow> *proxy = (Proxy<QMainWindow> *)Data_custom_val(ml_win);
  QWidget *w = proxy->call<QWidget *>(&QMainWindow::centralWidget);
  assert(w != nullptr);
  CAMLreturn(Proxy<QWidget>::create(w, true));
}

void caml_mrvn_QT5_QMainWindow_setCentralWidget(value ml_win, value ml_widget) {
  CAMLparam2(ml_win, ml_widget);
  fprintf(stderr, "QMainWindow::setCentralWidget()\n");
  Proxy<QMainWindow> *proxy_win = (Proxy<QMainWindow> *)Data_custom_val(ml_win);
  Proxy<QWidget> *proxy_widget = (Proxy<QWidget> *)Data_custom_val(ml_widget);
  QWidget *w = proxy_widget->obj();
  assert(w != nullptr);
  proxy_win->call(&QMainWindow::setCentralWidget, w);
  CAMLreturn0;
}

void caml_mrvn_QT5_QMainWindow_show(value ml_proxy) {
  CAMLparam1(ml_proxy);
  fprintf(stderr, "%s(%lu)\n", __PRETTY_FUNCTION__, ml_proxy);
  Proxy<QMainWindow> *proxy = (Proxy<QMainWindow> *)Data_custom_val(ml_proxy);
  proxy->call<void>(&QMainWindow::show);
  CAMLreturn0;
}

__END_DECLS
