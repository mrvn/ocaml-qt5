#ifdef MRVN_QT5_OCLASS_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OCLASS_H
#define MRVN_QT5_OCLASS_H
#define MRVN_QT5_OCLASS_H__INSIDE

#include <utility>
#include <caml/mlvalues.h>

#include "debug.h"

class OClass {
public:
    OClass(size_t ref_count=0);
    virtual ~OClass();
    void register_obj(value ml_obj);
    void unregister_obj();
    void incr(size_t amount=1);
    void decr(size_t amount=1);
    virtual void preDestructor();
protected:
    value maybe_obj();
    value maybe_obj() const;
    value get_obj();
    value get_obj() const;
private:
    value ml_obj_;
    size_t ref_count_;
};

template<class O, class Q>
class TClass : public virtual O, public Q {
public:
    template<typename ... A>
    TClass(A && ... a) : O(), Q(std::forward<A>(a) ...) {
	DEBUG("%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TClass() {
	DEBUG("%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
	O::preDestructor();
    }
};

#undef MRVN_QT5_OCLASS_H__INSIDE
#endif // #ifndef MRVN_QT5_OCLASS_H
