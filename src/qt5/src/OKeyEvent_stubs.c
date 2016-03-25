#include <QKeyEvent>

#include "OKeyEvent.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OKeyEvent::OKeyEvent(QKeyEvent *event) : OEvent(event) {
    fprintf(stderr, "%p->%s(%p)\n", this, __PRETTY_FUNCTION__, event);
}

OKeyEvent::~OKeyEvent() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

QKeyEvent * OKeyEvent::event() const {
    QKeyEvent *e = dynamic_cast<QKeyEvent *>(OEvent::event());
    fprintf(stderr, "%s: %p\n", __PRETTY_FUNCTION__, e);
    return e;
}

extern "C" value caml_mrvn_QT5_OKeyEvent_key(OClass *obj) {
    CAMLparam0();
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    OKeyEvent *keyEvent = dynamic_cast<OKeyEvent *>(obj);
    assert((keyEvent != nullptr) && "not an OKeyEvent");
    QKeyEvent *event = keyEvent->event();
    CAMLreturn(Val_int(event->key()));
}
