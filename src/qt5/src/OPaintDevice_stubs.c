#include <QPaintDevice>

#include "OPaintDevice.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OPaintDevice::OPaintDevice() : painter_(nullptr) {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OPaintDevice::~OPaintDevice() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
    assert((painter_ == nullptr) && "OPainter still registered");
}

void OPaintDevice::registerPainter(OPainter *painter) {
    fprintf(stderr, "%p [0x%lx]->%s(%p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, painter);
    assert((painter_ == nullptr) && "already have a painter");
    painter_ = painter;
    incr();
}

void OPaintDevice::unregisterPainter(OPainter *painter) {
    fprintf(stderr, "%p [0x%lx]->%s(%p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, painter);
    assert((painter_ == painter) && "not my painter");
    painter_ = nullptr;
    decr();
}

/* protected
extern "C" value caml_mrvn_QT5_OPaintDevice_make(void) {
    CAMLparam0();
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQPaintDevice *obj = new OQPaintDevice();
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}
*/
