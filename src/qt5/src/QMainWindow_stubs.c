#include <QMainWindow>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <features.h>
#include <stdio.h>

__BEGIN_DECLS

value qMainWindow_constructor() {
  CAMLparam0();
  CAMLlocal1(win);
  win = (value)new QMainWindow();
  fprintf(stderr, "QMainWindow::QMainWindow() @ %p\n", (QMainWindow*)win);
  CAMLreturn(win);
}

void qMainWindow_show(value ml_win) {
  CAMLparam1(ml_win);
  QMainWindow *win = (QMainWindow *)ml_win;
  fprintf(stderr, "QMainWindow::show() @ %p\n", win);
  win->show();
  CAMLreturn0;
}

void qMainWindow_destructor(value ml_win) {
  CAMLparam1(ml_win);
  QMainWindow *win = (QMainWindow *)ml_win;
  fprintf(stderr, "QMainWindow::~QMainWindow() @ %p\n", win);
  delete win;
  CAMLreturn0;
}

__END_DECLS
