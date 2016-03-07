#ifndef MRVN_QT5_EVENTHANDLER_H
#define MRVN_QT5_EVENTHANDLER_H

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/custom.h>
#include <caml/callback.h>
#include <cassert>
#include <stdio.h>

#include "Proxy.h"

extern char caml_mrvn_QT5_EventHandler_identifier[];
extern struct custom_operations caml_mrvn_QT5_EventHandler_custom_ops;

class EventHandlerBase {
public:
    EventHandlerBase() { };
    virtual ~EventHandlerBase() { };
    virtual void set(value ml_proxy, value ml_fn) = 0;
};

class QEvent;
bool call_bool_QEvent(value closure, QEvent *event);

template<class O>
class EventHandler : public EventHandlerBase {
public:
    EventHandler(void (O::*fn)(value)) : fn_(fn) {
	fprintf(stderr, "%p->%s(%p)\n", this, __PRETTY_FUNCTION__, (void*)fn_);
    }
    virtual void set(value ml_proxy, value closure) {
	CAMLparam2(ml_proxy, closure);
	fprintf(stderr, "%p->%s(ml_proxy = 0x%lx, closure = 0x%lx, fn = %p)\n", this, __PRETTY_FUNCTION__, ml_proxy, closure, (void*)fn_);
	Proxy<O> *proxy = (Proxy<O> *)Data_custom_val(ml_proxy);
	fprintf(stderr, "%s: proxy = %p\n", __PRETTY_FUNCTION__, proxy);
	proxy->call(fn_, closure);
	CAMLreturn0;
    }
private:
    void (O::*fn_)(value);
};

#endif // #ifndef MRVN_QT5_EVENTHANDLER_H
