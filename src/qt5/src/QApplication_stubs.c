#include <QApplication>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <features.h>
#include <stdlib.h>
#include <cassert>

__BEGIN_DECLS

value qApplication_constructor(value ml_args) {
  CAMLparam1(ml_args);
  CAMLlocal1(res);
  int *argc_p = new int;
  assert(argc_p != nullptr);
  *argc_p = caml_array_length(ml_args);
  char **argv = new char*[*argc_p];
  assert(argv != nullptr);
  for (int i = 0; i < *argc_p; ++i) {
    argv[i] = strdup(String_val(Field(ml_args, i)));
  }
  QApplication *app = new QApplication(*argc_p, argv);
  assert(app != NULL);
  res = caml_alloc(3, 0); // allocate record for 3 return values
  Field(res, 0) = (value)app;
  Field(res, 1) = (value)argc_p;
  Field(res, 2) = (value)argv;
  fprintf(stderr, "QApplication::QApplication() @ %p\n", app);
  CAMLreturn(res);
}

value qApplication_exec(value ml_app) {
  CAMLparam1(ml_app);
  QApplication *app = (QApplication *)ml_app;
  fprintf(stderr, "QApplication::exec() @ %p\n", app);
  int res = app->exec();
  CAMLreturn(Val_int(res));
}

void qApplication_destructor(value ml_r) {
  CAMLparam1(ml_r);
  QApplication *app = (QApplication *)Field(ml_r, 0);
  int *argc_p = (int *)Field(ml_r, 1);
  char **argv = (char **)Field(ml_r, 2);
  fprintf(stderr, "QApplication::~QApplication() @ %p\n", app);
  for (int i = 0; i < *argc_p; ++i) {
    free(argv[i]);
  }
  delete app;
  delete argc_p;
  delete argv;
  CAMLreturn0;
}

__END_DECLS
