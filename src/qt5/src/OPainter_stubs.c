#include <QPainter>
#include <QtCore/QDebug>

#include "OPainter.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OPainter::OPainter(OPaintDevice *device) : device_(device) {
    fprintf(stderr, "%p [0x%lx]->%s(%p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, device_);
    device_->incr();
}

OPainter::~OPainter() {
    fprintf(stderr, "%p [0x%lx]->%s: device = %p\n", this, maybe_obj(), __PRETTY_FUNCTION__, device_);
    device_->decr();
}

extern "C" value caml_mrvn_QT5_OPainter_make(OClass *device) {
    CAMLparam0();
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OPaintDevice *dev = dynamic_cast<OPaintDevice *>(device);
    assert((dev != nullptr) && "not an OPaintDevice");
    /* make sure the dynamic_cast in OQPainter() doesn't fail */
    QPaintDevice *qdev = dynamic_cast<QPaintDevice *>(device);
    assert((qdev != nullptr) && "OPaintDevice not mixed with QPaintDevice");
    OQPainter *obj = new OQPainter(dev);
    qDebug() << "OQPainter()" << obj;
    qDebug() << "QPainter()" << dynamic_cast<QPainter*>(obj);
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}

extern "C" value caml_mrvn_QT5_OPainter_drawText(OClass *obj, OClass *rect, value ml_align, value ml_text) {
    CAMLparam2(ml_align, ml_text);
    fprintf(stderr, "%s(%p, %p, %d, '%s')\n", __PRETTY_FUNCTION__, obj, rect, Int_val(ml_align), String_val(ml_text));
    QPainter *painter = dynamic_cast<QPainter *>(obj);
    assert((painter != nullptr) && "OPainter not mixed with QPainter");
    QRect *r = dynamic_cast<QRect *>(rect);
    assert((r != nullptr) && "ORect not mixed with QRect");
    painter->drawText(*r, (Qt::AlignmentFlag)Int_val(ml_align), String_val(ml_text));
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OPainter_fillRect(OClass *obj, OClass *rect, OClass *color) {
    CAMLparam0();
    fprintf(stderr, "%s(%p, %p, %p)\n", __PRETTY_FUNCTION__, obj, rect, color);
    QPainter *painter = dynamic_cast<QPainter *>(obj);
    qDebug() <<  painter;
    assert((painter != nullptr) && "OPainter not mixed with QPainter");
    QRect *r = dynamic_cast<QRect *>(rect);
    qDebug() <<  *r;
    assert((r != nullptr) && "ORect not mixed with QRect");
    QColor *c = dynamic_cast<QColor *>(color);
    qDebug() <<  *c;
    assert((c != nullptr) && "OColor not mixed with QColor");
    painter->fillRect(*r, *c);
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OPainter_setPenColor(OClass *obj, OClass *color) {
    CAMLparam0();
    fprintf(stderr, "%s(%p, %p)\n", __PRETTY_FUNCTION__, obj, color);
    QPainter *painter = dynamic_cast<QPainter *>(obj);
    assert((painter != nullptr) && "OPainter not mixed with QPainter");
    QColor *c = dynamic_cast<QColor *>(color);
    painter->setPen(*c);
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OPainter_drawLine(OClass *obj, value ml_x1, value ml_y1, value ml_x2, value ml_y2) {
    CAMLparam4(ml_x1, ml_y1, ml_x2, ml_y2);
    fprintf(stderr, "%s(%p, %d, %d, %d, %d)\n", __PRETTY_FUNCTION__, obj, Int_val(ml_x1), Int_val(ml_y1), Int_val(ml_x2), Int_val(ml_y2));
    QPainter *painter = dynamic_cast<QPainter *>(obj);
    assert((painter != nullptr) && "OPainter not mixed with QPainter");
    painter->drawLine(Int_val(ml_x1), Int_val(ml_y1), Int_val(ml_x2), Int_val(ml_y2));
    CAMLreturn(Val_unit);
}
