#include <QLabel>

#include "OLabel.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <cassert>

OLabel::OLabel() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OLabel::~OLabel() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

extern "C" value caml_mrvn_QT5_OLabel_make(value ml_text) {
    CAMLparam1(ml_text);
    fprintf(stderr, "%s(\"%s\")\n", __PRETTY_FUNCTION__, String_val(ml_text));
    QString text(String_val(ml_text));
    OQLabel *obj;
    if (text == QString("")) {
	obj = new OQLabel();
    } else {
	obj = new OQLabel(text);
    }
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}

extern "C" value caml_mrvn_QT5_OLabel_setAlignment(OClass *obj, value ml_align) {
    CAMLparam1(ml_align);
    fprintf(stderr, "%s(0x%x)\n", __PRETTY_FUNCTION__, Int_val(ml_align));
    QLabel *label = dynamic_cast<QLabel *>(obj);
    assert((label != nullptr) && "not mixed with QLabel");
    label->setAlignment((Qt::AlignmentFlag)Int_val(ml_align));
    CAMLreturn(Val_unit);
}
