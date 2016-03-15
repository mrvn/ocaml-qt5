#include <QPaintEvent>

#include "OPaintEvent.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OPaintEvent::OPaintEvent(QPaintEvent *event) : OEvent(event) {
    fprintf(stderr, "%p->%s(%p)\n", this, __PRETTY_FUNCTION__, event);
}

OPaintEvent::~OPaintEvent() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

QPaintEvent * OPaintEvent::event() const {
    QPaintEvent *e = dynamic_cast<QPaintEvent *>(OEvent::event());
    fprintf(stderr, "%s: %p\n", __PRETTY_FUNCTION__, e);
    return e;
}
