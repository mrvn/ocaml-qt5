#include <QApplication>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <features.h>
#include <stdlib.h>
#include <cassert>

__BEGIN_DECLS

value qApplication_constructor(value ml_argv) {
  CAMLparam1(ml_argv);
  int *argc_p = (int *)Field(ml_argv, 0);
  char **argv = (char **)Field(ml_argv, 1);
  QApplication *app = new QApplication(*argc_p, argv);
  assert(app != NULL);
  fprintf(stderr, "QApplication::QApplication() @ %p\n", app);
  CAMLreturn((value)app);
}

value qApplication_exec(value ml_app) {
  CAMLparam1(ml_app);
  QApplication *app = (QApplication *)ml_app;
  fprintf(stderr, "QApplication::exec() @ %p\n", app);
  int res = app->exec();
  CAMLreturn(Val_int(res));
}

void qApplication_destructor(value ml_app) {
  CAMLparam1(ml_app);
  QApplication *app = (QApplication *)ml_app;
  fprintf(stderr, "QApplication::~QApplication() @ %p\n", app);
  delete app;
  CAMLreturn0;
}

__END_DECLS
