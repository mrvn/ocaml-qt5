#include <QEvent>

#include "OEvent.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OEvent::OEvent(QEvent *event) : OClass(1), event_(event) {
    fprintf(stderr, "%p->%s(%p)\n", this, __PRETTY_FUNCTION__, event);
}

OEvent::~OEvent() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
    assert((event_ == nullptr) && "event not removed");
}

void OEvent::removeEvent() {
    assert((event_ != nullptr) && "event removed twice");
    event_ = nullptr;
    decr();
}

QEvent * OEvent::event() const {
    fprintf(stderr, "%s: %p\n", __PRETTY_FUNCTION__, event_);
    return event_;
}
