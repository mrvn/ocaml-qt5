#include <QFrame>

#include "OFrame.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OFrame::OFrame() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OFrame::~OFrame() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

extern "C" value caml_mrvn_QT5_OFrame_make(void) {
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQFrame *obj = new OQFrame();
    assert(obj != nullptr);
    return value(static_cast<OClass *>(obj));
}

extern "C" value caml_mrvn_QT5_OFrame_setFrameStyle(OClass *obj, value ml_style) {
    CAMLparam1(ml_style);
    fprintf(stderr, "%s(0x%x)\n", __PRETTY_FUNCTION__, Int_val(ml_style));
    QFrame *frame = dynamic_cast<QFrame *>(obj);
    assert((frame != nullptr) && "not mixed with QFrame");
    frame->setFrameStyle(Int_val(ml_style));
    CAMLreturn(Val_unit);
}
