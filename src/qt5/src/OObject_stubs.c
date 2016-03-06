#include <QEvent>
#include <QAbstractButton>

#include "OObject.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <cassert>

#include "Proxy.h"
#include "EventHandler.h"

EventHandler<OObject<QAbstractButton> > OObject_QObject_handler_event(&OObject<QAbstractButton>::set_handler_event);

extern "C"
value caml_mrvn_QT5_OObject_QObject_handler_event(void) {
    CAMLparam0();
    fprintf(stderr, "%s() = %p\n", __PRETTY_FUNCTION__, (void*)&OObject_QObject_handler_event);
    CAMLreturn((value)&OObject_QObject_handler_event);
}

