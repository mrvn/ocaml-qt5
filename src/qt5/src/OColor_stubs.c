#include <QColor>

#include "OColor.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OColor::OColor() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OColor::~OColor() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OQColor::OQColor(const char *name) : OColor(), QColor(name) {
    fprintf(stderr, "%p [0x%lx]->%s('%s')\n", this, OColor::maybe_obj(), __PRETTY_FUNCTION__, name);
}

OQColor::OQColor(const QColor &color) : OColor(), QColor(color
) {
    fprintf(stderr, "%p [0x%lx]->%s(color)\n", this, OColor::maybe_obj(), __PRETTY_FUNCTION__);
}

OQColor::~OQColor() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, OColor::maybe_obj(), __PRETTY_FUNCTION__);
}

extern "C" value caml_mrvn_QT5_OColor_darker(OClass *obj) {
    CAMLparam0();
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QColor *color = dynamic_cast<QColor *>(obj);
    assert((color != nullptr) && "OColor not mixed with QColor");
    QColor darker = color->darker();
    OQColor *res = new OQColor(darker);
    assert(res != nullptr);
    CAMLreturn(value(static_cast<OClass *>(res)));
}

extern "C" value caml_mrvn_QT5_OColor_lighter(OClass *obj) {
    CAMLparam0();
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QColor *color = dynamic_cast<QColor *>(obj);
    assert((color != nullptr) && "OColor not mixed with QColor");
    QColor lighter = color->lighter();
    OQColor *res = new OQColor(lighter);
    assert(res != nullptr);
    CAMLreturn(value(static_cast<OClass *>(res)));
}

extern "C" value caml_mrvn_QT5_OColor_make(value ml_name) {
    CAMLparam1(ml_name);
    const char *name = String_val(ml_name);
    OQColor *res = new OQColor(name);
    assert(res != nullptr);
    CAMLreturn(value(static_cast<OClass *>(res)));
}
