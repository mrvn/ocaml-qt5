#include <QWidget>

#include "OWidget.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OWidget::OWidget() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OWidget::~OWidget() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OQWidget::~OQWidget() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
    preDestructor();
}

extern "C" value caml_mrvn_QT5_OWidget_make(void) {
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQWidget *obj = new OQWidget();
    assert(obj != nullptr);
    return value(static_cast<OClass *>(obj));
}
