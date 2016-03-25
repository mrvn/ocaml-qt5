#include <QPushButton>

#include "OPushButton.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <cassert>

OPushButton::OPushButton() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

OPushButton::~OPushButton() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

extern "C" value caml_mrvn_QT5_OPushButton_make(value ml_text) {
    CAMLparam1(ml_text);
    DEBUG("%s(\"%s\")\n", __PRETTY_FUNCTION__, String_val(ml_text));
    QString text(String_val(ml_text));
    OQPushButton *obj = new OQPushButton(text);
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}
