#ifdef MRVN_QT5_SIGNAL_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_SIGNAL_H
#define MRVN_QT5_SIGNAL_H
#define MRVN_QT5_SIGNAL_H__INSIDE

#include <QObject>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/custom.h>
#include <caml/callback.h>
#include <cassert>

#include "debug.h"
#include "Connection.h"
#include "OObject.h"

class SignalBase {
public:
    SignalBase() { };
    virtual ~SignalBase() { };
    virtual QMetaObject::Connection connect(QObject *obj, value ml_fn) = 0;
};

value call2(value closure, bool arg);

template<class O, typename A>
class Signal : public SignalBase {
public:
    Signal(void (O::*fn)(A)) : fn_(fn) {
	DEBUG("%p->%s(%p)\n", this, __PRETTY_FUNCTION__, (void*)fn_);
    }
    virtual QMetaObject::Connection connect(QObject *obj, value closure) {
	DEBUG("%p->%s(obj = %p, fn = %p)\n", this, __PRETTY_FUNCTION__, obj, (void*)fn_);
	O *o = dynamic_cast<O*>(obj);
	assert(o != nullptr);
	// FIXME: attach to object for disconnect and destruction
	value *closurep = new value();
	assert(closurep != nullptr);
	*closurep = closure;
	caml_register_generational_global_root(closurep);
	return QObject::connect(o, fn_, [closurep](A arg) {
		DEBUG("triggered: closure = 0x%lx, arg = %s\n", *closurep, arg ? "true" : "false");
		call2(*closurep, arg);});
    }
private:
    void (O::*fn_)(A);
};

#undef MRVN_QT5_SIGNAL_H__INSIDE
#endif // #ifndef MRVN_QT5_SIGNAL_H
