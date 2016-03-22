#ifdef MRVN_QT5_OOBJECT_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OOBJECT_H
#define MRVN_QT5_OOBJECT_H
#define MRVN_QT5_OOBJECT_H__INSIDE

#include "OClass.h"

class QObject;
class QEvent;
class QTimerEvent;

class OObject : public virtual OClass {
public:
    OObject();
    virtual ~OObject();
    virtual void preDestructor();
    virtual bool event(QEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    virtual void qTimerEvent(QTimerEvent *event) = 0;
};

template<class O, class Q>
class TObject : public TClass<O, Q> {
public:
    template<typename ... A>
    TObject(A && ... a) : TClass<O, Q>(std::forward<A>(a) ...) {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TObject() {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual bool event(QEvent *event) final override {
	if (O::event(event)) {
	    return true;
	} else {
	    return Q::event(event);
	}
    };
    virtual void timerEvent(QTimerEvent *event) final override {
        O::timerEvent(event);
    }
    virtual void qTimerEvent(QTimerEvent *event) final override {
        Q::timerEvent(event);
    }
};

using OQObject = TObject<OObject, QObject>;

#undef MRVN_QT5_OOBJECT_H__INSIDE
#endif // #ifndef MRVN_QT5_OOBJECT_H
