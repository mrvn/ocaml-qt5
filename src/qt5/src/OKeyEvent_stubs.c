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
