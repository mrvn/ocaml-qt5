#include <QLayoutItem>

#include "OLayoutItem.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "debug.h"

OLayoutItem::OLayoutItem() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

OLayoutItem::~OLayoutItem() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

/* abstract
extern "C" value caml_mrvn_QT5_OLayoutItem_make(void) {
    DEBUG("%s()\n", __PRETTY_FUNCTION__);
    OQLayoutItem *obj = new OQLayoutItem();
    assert(obj != nullptr);
    return value(static_cast<OClass *>(obj));
}
*/
