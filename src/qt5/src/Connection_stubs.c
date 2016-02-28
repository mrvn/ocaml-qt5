#include "Connection_stubs.h"
#include <QObject>
#include <caml/custom.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>

char caml_mrvn_QT5_Connection_identifier[] = "mrvn.caml.QT5.Connection";

static void finalize(value v) {
  QMetaObject::Connection *con = (QMetaObject::Connection *)Data_custom_val(v);
  con->~Connection();
}

struct custom_operations caml_mrvn_QT5_Connection_custom_ops = {
  caml_mrvn_QT5_Connection_identifier,
  finalize,
  custom_compare_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default,
};

value make(QMetaObject::Connection con, value ml_fn) {
  CAMLparam0();
  CAMLlocal2(ml_qtCon, res);
  fprintf(stderr, "Creating connection\n");
  ml_qtCon = caml_alloc_custom(&caml_mrvn_QT5_Connection_custom_ops, sizeof(QMetaObject::Connection), 1, 1000);
  new(Data_custom_val(ml_qtCon))QMetaObject::Connection(con);
  res = caml_alloc_tuple(2);
  Field(res, 0) = ml_qtCon;
  Field(res, 1) = ml_fn;
  CAMLreturn(res);
}

/*
external disconnect : 'a t -> unit
  = "caml_mrvn_QT5_Connection_disconnect"
*/
extern "C"
void caml_mrvn_QT5_Connection_disconnect(value ml_con) {
  CAMLparam1(ml_con);
  CAMLlocal1(ml_qtCon);
  ml_qtCon = Field(ml_con, 0);
  QMetaObject::Connection *con = (QMetaObject::Connection *)Data_custom_val(ml_qtCon);
  QObject::disconnect(*con);
  CAMLreturn0;
}


