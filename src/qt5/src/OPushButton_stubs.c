#include <QPushButton>

#include "OPushButton.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <cassert>

#include "OEvent.h"

OPushButton::OPushButton() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OPushButton::~OPushButton() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

class OQPushButton : public OPushButton, public QPushButton {
public:
    OQPushButton(QString & text) : OPushButton(), QPushButton(text) {
	fprintf(stderr, "%p->%s(\"%s\")\n", this, __PRETTY_FUNCTION__, text.toUtf8().constData());
    }
    virtual ~OQPushButton() {
	fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
	preDestructor();
    }
    virtual bool event(QEvent *event) final override {
	CAMLparam0();
	CAMLlocal3(obj, handleEvent, res);
	static value hash = caml_hash_variant("external_event");
	fprintf(stderr, "%p <0x%lx>->%s(%p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, event);
	obj = maybe_obj();
	if (obj != 0) { // ocaml object still atached
	    fprintf(stderr, "  obj = 0x%lx\n", obj);
	    handleEvent = caml_get_public_method(obj, hash);
	    fprintf(stderr, "  handleEvent = 0x%lx\n", handleEvent);
	    if (handleEvent != 0) {
		OEvent *oEvent = new OEvent(event);
		fprintf(stderr, "  oEvent = %p\n", oEvent);
		assert(oEvent != nullptr);
		fprintf(stderr, "  calling 0x%lx\n", handleEvent);	    
		res = caml_callback2(handleEvent, obj, (value)oEvent);
		oEvent->removeEvent();
		if (Is_exception_result(res)) {
		    // on exception pass event upstream
		    res = Extract_exception(res);
		    fprintf(stderr, "  callback got exception 0x%lx\n", res);
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
	}
	// fall through to original event handler
	CAMLreturn(QPushButton::event(event));
    }
};

extern "C" value caml_mrvn_QT5_OPushButton_make(value ml_text) {
    CAMLparam1(ml_text);
    fprintf(stderr, "%s(\"%s\")\n", __PRETTY_FUNCTION__, String_val(ml_text));
    QString text(String_val(ml_text));
    OQPushButton *obj = new OQPushButton(text);
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}
