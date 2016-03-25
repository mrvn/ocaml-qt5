#include <QPainter>

#include "OPainter.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "OPaintDevice.h"

OPainter::OPainter() : device_(nullptr) {
    DEBUG("%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OPainter::~OPainter() {
    DEBUG("%p [0x%lx]->%s: device = %p\n", this, maybe_obj(), __PRETTY_FUNCTION__, device_);
    assert((device_ == nullptr) && "forgot to cal end()");
}

bool OPainter::begin(OPaintDevice *device) {
    DEBUG("%p [0x%lx]->%s(%p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, device);
    assert((device_ == nullptr) && "already have a device");
    device_ = device;
    device_->registerPainter(this);
    QPainter *painter = dynamic_cast<QPainter *>(this);
    assert((painter != nullptr) && "OPainter not mixed with QPainter");
    QPaintDevice *dev = dynamic_cast<QPaintDevice *>(device);
    assert((dev != nullptr) && "OPaintDevice not mixed with QPaintDevice");
    return painter->begin(dev);
}


void OPainter::end() {
    DEBUG("%p [0x%lx]->%s: device = %p\n", this, maybe_obj(), __PRETTY_FUNCTION__, device_);
    assert((device_ != nullptr) && "don't have a device");
    QPainter *painter = dynamic_cast<QPainter *>(this);
    assert((painter != nullptr) && "OPainter not mixed with QPainter");
    painter->end();
    device_->unregisterPainter(this);
    device_ = nullptr;
}

extern "C" value caml_mrvn_QT5_OPainter_make() {
    CAMLparam0();
    DEBUG("%s()\n", __PRETTY_FUNCTION__);
    OQPainter *obj = new OQPainter();
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}

extern "C" value caml_mrvn_QT5_OPainter_drawText(OClass *obj, OClass *rect, value ml_align, value ml_text) {
    CAMLparam2(ml_align, ml_text);
    DEBUG("%s(%p, %p, %d, '%s')\n", __PRETTY_FUNCTION__, obj, rect, Int_val(ml_align), String_val(ml_text));
    QPainter *painter = dynamic_cast<QPainter *>(obj);
    assert((painter != nullptr) && "OPainter not mixed with QPainter");
    QRect *r = dynamic_cast<QRect *>(rect);
    assert((r != nullptr) && "ORect not mixed with QRect");
    painter->drawText(*r, (Qt::AlignmentFlag)Int_val(ml_align), String_val(ml_text));
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OPainter_fillRect(OClass *obj, OClass *rect, OClass *color) {
    CAMLparam0();
    DEBUG("%s(%p, %p, %p)\n", __PRETTY_FUNCTION__, obj, rect, color);
    QPainter *painter = dynamic_cast<QPainter *>(obj);
    assert((painter != nullptr) && "OPainter not mixed with QPainter");
    QRect *r = dynamic_cast<QRect *>(rect);
    assert((r != nullptr) && "ORect not mixed with QRect");
    QColor *c = dynamic_cast<QColor *>(color);
    assert((c != nullptr) && "OColor not mixed with QColor");
    painter->fillRect(*r, *c);
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OPainter_setPenColor(OClass *obj, OClass *color) {
    CAMLparam0();
    DEBUG("%s(%p, %p)\n", __PRETTY_FUNCTION__, obj, color);
    QPainter *painter = dynamic_cast<QPainter *>(obj);
    assert((painter != nullptr) && "OPainter not mixed with QPainter");
    QColor *c = dynamic_cast<QColor *>(color);
    painter->setPen(*c);
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OPainter_drawLine(OClass *obj, value ml_x1, value ml_y1, value ml_x2, value ml_y2) {
    CAMLparam4(ml_x1, ml_y1, ml_x2, ml_y2);
    DEBUG("%s(%p, %d, %d, %d, %d)\n", __PRETTY_FUNCTION__, obj, Int_val(ml_x1), Int_val(ml_y1), Int_val(ml_x2), Int_val(ml_y2));
    QPainter *painter = dynamic_cast<QPainter *>(obj);
    assert((painter != nullptr) && "OPainter not mixed with QPainter");
    painter->drawLine(Int_val(ml_x1), Int_val(ml_y1), Int_val(ml_x2), Int_val(ml_y2));
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OPainter_begin(OClass *obj, OClass *device) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    OPainter *painter = dynamic_cast<OPainter *>(obj);
    assert((painter != nullptr) && "not an OPainter");
    OPaintDevice *dev = dynamic_cast<OPaintDevice *>(device);
    assert((dev != nullptr) && "not an OPaintDevice");
    CAMLreturn(Val_bool(painter->begin(dev)));
}

extern "C" value caml_mrvn_QT5_OPainter_end(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    OPainter *painter = dynamic_cast<OPainter *>(obj);
    assert((painter != nullptr) && "not an OPainter");
    painter->end();
    CAMLreturn(Val_unit);
}
