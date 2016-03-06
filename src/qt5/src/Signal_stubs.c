#include <QObject>

#include <caml/memory.h>

#include "Signal.h"
#include "Proxy.h"
#include "Connection.h"
#include "OObject.h"

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

/*
external connect :
  'a Proxy.t -> ('a, 'b) t -> 'b -> 'b Connection.t
    = "caml_mrvn_QT5_Signal_connect"
*/
extern "C"
value caml_mrvn_QT5_Signal_connect(value ml_proxy, value ml_signal, value ml_fn) {
  CAMLparam3(ml_proxy, ml_signal, ml_fn);
  fprintf(stderr, "%s(ml_proxy = 0x%lx, ml_signal = 0x%lx, ml_fn = 0x%lx)\n", __PRETTY_FUNCTION__, ml_proxy, ml_signal, ml_fn);
  Proxy<OObject<QObject> > *proxy = (Proxy<OObject<QObject> > *)Data_custom_val(ml_proxy);
  fprintf(stderr, "%s: proxy = %p\n", __PRETTY_FUNCTION__, proxy);
  OObject<QObject> *obj = proxy->obj();
  fprintf(stderr, "%s: obj = %p\n", __PRETTY_FUNCTION__, obj);
  SignalBase *signal = (SignalBase *)ml_signal;
  fprintf(stderr, "%s: signal = %p\n", __PRETTY_FUNCTION__, signal);
  QMetaObject::Connection con(signal->connect(obj, ml_fn));
  fprintf(stderr, "%s: got con\n", __PRETTY_FUNCTION__);
  CAMLreturn(Connection::make(con));
}

void call2(value closure, bool arg) {
    CAMLparam1(closure);
    CAMLlocal1(res);
    res = caml_callback_exn(closure, Val_int(arg));
    if(Is_exception_result(res)) {
        res = Extract_exception(res);
	fprintf(stderr, "callback got exception 0x%ld\n", res);
    }
    CAMLreturn0;
}

