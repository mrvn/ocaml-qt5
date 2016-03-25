#include <QRect>

#include "ORect.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "debug.h"

ORect::ORect() {
    DEBUG("%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

ORect::~ORect() {
    DEBUG("%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OQRect::OQRect(int x, int y, int w, int h) : ORect(), QRect(x, y, w, h) {
    DEBUG("%p [0x%lx]->%s(%d, %d, %d, %d)\n", this, ORect::maybe_obj(), __PRETTY_FUNCTION__, x, y, w, h);
}

OQRect::~OQRect() {
    DEBUG("%p [0x%lx]->%s\n", this, ORect::maybe_obj(), __PRETTY_FUNCTION__);
}

extern "C" value caml_mrvn_QT5_ORect_x(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QRect *rect = dynamic_cast<QRect *>(obj);
    assert((rect != nullptr) && "ORect not mixed with QRect");
    CAMLreturn(Val_int(rect->x()));
}

extern "C" value caml_mrvn_QT5_ORect_y(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QRect *rect = dynamic_cast<QRect *>(obj);
    assert((rect != nullptr) && "ORect not mixed with QRect");
    CAMLreturn(Val_int(rect->y()));
}

extern "C" value caml_mrvn_QT5_ORect_width(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QRect *rect = dynamic_cast<QRect *>(obj);
    assert((rect != nullptr) && "ORect not mixed with QRect");
    CAMLreturn(Val_int(rect->width()));
}

extern "C" value caml_mrvn_QT5_ORect_height(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QRect *rect = dynamic_cast<QRect *>(obj);
    assert((rect != nullptr) && "ORect not mixed with QRect");
    CAMLreturn(Val_int(rect->height()));
}

extern "C" value caml_mrvn_QT5_ORect_top(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QRect *rect = dynamic_cast<QRect *>(obj);
    assert((rect != nullptr) && "ORect not mixed with QRect");
    CAMLreturn(Val_int(rect->top()));
}

extern "C" value caml_mrvn_QT5_ORect_bottom(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QRect *rect = dynamic_cast<QRect *>(obj);
    assert((rect != nullptr) && "ORect not mixed with QRect");
    CAMLreturn(Val_int(rect->bottom()));
}

extern "C" value caml_mrvn_QT5_ORect_left(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QRect *rect = dynamic_cast<QRect *>(obj);
    assert((rect != nullptr) && "ORect not mixed with QRect");
    CAMLreturn(Val_int(rect->left()));
}

extern "C" value caml_mrvn_QT5_ORect_right(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QRect *rect = dynamic_cast<QRect *>(obj);
    assert((rect != nullptr) && "ORect not mixed with QRect");
    CAMLreturn(Val_int(rect->right()));
}

extern "C" value caml_mrvn_QT5_ORect_alloc(int x, int y, int w, int h) {
    CAMLparam0();
    DEBUG("%s(%d, %d, %d, %d)\n", __PRETTY_FUNCTION__, x, y, w, h);
    OQRect *obj = new OQRect(x, y, w, h);
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}

extern "C" value caml_mrvn_QT5_ORect_make(value ml_x, value ml_y, value ml_w, value ml_h) {
    DEBUG("%s(%d, %d, %d, %d)\n", __PRETTY_FUNCTION__, Int_val(ml_x), Int_val(ml_y), Int_val(ml_w), Int_val(ml_h));
    return caml_mrvn_QT5_ORect_alloc(Int_val(ml_x), Int_val(ml_y), Int_val(ml_w), Int_val(ml_h));
}
