#include <QAbstractButton>

#include "OAbstractButton.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "Signal.h"

OAbstractButton::OAbstractButton() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

OAbstractButton::~OAbstractButton() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

/* abstract
extern "C" value caml_mrvn_QT5_OAbstractButton_make(void) {
    DEBUG("%s()\n", __PRETTY_FUNCTION__);
    OQAbstractButton *obj = new OQAbstractButton();
    assert(obj != nullptr);
    return value(static_cast<OClass *>(obj));
}
*/

Signal<QAbstractButton, bool> QAbstractButton_clicked(&QAbstractButton::clicked);

extern "C"
value caml_mrvn_QT5_QAbstractButton_clicked(void) {
    CAMLparam0();
    DEBUG("%s = %p\n", __PRETTY_FUNCTION__, (void*)&QAbstractButton_clicked);
    CAMLreturn((value)&QAbstractButton_clicked);
}
