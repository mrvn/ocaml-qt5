#include <QPushButton>
#include <QString>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <features.h>
#include <stdlib.h>
#include <cassert>

#include "Proxy_stubs.h"

__BEGIN_DECLS

/*
value caml_mrvn_QT5_QPushButton_exec() {
  CAMLparam0();
  fprintf(stderr, "QPushButton::exec()\n");
  CAMLreturn(Val_int(QPushButton::exec()));
}
*/

value caml_mrvn_QT5_QPushButton_create(value ml_text) {
  CAMLparam1(ml_text);
  QString text(String_val(ml_text));
  QPushButton *button = new QPushButton(text);
  assert(button != NULL);
  fprintf(stderr, "QPushButton::QPushButton() @ %p\n", button);
  CAMLreturn(Proxy<QPushButton>::create(button));
}

__END_DECLS
