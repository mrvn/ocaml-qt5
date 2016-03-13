#include <QLayout>
#include <QWidget>

#include "OLayout.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "OWidget.h"

OLayout::OLayout() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OLayout::~OLayout() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

void OLayout::preDestructor() {
    QLayout *layout = dynamic_cast<QLayout *>(this);
    assert((layout != nullptr) && "OLayout not mixed with QLayout");
    // remove all widgets from layout
    QLayoutItem *item;
    while((item = layout->takeAt(0)) != nullptr) {
	QWidget *w = item->widget();
	OWidget *o = dynamic_cast<OWidget *>(w);
	if (o != nullptr) {
	    // it's an ocaml widget, lower ref count
	    fprintf(stderr, "  decrementing\n");
	    o->decr();
	} else {
	    fprintf(stderr, "  pure QT5 widget, delete\n");
	    // pure QT5 widget, delete
	    delete w;
	}
    }
}

void OLayout::addWidget(OWidget *widget) {
    fprintf(stderr, "%p->%s(%p)\n", this, __PRETTY_FUNCTION__, widget);
    widget->incr();
    QLayout *layout = dynamic_cast<QLayout *>(this);
    assert((layout != nullptr) && "OLayout not mixed with QLayout");
    QWidget *w = dynamic_cast<QWidget *>(widget);
    assert((w != nullptr) && "OWidget not mixed with QWidget");
    layout->addWidget(w);
}

/* abstract
extern "C" value caml_mrvn_QT5_OLayout_make(void) {
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQLayout *obj = new OQLayout();
    assert(obj != nullptr);
    return value(static_cast<OClass *>(obj));
}
*/

extern "C" value caml_mrvn_QT5_OLayout_addWidget(OClass *obj, OClass *widget) {
    CAMLparam0();
    fprintf(stderr, "%s(%p, %p)\n", __PRETTY_FUNCTION__, obj, widget);
    OLayout *layout = dynamic_cast<OLayout *>(obj);
    assert((layout != nullptr) && "not mixed with OLayout");
    OWidget *w = dynamic_cast<OWidget *>(widget);
    assert((w != nullptr) && "not mixed with OWidget");
    layout->addWidget(w);
    CAMLreturn(Val_unit);
}
