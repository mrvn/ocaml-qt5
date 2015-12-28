#include <QObject>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <features.h>
#include <stdio.h>

__BEGIN_DECLS

value qObject_constructor() {
  CAMLparam0();
  CAMLlocal1(obj);
  obj = (value)new QObject();
  fprintf(stderr, "QObject::QObject() @ %p\n", (QObject*)obj);
  CAMLreturn(obj);
}

void qObject_destructor(value ml_obj) {
  CAMLparam1(ml_obj);
  QObject *obj = (QObject *)ml_obj;
  fprintf(stderr, "QObject::~QObject() @ %p\n", obj);
  delete obj;
  CAMLreturn0;
}

__END_DECLS
