#include <QApplication>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <features.h>

__BEGIN_DECLS

value qApplication_constructor() {
  CAMLparam0();
  CAMLlocal1(app);
  static int argc = 1;
  static char *arg1 = "app.native";
  static char *arg2 = NULL;
  static char * argv[] = {arg1, arg2};
  fprintf(stderr, "QApplication::QApplication()\n");
  app = (value)new QApplication(argc, argv);
  fprintf(stderr, "QApplication::QApplication() @ %p\n", (QApplication*)app);
  CAMLreturn(app);
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
