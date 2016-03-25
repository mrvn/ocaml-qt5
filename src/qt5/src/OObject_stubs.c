#include <QObject>
#include <QTimerEvent>

#include "OObject.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <cassert>

#include "OEvent.h"
#include "OTimerEvent.h"

OObject::OObject() {
    DEBUG("%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OObject::~OObject() {
    DEBUG("%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

void OObject::preDestructor() {
    DEBUG("%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

bool OObject::event(QEvent *event) {
    CAMLparam0();
    CAMLlocal3(obj, handleEvent, res);
    static value hash = caml_hash_variant("external_event");
    //DEBUG("%p [0x%lx]->%s(%p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, event);
    obj = maybe_obj();
    if (obj != 0) { // ocaml object still atached
	handleEvent = caml_get_public_method(obj, hash);
	//DEBUG("  handleEvent = 0x%lx\n", handleEvent);
	if (handleEvent != 0) {
	    OEvent *oEvent = new OEvent(event);
	    //DEBUG("  oEvent = %p\n", oEvent);
	    assert(oEvent != nullptr);
	    DEBUG("%s: calling 0x%lx\n", __PRETTY_FUNCTION__, handleEvent);
            OClass *e = dynamic_cast<OClass *>(oEvent);
	    res = caml_callback2_exn(handleEvent, obj, (value)e);
	    if (Is_exception_result(res)) {
		// on exception pass event upstream
		res = Extract_exception(res);
		DEBUG("%s: callback got exception 0x%lx\n", __PRETTY_FUNCTION__, res);
		assert(false);
		oEvent->removeEvent();
	    } else {
		oEvent->removeEvent();
		if (Bool_val(res)) {
		    // all done
		    DEBUG("%s: handled\n", __PRETTY_FUNCTION__);
		    CAMLreturn(true);
		} else {
		    DEBUG("%s: not handled\n", __PRETTY_FUNCTION__);
		}
	    }
	}
    }
    // fall through to original event handler
    CAMLreturn(false);
}

void OObject::timerEvent(QTimerEvent *event) {
    CAMLparam0();
    CAMLlocal3(obj, handleEvent, res);
    static value hash = caml_hash_variant("external_timerEvent");
    //DEBUG("%p [0x%lx]->%s(%p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, event);
    obj = maybe_obj();
    if (obj != 0) { // ocaml object still atached
	handleEvent = caml_get_public_method(obj, hash);
	//DEBUG("  handleEvent = 0x%lx\n", handleEvent);
	if (handleEvent != 0) {
	    OTimerEvent *oTimerEvent = new OTimerEvent(event);
	    //DEBUG("  oEvent = %p\n", oEvent);
	    assert(oTimerEvent != nullptr);
	    DEBUG("%s: calling 0x%lx\n", __PRETTY_FUNCTION__, handleEvent);
            OClass *e = dynamic_cast<OClass *>(oTimerEvent);
	    res = caml_callback2_exn(handleEvent, obj, (value)e);
	    if (Is_exception_result(res)) {
		// on exception pass event upstream
		res = Extract_exception(res);
		DEBUG("%s: callback got exception 0x%lx\n", __PRETTY_FUNCTION__, res);
		assert(false);
		oTimerEvent->removeEvent();
	    } else {
		oTimerEvent->removeEvent();
                DEBUG("%s: handled\n", __PRETTY_FUNCTION__);
                CAMLreturn0;
	    }
	}
    }
    // fall through to original event handler
    qTimerEvent(event);
    CAMLreturn0;
}

extern "C" value caml_mrvn_QT5_OObject_qTimerEvent(OClass *obj, OClass *event) {
    CAMLparam0();
    DEBUG("%s(%p, %p)\n", __PRETTY_FUNCTION__, obj, event);
    OObject *o = dynamic_cast<OObject *>(obj);
    assert((o != nullptr) && "OObject not mixed with QObject");
    QTimerEvent *e = dynamic_cast<QTimerEvent *>(event);
    assert((e != nullptr) && "OTimerEvent not mixed with QTimerEvent");
    o->qTimerEvent(e);
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OObject_make(void) {
    CAMLparam0();
    DEBUG("%s\n", __PRETTY_FUNCTION__);
    OQObject *obj = new OQObject();
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}

extern "C" value caml_mrvn_QT5_OObject_destroy(OObject *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    delete obj;
    CAMLreturn(Val_unit);
}
