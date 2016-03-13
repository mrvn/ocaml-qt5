#include <QObject>

#include <caml/memory.h>

#include "Signal.h"
#include "Connection.h"
#include "OObject.h"
/*
char caml_mrvn_QT5_Signal_identifier[] = "mrvn.caml.QT5.Signal";

static void finalize(value v) {
  SignalBase *signal = (SignalBase*)Data_custom_val(v);
    signal->~SignalBase();
  }

struct custom_operations caml_mrvn_QT5_Signal_custom_ops = {
    caml_mrvn_QT5_Signal_identifier,
    finalize,
    custom_compare_default,
    custom_hash_default,
    custom_serialize_default,
    custom_deserialize_default,
    custom_compare_ext_default,
  };
*/

extern "C"
value caml_mrvn_QT5_Signal_connect(OObject *obj, SignalBase * signal, value ml_fn) {
    CAMLparam1(ml_fn);
    fprintf(stderr, "%s(obj = %p, signal = %p, ml_fn = 0x%lx)\n",
	    __PRETTY_FUNCTION__, obj, signal, ml_fn);
    QObject * qObj = dynamic_cast<QObject *>(obj);
    assert(qObj != nullptr);
    fprintf(stderr, "%s: qObj = %p\n", __PRETTY_FUNCTION__, qObj);
    QMetaObject::Connection con(signal->connect(qObj, ml_fn));
    fprintf(stderr, "%s: got con\n", __PRETTY_FUNCTION__);
    CAMLreturn(Connection::make(con));
}

value call2(value closure, bool arg) {
    CAMLparam1(closure);
    CAMLlocal1(res);
    res = caml_callback_exn(closure, Val_bool(arg));
    if (Is_exception_result(res)) {
        res = Extract_exception(res);
	fprintf(stderr, "%s: callback got exception 0x%ld\n", __PRETTY_FUNCTION__, res);
    }
    CAMLreturn(Val_unit);
}

