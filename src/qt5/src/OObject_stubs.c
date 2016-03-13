#include <QObject>

#include "OObject.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <cassert>

#include "OEvent.h"

OObject::OObject() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OObject::~OObject() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

void OObject::preDestructor() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

bool OObject::event(QEvent *event) {
    CAMLparam0();
    CAMLlocal3(obj, handleEvent, res);
    static value hash = caml_hash_variant("external_event");
    //fprintf(stderr, "%p [0x%lx]->%s(%p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, event);
    obj = maybe_obj();
    if (obj != 0) { // ocaml object still atached
	handleEvent = caml_get_public_method(obj, hash);
	//fprintf(stderr, "  handleEvent = 0x%lx\n", handleEvent);
	if (handleEvent != 0) {
	    OEvent *oEvent = new OEvent(event);
	    //fprintf(stderr, "  oEvent = %p\n", oEvent);
	    assert(oEvent != nullptr);
	    fprintf(stderr, "%s: calling 0x%lx\n", __PRETTY_FUNCTION__, handleEvent);
	    res = caml_callback2_exn(handleEvent, obj, (value)oEvent);
	    if (Is_exception_result(res)) {
		// on exception pass event upstream
		res = Extract_exception(res);
		fprintf(stderr, "%s: callback got exception 0x%lx\n", __PRETTY_FUNCTION__, res);
		assert(false);
		oEvent->removeEvent();
	    } else {
		oEvent->removeEvent();
		if (Bool_val(res)) {
		    // all done
		    fprintf(stderr, "%s: handled\n", __PRETTY_FUNCTION__);
		    CAMLreturn(true);
		} else {
		    fprintf(stderr, "%s: not handled\n", __PRETTY_FUNCTION__);
		}
	    }
	}
    }
    // fall through to original event handler
    CAMLreturn(false);
}

extern "C" value caml_mrvn_QT5_OObject_make(void) {
    CAMLparam0();
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQObject *obj = new OQObject();
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}

extern "C" value caml_mrvn_QT5_OObject_destroy(OObject *obj) {
    CAMLparam0();
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    delete obj;
    CAMLreturn(Val_unit);
}
