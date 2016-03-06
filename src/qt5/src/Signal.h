#ifndef MRVN_QT5_SIGNAL_H
#define MRVN_QT5_SIGNAL_H

#include <QObject>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/custom.h>
#include <caml/callback.h>
#include <cassert>
#include <stdio.h>

#include "Connection.h"
#include "OObject.h"

extern char caml_mrvn_QT5_Signal_identifier[];
extern struct custom_operations caml_mrvn_QT5_Signal_custom_ops;

class SignalBase {
public:
    SignalBase() { };
    virtual ~SignalBase() { };
    virtual QMetaObject::Connection connect(QObject *obj, value ml_fn) = 0;
};

void call2(value closure, bool arg);

template<class O, typename A>
class Signal : public SignalBase {
public:
    Signal(void (O::*fn)(A)) : fn_(fn) {
	fprintf(stderr, "%p->%s(%p)\n", this, __PRETTY_FUNCTION__, (void*)fn_);
    }
    virtual QMetaObject::Connection connect(QObject *obj, value closure) {
	fprintf(stderr, "%p->%s(obj = %p, fn = %p)\n", this, __PRETTY_FUNCTION__, obj, (void*)fn_);
	O *o = dynamic_cast<O*>(obj);
	assert(o != nullptr);
	return QObject::connect(o, fn_, [closure](A arg) { fprintf(stderr, "triggered\n"); call2(closure, arg);});
    }
private:
    void (O::*fn_)(A);
};

#endif // #ifndef MRVN_QT5_SIGNAL_H
