#include <QApplication>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <features.h>
#include <stdlib.h>
#include <cassert>

#include "Proxy_stubs.h"

__BEGIN_DECLS

value caml_mrvn_QT5_QApplication_exec() {
  CAMLparam0();
  fprintf(stderr, "QApplication::exec()\n");
  CAMLreturn(Val_int(QApplication::exec()));
}

value caml_mrvn_QT5_QApplication_create(value ml_argv) {
  CAMLparam1(ml_argv);
  int *argc_p = (int *)Field(ml_argv, 0);
  char **argv = (char **)Field(ml_argv, 1);
  QApplication *app = new QApplication(*argc_p, argv);
  assert(app != NULL);
  fprintf(stderr, "QApplication::QApplication() @ %p\n", app);
  CAMLreturn(Proxy<QApplication>::create(app));
}

__END_DECLS
