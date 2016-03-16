#include <QPaintDevice>

#include "OPaintDevice.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OPaintDevice::OPaintDevice() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OPaintDevice::~OPaintDevice() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
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
