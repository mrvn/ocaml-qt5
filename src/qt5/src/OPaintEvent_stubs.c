#include <QPaintEvent>

#include "OPaintEvent.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "debug.h"

OPaintEvent::OPaintEvent(QPaintEvent *event) : OEvent(event) {
    DEBUG("%p->%s(%p)\n", this, __PRETTY_FUNCTION__, event);
}

OPaintEvent::~OPaintEvent() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

QPaintEvent * OPaintEvent::event() const {
    QPaintEvent *e = dynamic_cast<QPaintEvent *>(OEvent::event());
    DEBUG("%s: %p\n", __PRETTY_FUNCTION__, e);
    return e;
}
