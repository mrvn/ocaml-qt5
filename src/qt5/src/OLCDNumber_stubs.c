#include <QLCDNumber>

#include "OLCDNumber.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OLCDNumber::OLCDNumber() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OLCDNumber::~OLCDNumber() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

extern "C" value caml_mrvn_QT5_OLCDNumber_make(value ml_numDigits) {
    CAMLparam1(ml_numDigits);
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQLCDNumber *obj = new OQLCDNumber(Int_val(ml_numDigits));
    assert(obj != nullptr);
    CAMLreturn((value)static_cast<OClass *>(obj));
}

extern "C" value caml_mrvn_QT5_OLCDNumber_setMode(OClass *obj, value ml_mode) {
    CAMLparam1(ml_mode);
    fprintf(stderr, "%s(0x%x)\n", __PRETTY_FUNCTION__, Int_val(ml_mode));
    QLCDNumber *LCDNumber = dynamic_cast<QLCDNumber *>(obj);
    assert((LCDNumber != nullptr) && "not mixed with QLCDNumber");
    LCDNumber->setMode((QLCDNumber::Mode)Int_val(ml_mode));
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OLCDNumber_setSegmentStyle(OClass *obj, value ml_style) {
    CAMLparam1(ml_style);
    fprintf(stderr, "%s(0x%x)\n", __PRETTY_FUNCTION__, Int_val(ml_style));
    QLCDNumber *LCDNumber = dynamic_cast<QLCDNumber *>(obj);
    assert((LCDNumber != nullptr) && "not mixed with QLCDNumber");
    LCDNumber->setSegmentStyle((QLCDNumber::SegmentStyle)Int_val(ml_style));
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OLCDNumber_display(OClass *obj, value ml_num) {
    CAMLparam1(ml_num);
    fprintf(stderr, "%s(0x%x)\n", __PRETTY_FUNCTION__, Int_val(ml_num));
    QLCDNumber *number = dynamic_cast<QLCDNumber *>(obj);
    assert((number != nullptr) && "not mixed with QLCDNumber");
    number->display(Int_val(ml_num));
    CAMLreturn(Val_unit);
}
