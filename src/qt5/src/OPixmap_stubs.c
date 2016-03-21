#include <QPixmap>

#include "OPixmap.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <cassert>

#include "ORect.h"

OPixmap::OPixmap() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OPixmap::~OPixmap() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

extern "C" value caml_mrvn_QT5_OPixmap_make(value ml_width, value ml_height) {
  fprintf(stderr, "%s(%d, %d)\n", __PRETTY_FUNCTION__, Int_val(ml_width), Int_val(ml_height));
    OQPixmap *obj = new OQPixmap(Int_val(ml_width), Int_val(ml_height));
    assert(obj != nullptr);
    return value(static_cast<OClass *>(obj));
}

extern "C" value caml_mrvn_QT5_OPixmap_rect(OClass *obj) {
    CAMLparam0();
    CAMLlocal1(res);
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QPixmap *pixmap = dynamic_cast<QPixmap *>(obj);
    assert((pixmap != nullptr) && "OPixmap not mixed with QPixmap");
    QRect r = pixmap->rect();
    res = caml_mrvn_QT5_ORect_alloc(r.x(), r.y(), r.width(), r.height());
    CAMLreturn(res);
}

