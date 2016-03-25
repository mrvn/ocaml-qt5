#include <QTimerEvent>

#include "OTimerEvent.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "debug.h"

OTimerEvent::OTimerEvent(QTimerEvent *event) : OEvent(event) {
    DEBUG("%p->%s(%p)\n", this, __PRETTY_FUNCTION__, event);
}

OTimerEvent::~OTimerEvent() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

QTimerEvent * OTimerEvent::event() const {
    QTimerEvent *e = dynamic_cast<QTimerEvent *>(OEvent::event());
    DEBUG("%s: %p\n", __PRETTY_FUNCTION__, e);
    return e;
}

extern "C" value caml_mrvn_QT5_OTimerEvent_timerId(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    OTimerEvent *event = dynamic_cast<OTimerEvent *>(obj);
    assert((event != nullptr) && "not an OTimerEvent");
    QTimerEvent *e = event->event();
    assert((e != nullptr) && "lost the QTimerEvent");
    int id = e->timerId();
    DEBUG("%s(%p): id = %d\n", __PRETTY_FUNCTION__, obj, id);
    CAMLreturn(Val_int(id));
}
