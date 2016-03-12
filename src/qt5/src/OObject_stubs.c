#include <QObject>

#include "OObject.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <cassert>

OObject::OObject() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OObject::~OObject() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

void OObject::preDestructor(QObject *obj) {
    fprintf(stderr, "%p->%s(%p)\n", this, __PRETTY_FUNCTION__, obj);
}

bool OObject::event(QEvent *event) {
    CAMLparam0();
    CAMLlocal3(obj, handleEvent, res);
    static value hash = caml_hash_variant("externalEvent");
    fprintf(stderr, "%p <0x%lx>->%s(%p)\n", this, get_obj(), __PRETTY_FUNCTION__, event);
    obj = get_obj();
    handleEvent = caml_get_public_method(obj, hash);
    if (handleEvent != 0) {
	fprintf(stderr, "  calling 0x%lu\n", handleEvent);
	res = caml_callback2(handleEvent, obj, (value)event);
	if (Is_exception_result(res)) {
	    // on exception pass event upstream
	    res = Extract_exception(res);
	    fprintf(stderr, "  callback got exception 0x%ld\n", res);
	} else if (Bool_val(res)) {
	    // all done
	    fprintf(stderr, "  handled\n");
	    CAMLreturn(true);
	} else {
	    fprintf(stderr, "  not handled\n");
	}
    } else {
	fprintf(stderr, "  not intercepted\n");
    }
    QObject *q = dynamic_cast<QObject *>(this);
    assert((q != nullptr) && "OObject not mixed with QObject");
    CAMLreturn(q->QObject::event(event));
}

OQObject::~OQObject() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
    preDestructor(this);
}

extern "C" value caml_mrvn_QT5_OObject_make(void) {
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQObject *obj = new OQObject();
    assert(obj != nullptr);
    return value(static_cast<OClass *>(obj));
}

extern "C" void caml_mrvn_QT5_OObject_destroy(OObject *obj) {
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    delete obj;
}

