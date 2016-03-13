#include <QLayoutItem>

#include "OLayoutItem.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OLayoutItem::OLayoutItem() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OLayoutItem::~OLayoutItem() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

/* abstract
extern "C" value caml_mrvn_QT5_OLayoutItem_make(void) {
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQLayoutItem *obj = new OQLayoutItem();
    assert(obj != nullptr);
    return value(static_cast<OClass *>(obj));
}
*/
