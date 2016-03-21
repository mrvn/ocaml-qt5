#include <QSize>

#include "OSize.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OSize::OSize() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OSize::~OSize() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OQSize::OQSize(int width, int height) : OSize(), QSize(width, height) {
    fprintf(stderr, "%p [0x%lx]->%s(%d, %d)\n", this, OSize::maybe_obj(), __PRETTY_FUNCTION__, width, height);
}

OQSize::~OQSize() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, OSize::maybe_obj(), __PRETTY_FUNCTION__);
}

extern "C" value caml_mrvn_QT5_OSize_width(OClass *obj) {
    CAMLparam0();
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QSize *size = dynamic_cast<QSize *>(obj);
    assert((size != nullptr) && "OSize not mixed with QSize");
    CAMLreturn(Val_int(size->width()));
}

extern "C" value caml_mrvn_QT5_OSize_height(OClass *obj) {
    CAMLparam0();
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QSize *size = dynamic_cast<QSize *>(obj);
    assert((size != nullptr) && "OSize not mixed with QSize");
    CAMLreturn(Val_int(size->height()));
}

extern "C" value caml_mrvn_QT5_OSize_alloc(int width, int height) {
    CAMLparam0();
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQSize *obj = new OQSize(width, height);
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}

extern "C" value caml_mrvn_QT5_OSize_make(value ml_width, value ml_height) {
    return caml_mrvn_QT5_OSize_alloc(Int_val(ml_width), Int_val(ml_height));
}
