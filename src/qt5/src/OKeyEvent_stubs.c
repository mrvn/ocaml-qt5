#include <QKeyEvent>

#include "OKeyEvent.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "debug.h"

OKeyEvent::OKeyEvent(QKeyEvent *event) : OEvent(event) {
    DEBUG("%p->%s(%p)\n", this, __PRETTY_FUNCTION__, event);
}

OKeyEvent::~OKeyEvent() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

QKeyEvent * OKeyEvent::event() const {
    QKeyEvent *e = dynamic_cast<QKeyEvent *>(OEvent::event());
    DEBUG("%s: %p\n", __PRETTY_FUNCTION__, e);
    return e;
}

extern "C" value caml_mrvn_QT5_OKeyEvent_key(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    OKeyEvent *keyEvent = dynamic_cast<OKeyEvent *>(obj);
    assert((keyEvent != nullptr) && "not an OKeyEvent");
    QKeyEvent *event = keyEvent->event();
    CAMLreturn(Val_int(event->key()));
}
