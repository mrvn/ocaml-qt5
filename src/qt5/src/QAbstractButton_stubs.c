#include <QObject>
#include <QAbstractButton>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <stdlib.h>
/*
#include <caml/alloc.h>
#include <features.h>
#include <cassert>
*/

#include "Proxy_stubs.h"

__BEGIN_DECLS

void caml_mrvn_QT5_QAbstractButton_connect(value ml_button) {
  CAMLparam1(ml_button);
  fprintf(stderr, "QAbstractButton::connect()\n");
  Proxy<QAbstractButton> *proxy = (Proxy<QAbstractButton> *)Data_custom_val(ml_button);
  QAbstractButton *button = proxy->obj();
  QObject::connect(button, &QAbstractButton::clicked,
		   [button](bool clicked) {
		       fprintf(stderr, "%p clicked\n", button);
		   });
  CAMLreturn0;
}

__END_DECLS
