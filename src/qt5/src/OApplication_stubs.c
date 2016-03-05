#include <QApplication>

#include "OApplication.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <features.h>
#include <stdlib.h>
#include <cassert>

#include "Proxy.h"

extern "C" value caml_mrvn_QT5_OApplication_exec() {
  CAMLparam0();
  fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
  CAMLreturn(Val_int(QApplication::exec()));
}

extern "C" value caml_mrvn_QT5_OApplication_make(value ml_args) {
  CAMLparam1(ml_args);
  fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
  OApplication<QApplication> *app = new OApplication<QApplication>(ml_args);
  fprintf(stderr, "%s() = %p\n", __PRETTY_FUNCTION__, app);
  CAMLreturn(Proxy<OApplication<QApplication> >::make(app));
}
