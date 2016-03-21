#include <QWidget>
#include <QLayout>
#include <QEvent>
#include <QKeyEvent>
#include <QSize>

#include "OWidget.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <cassert>

#include "OLayout.h"
#include "OPaintEvent.h"
#include "OKeyEvent.h"
#include "ORect.h"
#include "OSize.h"

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

void OWidget::paintEvent(QPaintEvent *event) {
    CAMLparam0();
    CAMLlocal3(obj, handleEvent, res);
    static value hash = caml_hash_variant("external_paintEvent");
    //fprintf(stderr, "%p [0x%lx]->%s(%p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, event);
    obj = maybe_obj();
    if (obj == 0) {
        qPaintEvent(event); // ocaml object detached
    } else {
        handleEvent = caml_get_public_method(obj, hash);
        //fprintf(stderr, "  handleEvent = 0x%lx\n", handleEvent);
        if (handleEvent == 0) {
            qPaintEvent(event); // no override
        } else {
            OPaintEvent *oEvent = new OPaintEvent(event);
            //fprintf(stderr, "  oEvent = %p\n", oEvent);
            assert(oEvent != nullptr);
            fprintf(stderr, "%s: calling 0x%lx\n", __PRETTY_FUNCTION__, handleEvent);
            OClass *e = dynamic_cast<OClass *>(oEvent);
            res = caml_callback2_exn(handleEvent, obj, (value)e);
            if (Is_exception_result(res)) {
                // on exception pass event upstream
                res = Extract_exception(res);
                fprintf(stderr, "%s: callback got exception 0x%lx\n", __PRETTY_FUNCTION__, res);
                assert(false);
                oEvent->removeEvent();
                qPaintEvent(event);
            } else {
                oEvent->removeEvent();
                fprintf(stderr, "%s: dispatched\n", __PRETTY_FUNCTION__);
            }
        }
    }
    CAMLreturn0;
}

QSize OWidget::sizeHint() const {
    CAMLparam0();
    CAMLlocal3(obj, handleEvent, res);
    static value hash = caml_hash_variant("external_sizeHint");
    //fprintf(stderr, "%p [0x%lx]->%s(%p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, event);
    obj = maybe_obj();
    if (obj == 0) {
        CAMLreturnT(QSize, qSizeHint()); // ocaml object detached
    } else {
        handleEvent = caml_get_public_method(obj, hash);
        //fprintf(stderr, "  handleEvent = 0x%lx\n", handleEvent);
        if (handleEvent == 0) {
            CAMLreturnT(QSize, qSizeHint()); // no override
        } else {
            fprintf(stderr, "%s: calling 0x%lx\n", __PRETTY_FUNCTION__, handleEvent);
            res = caml_callback_exn(handleEvent, obj);
            if (Is_exception_result(res)) {
                // on exception pass event upstream
                res = Extract_exception(res);
                fprintf(stderr, "%s: callback got exception 0x%lx\n", __PRETTY_FUNCTION__, res);
                assert(false);
                CAMLreturnT(QSize, qSizeHint());
            } else {
                fprintf(stderr, "%s: dispatched\n", __PRETTY_FUNCTION__);
		QSize *size = dynamic_cast<QSize *>((OClass *)res);
		assert((size != nullptr) && "OSize not mixed with QSize");
		CAMLreturnT(QSize, *size);
            }
        }
    }
}

QSize OWidget::minimumSizeHint() const {
    CAMLparam0();
    CAMLlocal3(obj, handleEvent, res);
    static value hash = caml_hash_variant("external_minimumSizeHint");
    //fprintf(stderr, "%p [0x%lx]->%s(%p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, event);
    obj = maybe_obj();
    if (obj == 0) {
        CAMLreturnT(QSize, qMinimumSizeHint()); // ocaml object detached
    } else {
        handleEvent = caml_get_public_method(obj, hash);
        //fprintf(stderr, "  handleEvent = 0x%lx\n", handleEvent);
        if (handleEvent == 0) {
            CAMLreturnT(QSize, qMinimumSizeHint()); // no override
        } else {
            fprintf(stderr, "%s: calling 0x%lx\n", __PRETTY_FUNCTION__, handleEvent);
            res = caml_callback_exn(handleEvent, obj);
            if (Is_exception_result(res)) {
                // on exception pass event upstream
                res = Extract_exception(res);
                fprintf(stderr, "%s: callback got exception 0x%lx\n", __PRETTY_FUNCTION__, res);
                assert(false);
                CAMLreturnT(QSize, qMinimumSizeHint());
            } else {
                fprintf(stderr, "%s: dispatched\n", __PRETTY_FUNCTION__);
		QSize *size = dynamic_cast<QSize *>((OClass *)res);
		assert((size != nullptr) && "OSize not mixed with QSize");
		CAMLreturnT(QSize, *size);
            }
        }
    }
}

void OWidget::keyPressEvent(QKeyEvent * event) {
    CAMLparam0();
    CAMLlocal3(obj, handleEvent, res);
    static value hash = caml_hash_variant("external_keyPressEvent");
    //fprintf(stderr, "%p [0x%lx]->%s(%p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, event);
    obj = maybe_obj();
    if (obj == 0) {
        qKeyPressEvent(event); // ocaml object detached
    } else {
        handleEvent = caml_get_public_method(obj, hash);
        //fprintf(stderr, "  handleEvent = 0x%lx\n", handleEvent);
        if (handleEvent == 0) {
            qKeyPressEvent(event); // no override
        } else {
            OKeyEvent *oEvent = new OKeyEvent(event);
            //fprintf(stderr, "  oEvent = %p\n", oEvent);
            assert(oEvent != nullptr);
            fprintf(stderr, "%s: calling 0x%lx\n", __PRETTY_FUNCTION__, handleEvent);
            OClass *e = dynamic_cast<OClass *>(oEvent);
            res = caml_callback2_exn(handleEvent, obj, (value)e);
            if (Is_exception_result(res)) {
                // on exception pass event upstream
                res = Extract_exception(res);
                fprintf(stderr, "%s: callback got exception 0x%lx\n", __PRETTY_FUNCTION__, res);
                assert(false);
                oEvent->removeEvent();
                qKeyPressEvent(event);
            } else {
                oEvent->removeEvent();
                fprintf(stderr, "%s: dispatched\n", __PRETTY_FUNCTION__);
            }
        }
    }
    CAMLreturn0;
}

extern "C" value caml_mrvn_QT5_OWidget_qPaintEvent(OClass *obj, OClass *event) {
    CAMLparam0();
    fprintf(stderr, "%s(%p, %p)\n", __PRETTY_FUNCTION__, obj, event);
    OWidget *widget = dynamic_cast<OWidget *>(obj);
    assert((widget != nullptr) && "not an OWidget");
    OPaintEvent *oEvent = dynamic_cast<OPaintEvent *>(event);
    assert((oEvent != nullptr) && "not an OPaintEvent");
    QPaintEvent *e = oEvent->event();
    assert((e != nullptr) && "QPaintEvent missing");
    widget->qPaintEvent(e);
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OWidget_qKeyPressEvent(OClass *obj, OClass *event) {
    CAMLparam0();
    fprintf(stderr, "%s(%p, %p)\n", __PRETTY_FUNCTION__, obj, event);
    OWidget *widget = dynamic_cast<OWidget *>(obj);
    assert((widget != nullptr) && "not an OWidget");
    OKeyEvent *oEvent = dynamic_cast<OKeyEvent *>(event);
    assert((oEvent != nullptr) && "not an OKeyEvent");
    QKeyEvent *e = oEvent->event();
    assert((e != nullptr) && "QKeyPressEvent missing");
    widget->qKeyPressEvent(e);
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OWidget_qSizeHint(OClass *obj) {
    CAMLparam0();
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    OWidget *widget = dynamic_cast<OWidget *>(obj);
    assert((widget != nullptr) && "not an OWidget");
    QSize size = widget->qSizeHint();
    CAMLreturn(caml_mrvn_QT5_OSize_alloc(size.width(), size.height()));
}

extern "C" value caml_mrvn_QT5_OWidget_qMinimumSizeHint(OClass *obj) {
    CAMLparam0();
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    OWidget *widget = dynamic_cast<OWidget *>(obj);
    assert((widget != nullptr) && "not an OWidget");
    QSize size = widget->qMinimumSizeHint();
    CAMLreturn(caml_mrvn_QT5_OSize_alloc(size.width(), size.height()));
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
    assert((widget != nullptr) && "OWidget not mixed with QWidget");
    widget->setFocusPolicy((Qt::FocusPolicy)Int_val(ml_focus));
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OWidget_contentsRect(OClass *obj) {
    CAMLparam0();
    CAMLlocal1(res);
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QWidget *widget = dynamic_cast<QWidget *>(obj);
    assert((widget != nullptr) && "OWidget not mixed with QWidget");
    QRect r = widget->contentsRect();
    res = caml_mrvn_QT5_ORect_alloc(r.x(), r.y(), r.width(), r.height());
    CAMLreturn(res);
}

extern "C" value caml_mrvn_QT5_OWidget_update(OClass *obj) {
    CAMLparam0();
    CAMLlocal1(res);
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QWidget *widget = dynamic_cast<QWidget *>(obj);
    assert((widget != nullptr) && "OWidget not mixed with QWidget");
    widget->update();
    CAMLreturn(Val_unit);
}
