#include <QApplication>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <features.h>

__BEGIN_DECLS

QApplication * qApplication_constructor() {
  int argc = 0;
  char * argv[] = {NULL};
  return new QApplication(argc, argv);
}

int qApplication_exec(QApplication *app) {
  return app->exec();
}

void qApplication_destructor(QApplication *app) {
  delete app;
}

__END_DECLS
