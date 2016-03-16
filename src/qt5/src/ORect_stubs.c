#include <QRect>

#include "ORect.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

ORect::ORect() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

ORect::~ORect() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OQRect::OQRect(int x, int y, int w, int h) : ORect(), QRect(x, y, w, h) {
    fprintf(stderr, "%p [0x%lx]->%s(%d, %d, %d, %d)\n", this, ORect::maybe_obj(), __PRETTY_FUNCTION__, x, y, w, h);
}

OQRect::~OQRect() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, ORect::maybe_obj(), __PRETTY_FUNCTION__);
}

extern "C" value caml_mrvn_QT5_ORect_make(value ml_x, value ml_y, value ml_w, value ml_h) {
    CAMLparam0();
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQRect *obj = new OQRect(Int_val(ml_x), Int_val(ml_y), Int_val(ml_w), Int_val(ml_h));
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}
