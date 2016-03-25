#include <QFrame>

#include "OFrame.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OFrame::OFrame() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

OFrame::~OFrame() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

extern "C" value caml_mrvn_QT5_OFrame_make(void) {
    DEBUG("%s\n", __PRETTY_FUNCTION__);
    OQFrame *obj = new OQFrame();
    assert(obj != nullptr);
    return value(static_cast<OClass *>(obj));
}

extern "C" value caml_mrvn_QT5_OFrame_setFrameStyle(OClass *obj, value ml_style) {
    CAMLparam1(ml_style);
    DEBUG("%s(%p, 0x%x)\n", __PRETTY_FUNCTION__, obj, Int_val(ml_style));
    QFrame *frame = dynamic_cast<QFrame *>(obj);
    assert((frame != nullptr) && "not mixed with QFrame");
    frame->setFrameStyle(Int_val(ml_style));
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OFrame_frameWidth(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QFrame *frame = dynamic_cast<QFrame *>(obj);
    assert((frame != nullptr) && "OFrame not mixed with QFrame");
    CAMLreturn(Val_int(frame->frameWidth()));
}
