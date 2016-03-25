#include <QObject>

#include "Connection.h"

#include <caml/custom.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>

#include "debug.h"

char caml_mrvn_QT5_Connection_identifier[] = "mrvn.caml.QT5.Connection";

Connection::Connection(const QMetaObject::Connection &con)
  : QMetaObject::Connection(con) {
  DEBUG("%p->%s()\n", this, __PRETTY_FUNCTION__);
}

Connection::~Connection() {
  DEBUG("%p->%s()\n", this, __PRETTY_FUNCTION__);
}

void Connection::disconnect() {
  DEBUG("%p->%s()\n", this, __PRETTY_FUNCTION__);
  QObject::disconnect(*this);
}

static void connection_finalize(value v) {
  Connection *con = (Connection *)Data_custom_val(v);
  DEBUG("%s(): Connection @ %p\n", __PRETTY_FUNCTION__, con);
  con->~Connection();
}

struct custom_operations caml_mrvn_QT5_Connection_custom_ops = {
  caml_mrvn_QT5_Connection_identifier,
  connection_finalize,
  custom_compare_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default,
};

value Connection::make(const QMetaObject::Connection &con) {
    CAMLparam0();
    CAMLlocal1(res);
    DEBUG("%s()\n", __PRETTY_FUNCTION__);
    res = caml_alloc_custom(&caml_mrvn_QT5_Connection_custom_ops, sizeof(Connection), 1, sizeof(Connection));
    new(Data_custom_val(res))Connection(con);
    CAMLreturn(res);
}

/*
external disconnect : 'a t -> unit
  = "caml_mrvn_QT5_Connection_disconnect"
*/
extern "C"
value caml_mrvn_QT5_Connection_disconnect(value ml_con) {
  CAMLparam1(ml_con);
  Connection *con = (Connection *)Data_custom_val(ml_con);
  con->disconnect();
  CAMLreturn(Val_unit);
}

