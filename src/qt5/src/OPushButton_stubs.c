#include <QPushButton>
#include <QString>

#include "OPushButton.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <features.h>
#include <stdlib.h>
#include <cassert>

#include "Proxy.h"

extern "C" value caml_mrvn_QT5_OPushButton_make(value ml_text) {
    CAMLparam1(ml_text);
    QString text(String_val(ml_text));
    OPushButton<QPushButton> *button = new OPushButton<QPushButton>(text);
    assert(button != NULL);
    fprintf(stderr, "OPushButton::OPushButton() @ %p [%p, %p]\n", button, dynamic_cast<QPushButton *>(button), dynamic_cast<OPushButton<QPushButton> *>(dynamic_cast<QPushButton *>(button)));
    CAMLreturn(Proxy<OPushButton<QPushButton> >::make(button));
}
