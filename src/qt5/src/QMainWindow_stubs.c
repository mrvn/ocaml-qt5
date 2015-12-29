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

void caml_mrvn_QT5_QMainWindow_show(value ml_proxy) {
  CAMLparam1(ml_proxy);
  fprintf(stderr, "%s(%lu)\n", __PRETTY_FUNCTION__, ml_proxy);
  Proxy<QMainWindow> *proxy = (Proxy<QMainWindow> *)Data_custom_val(ml_proxy);
  proxy->call<void>(&QMainWindow::show);
  CAMLreturn0;
}

__END_DECLS
