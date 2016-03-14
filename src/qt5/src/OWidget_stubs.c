#include <QWidget>
#include <QLayout>

#include "OWidget.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "OLayout.h"

OWidget::OWidget() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OWidget::~OWidget() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

void OWidget::setLayout(OLayout *layout) {
    fprintf(stderr, "%p->%s(%p)\n", this, __PRETTY_FUNCTION__, layout);
    layout->incr();
    QWidget *w = dynamic_cast<QWidget *>(this);
    assert((w != nullptr) && "OWidget not mixed with QWidget");
    QLayout *q = dynamic_cast<QLayout *>(layout);
    assert((q != nullptr) && "OLayout not mixed with QLayout");
    w->setLayout(q);
}

extern "C" value caml_mrvn_QT5_OWidget_make(void) {
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQWidget *obj = new OQWidget();
    assert(obj != nullptr);
    return value(static_cast<OClass *>(obj));
}

extern "C" value caml_mrvn_QT5_OWidget_show(OClass *obj) {
    CAMLparam0();
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QWidget *w = dynamic_cast<QWidget *>(obj);
    assert((w != nullptr) && "OWidget not mixed with QWidget");
    w->show();
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OWidget_resize(OClass *obj, value ml_x, value ml_y) {
    CAMLparam2(ml_x, ml_y);
    fprintf(stderr, "%s(%p, %d, %d)\n", __PRETTY_FUNCTION__, obj, Int_val(ml_x), Int_val(ml_y));
    QWidget *widget = dynamic_cast<QWidget *>(obj);
    assert((widget != nullptr) && "OWidget not mixed with QWidget");
    widget->resize(Int_val(ml_x), Int_val(ml_y));
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OWidget_setWindowTitle(OClass *obj, value ml_text) {
    CAMLparam1(ml_text);
    fprintf(stderr, "%s(%p, \"%s\")\n", __PRETTY_FUNCTION__, obj, String_val(ml_text));
    QString text(String_val(ml_text));
    QWidget *widget = dynamic_cast<QWidget *>(obj);
    assert((widget != nullptr) && "OWidget not mixed with QWidget");
    widget->setWindowTitle(text);
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OWidget_setLayout(OClass *obj, OClass *layout) {
    CAMLparam0();
    fprintf(stderr, "%s(%p, %p)\n", __PRETTY_FUNCTION__, obj, layout);
    OWidget *w = dynamic_cast<OWidget *>(obj);
    assert((w != nullptr) && "OWidget not mixed with OWidget");
    OLayout *x = dynamic_cast<OLayout *>(layout);
    assert((x != nullptr) && "OWidget not mixed with OLayout");
    w->setLayout(x);
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OWidget_setFocusPolicy(OClass *obj, value ml_focus) {
    CAMLparam1(ml_focus);
    fprintf(stderr, "%s(%p, 0x%x)\n", __PRETTY_FUNCTION__, obj, Int_val(ml_focus));
    QWidget *widget = dynamic_cast<QWidget *>(obj);
    assert((widget != nullptr) && "not mixed with QWidget");
    widget->setFocusPolicy((Qt::FocusPolicy)Int_val(ml_focus));
    CAMLreturn(Val_unit);
}
