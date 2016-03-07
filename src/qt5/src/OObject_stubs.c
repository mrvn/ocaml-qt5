#include "OObject.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <cassert>

#include "Proxy.h"

extern "C"
value caml_mrvn_QT5_OObject_QObject_handler_event(value ml_proxy) {
    CAMLparam0();
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    Proxy<QObject> *proxy = (Proxy<QObject> *)Data_custom_val(ml_proxy);
    fprintf(stderr, "%s: proxy = %p\n", __PRETTY_FUNCTION__, proxy);
    value handler = proxy->call<QVariant>(&QObject::property, "caml_mrvn_QT5_OObject_QObject_handler_event").toLongLong();
    fprintf(stderr, "%s: handler = 0x%lx\n", __PRETTY_FUNCTION__, handler);
    CAMLreturn(handler);
}

