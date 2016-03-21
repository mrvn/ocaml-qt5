#include <QPalette>

#include "OPalette.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "OColor.h"

OPalette::OPalette() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OPalette::~OPalette() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OQPalette::OQPalette() : OPalette(), QPalette() {
    fprintf(stderr, "%p [0x%lx]->%s()\n", this, OPalette::maybe_obj(), __PRETTY_FUNCTION__);
}

OQPalette::OQPalette(const QPalette &palette) : OPalette(), QPalette(palette) {
    fprintf(stderr, "%p [0x%lx]->%s(palette)\n", this, OPalette::maybe_obj(), __PRETTY_FUNCTION__);
}

OQPalette::~OQPalette() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, OPalette::maybe_obj(), __PRETTY_FUNCTION__);
}

extern "C" value caml_mrvn_QT5_OPalette_background(OClass *obj) {
    CAMLparam0();
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QPalette *palette = dynamic_cast<QPalette *>(obj);
    assert((palette != nullptr) && "OPalette not mixed with QPalette");
    QBrush brush = palette->background();
    OQColor *res = new OQColor(brush.color());
    assert(res != nullptr);
    CAMLreturn((value)dynamic_cast<OClass *>(res));
}

extern "C" value caml_mrvn_QT5_OPalette_alloc(const QPalette &palette) {
    CAMLparam0();
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQPalette *obj = new OQPalette(palette);
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}

extern "C" value caml_mrvn_QT5_OPalette_make() {
    CAMLparam0();
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQPalette *obj = new OQPalette();
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}
