#include "Proxy_stubs.h"

char caml_mrvn_QT5_Proxy_identifier[] = "mrvn.caml.QT5.Proxy";

static void finalize(value v) {
    Proxy<QObject> *proxy = (Proxy<QObject> *)Data_custom_val(v);
    proxy->~Proxy();
  }


struct custom_operations caml_mrvn_QT5_Proxy_custom_ops = {
    caml_mrvn_QT5_Proxy_identifier,
    finalize,
    custom_compare_default,
    custom_hash_default,
    custom_serialize_default,
    custom_deserialize_default,
    custom_compare_ext_default,
  };

