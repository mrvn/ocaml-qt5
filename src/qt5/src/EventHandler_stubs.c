#include "EventHandler.h"

#include <QObject>
#include <caml/memory.h>

#include "Proxy.h"
#include "OEvent.h"
#include "OObject.h"

char caml_mrvn_QT5_EventHandler_identifier[] = "mrvn.caml.QT5.EventHandler";

static void finalize(value v) {
    EventHandlerBase *handler = (EventHandlerBase*)Data_custom_val(v);
    handler->~EventHandlerBase();
}

struct custom_operations caml_mrvn_QT5_EventHandler_custom_ops = {
    caml_mrvn_QT5_EventHandler_identifier,
    finalize,
    custom_compare_default,
    custom_hash_default,
    custom_serialize_default,
    custom_deserialize_default,
    custom_compare_ext_default,
  };

/*
external set :
  'a Proxy.t -> ('a, 'b) t -> 'b -> unit
    = "caml_mrvn_QT5_EventHandler_set"
*/
extern "C"
void caml_mrvn_QT5_EventHandler_set(value ml_proxy, value ml_event_handler, value closure) {
  CAMLparam3(ml_proxy, ml_event_handler, closure);
  fprintf(stderr, "%s(ml_proxy = 0x%lx, ml_event_handler = 0x%lx, closure = 0x%lx)\n", __PRETTY_FUNCTION__, ml_proxy, ml_event_handler, closure);
  EventHandlerBase *handler = (EventHandlerBase *)ml_event_handler;
  fprintf(stderr, "%s: handler = %p\n", __PRETTY_FUNCTION__, handler);
  handler->set(ml_proxy, closure);
  CAMLreturn0;
}

bool call_bool_QEvent(value closure, QEvent *event) {
    CAMLparam1(closure);
    CAMLlocal2(proxy, res);
    fprintf(stderr, "%s: closure = 0x%lu, event = %p\n", __PRETTY_FUNCTION__, closure, event);
    OEvent oEvent(event);
    fprintf(stderr, "%s: oEvent @ %p\n", __PRETTY_FUNCTION__, &oEvent);
    proxy = Proxy<OEvent>::make(&oEvent);
    fprintf(stderr, "%s: proxy = 0x%lu\n", __PRETTY_FUNCTION__, proxy);
    res = caml_callback_exn(closure, proxy);
    fprintf(stderr, "%s: res = 0x%lu\n", __PRETTY_FUNCTION__, res);
    if(Is_exception_result(res)) {
        res = Extract_exception(res);
	fprintf(stderr, "%s: callback got exception 0x%ld\n", __PRETTY_FUNCTION__, res);
	CAMLreturn(false);
    }
    CAMLreturn(Bool_val(res));
}
