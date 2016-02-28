#include "Signal_stubs.h"
#include "Proxy_stubs.h"
#include "Connection_stubs.h"
#include <caml/memory.h>

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

class Q;

/*
external connect :
  'a Proxy.t -> ('a, 'b) t -> 'b -> 'b Connection.t
    = "caml_mrvn_QT5_Signal_connect"
*/
extern "C"
value caml_mrvn_QT5_Signal_connect(value ml_proxy, value ml_signal, value ml_fn) {
  CAMLparam3(ml_proxy, ml_signal, ml_fn);
  fprintf(stderr, "%s\n", __PRETTY_FUNCTION__);
  Proxy<Q> *proxy = (Proxy<Q> *)Data_custom_val(ml_proxy);
  fprintf(stderr, "%s: proxy = %p\n", __PRETTY_FUNCTION__, proxy);
  Q *obj = proxy->obj();
  fprintf(stderr, "%s: obj = %p\n", __PRETTY_FUNCTION__, obj);
  SignalBase *signal = (SignalBase *)ml_signal;
  fprintf(stderr, "%s: signal = %p\n", __PRETTY_FUNCTION__, signal);
  QMetaObject::Connection con(signal->connect(obj, ml_fn));
  fprintf(stderr, "%s: got con\n", __PRETTY_FUNCTION__);
  CAMLreturn(make(con, ml_fn));
}

