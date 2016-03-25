#include <QGridLayout>
#include <QWidget>

#include "OGridLayout.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "OWidget.h"
#include "Signal.h"

OGridLayout::OGridLayout() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

OGridLayout::~OGridLayout() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
}

void OGridLayout::addWidgetAt(OWidget *widget, int row, int column, int rowSpan, int columnSpan) {
    DEBUG("%p->%s(%p, %d, %d, %d, %d)\n", this, __PRETTY_FUNCTION__, widget, row, column, rowSpan, columnSpan);
    widget->incr();
    QGridLayout *layout = dynamic_cast<QGridLayout *>(this);
    assert((layout != nullptr) && "OGridLayout not mixed with QGridLayout");
    QWidget *w = dynamic_cast<QWidget *>(widget);
    assert((w != nullptr) && "OWidget not mixed with QWidget");
    if ((rowSpan == 1) && (columnSpan == 1)) {
	layout->addWidget(w, row, column);
    } else {
	layout->addWidget(w, row, column, rowSpan, columnSpan);
    }
}

extern "C" value caml_mrvn_QT5_OGridLayout_make(void) {
    DEBUG("%s()\n", __PRETTY_FUNCTION__);
    OQGridLayout *obj = new OQGridLayout();
    assert(obj != nullptr);
    return value(static_cast<OClass *>(obj));
}

extern "C" value caml_mrvn_QT5_OGridLayout_addWidgetAt(OClass *obj, OClass *widget, value at) {
    CAMLparam1(at);
    DEBUG("%s(%p, %p)\n", __PRETTY_FUNCTION__, obj, widget);
    OGridLayout *layout = dynamic_cast<OGridLayout *>(obj);
    assert((layout != nullptr) && "not mixed with OGridLayout");
    OWidget *w = dynamic_cast<OWidget *>(widget);
    assert((w != nullptr) && "not mixed with OWidget");
    int row = Int_val(Field(at, 0));
    int column = Int_val(Field(at, 1));
    int rowSpan = Int_val(Field(at, 2));
    int columnSpan = Int_val(Field(at, 3));
    layout->addWidgetAt(w, row, column, rowSpan, columnSpan);
    CAMLreturn(Val_unit);
}
