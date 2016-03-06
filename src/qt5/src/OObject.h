#ifndef MRVN_QT5_OOBJECT_H
#define MRVN_QT5_OOBJECT_H

#include <QObject>
#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>

#include "OClass.h"

bool call_bool_QEvent(value closure, QEvent *event);

template<class Q>
class OObject : public Q, public OClass {
public:
    template<typename ... A>
    OObject(A && ... a) : Q(a...), ml_handler_event_(0) {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, proxy(), __PRETTY_FUNCTION__);
	caml_register_generational_global_root(&ml_handler_event_);
    }
    virtual ~OObject() {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, proxy(), __PRETTY_FUNCTION__);
	caml_remove_generational_global_root(&ml_handler_event_);
    }
    virtual bool event(QEvent *event) {
	fprintf(stderr, "%p <0x%lx>->%s(%p): ml_handle_event_ = 0x%lu\n", this, proxy(), __PRETTY_FUNCTION__, event, ml_handler_event_);
	if (ml_handler_event_ == 0) {
	    return Q::event(event);
	} else {
	    fprintf(stderr, "%p <0x%lx>->%s: calling 0x%lu\n", this, proxy(), __PRETTY_FUNCTION__, ml_handler_event_);
	    if (!call_bool_QEvent(ml_handler_event_, event)) {
		// not handled by the handler, pass it upstream
		fprintf(stderr, "%p <0x%lx>->%s: not handled\n", this, proxy(), __PRETTY_FUNCTION__);
		return Q::event(event);
	    } else {
		fprintf(stderr, "%p <0x%lx>->%s: handled\n", this, proxy(), __PRETTY_FUNCTION__);
		return true;
	    }
	}
    }
    virtual void set_handler_event(value closure) {
	fprintf(stderr, "%p <0x%lx>->%s(0x%lu)\n", this, proxy(), __PRETTY_FUNCTION__, closure);
	CAMLparam1(closure);
	caml_modify_generational_global_root(&ml_handler_event_, closure);
	CAMLreturn0;
    }
private:
    value ml_handler_event_;
};

#endif // #ifndef MRVN_QT5_OOBJECT_H
