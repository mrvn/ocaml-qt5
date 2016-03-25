#include <QEvent>

#include "OEvent.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "debug.h"

OEvent::OEvent(QEvent *event) : OClass(1), event_(event) {
    DEBUG("%p->%s(%p)\n", this, __PRETTY_FUNCTION__, event);
}

OEvent::~OEvent() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
    assert((event_ == nullptr) && "event not removed");
}

void OEvent::removeEvent() {
    assert((event_ != nullptr) && "event removed twice");
    event_ = nullptr;
    decr();
}

QEvent * OEvent::event() const {
    DEBUG("%s: %p\n", __PRETTY_FUNCTION__, event_);
    return event_;
}
