#ifndef MRVN_QT5_PROXY_H
#define MRVN_QT5_PROXY_H

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/custom.h>
#include <cassert>

extern char caml_mrvn_QT5_Proxy_identifier[];
extern struct custom_operations caml_mrvn_QT5_Proxy_custom_ops;

template<class O>
class Proxy {
public:
    virtual ~Proxy() {
	fprintf(stderr, "%p [%p]->%s()\n", this, obj_, __PRETTY_FUNCTION__);
	if (obj_ != nullptr) {
	    fprintf(stderr, "%p [%p]->%s(): ref_count = %zu, proxy = 0x%lx\n", this, obj_, __PRETTY_FUNCTION__, obj_->ref_count(), obj_->proxy());
	    assert(obj_->ref_count() == 0);
	    delete obj_;
	    // destructor must call Proxy<O>::invalidate()
	    assert(obj_ == nullptr);
	}
	fprintf(stderr, "%p [%p]->%s() done\n", this, obj_, __PRETTY_FUNCTION__);
    }

    virtual void invalidate() {
	fprintf(stderr, "%p [%p]->%s()\n", this, obj_, __PRETTY_FUNCTION__);
	obj_ = nullptr;
    }
    
    template<typename T, typename A>
    T call(T (O::*fn)(A arg), A arg) {
	fprintf(stderr, "%p [%p]->%s(fn = %p)\n", this, obj_, __PRETTY_FUNCTION__, (void*)fn);
	if (obj_ == nullptr) {
	    // FIXME: throw exception
	    assert(false);
	}
	return (obj_->*fn)(arg);
    }
    template<typename A>
    void call(void (O::*fn)(A arg), A arg) {
	fprintf(stderr, "%p [%p]->%s(fn = %p)\n", this, obj_, __PRETTY_FUNCTION__, (void*)fn);
	if (obj_ == nullptr) {
	    // FIXME: throw exception
	    assert(false);
	}
	(obj_->*fn)(arg);
    }
    template<typename T, typename A>
    T call(T (O::*fn)(A arg) const, A arg) const {
	fprintf(stderr, "%p [%p]->%s(fn = %p)\n", this, obj_, __PRETTY_FUNCTION__, (void*)fn);
	if (obj_ == nullptr) {
	    // FIXME: throw exception
	    assert(false);
	}
	return (obj_->*fn)(arg);
    }
    template<typename A>
    void call(void (O::*fn)(A arg) const, A arg) const {
	fprintf(stderr, "%p [%p]->%s(fn = %p)\n", this, obj_, __PRETTY_FUNCTION__, (void*)fn);
	if (obj_ == nullptr) {
	    // FIXME: throw exception
	    assert(false);
	}
	(obj_->*fn)(arg);
    }
    template<typename T>
    T call(T (O::*fn)()) {
	fprintf(stderr, "%p [%p]->%s(fn = %p)\n", this, obj_, __PRETTY_FUNCTION__, (void*)fn);
	if (obj_ == nullptr) {
	    // FIXME: throw exception
	    assert(false);
	}
	return (obj_->*fn)();
    }
    void call(void (O::*fn)()) {
	fprintf(stderr, "%p [%p]->%s(fn = %p)\n", this, obj_, __PRETTY_FUNCTION__, (void*)fn);
	if (obj_ == nullptr) {
	    // FIXME: throw exception
	    assert(false);
	}
	(obj_->*fn)();
    }
    template<typename T>
    T call(T (O::*fn)() const) const {
	fprintf(stderr, "%p [%p]->%s(fn = %p)\n", this, obj_, __PRETTY_FUNCTION__, (void*)fn);
	if (obj_ == nullptr) {
	    // FIXME: throw exception
	    assert(false);
	}
	return (obj_->*fn)();
    }
    void call(void (O::*fn)() const) const {
	fprintf(stderr, "%p [%p]->%s(fn = %p)\n", this, obj_, __PRETTY_FUNCTION__, (void*)fn);
	if (obj_ == nullptr) {
	    // FIXME: throw exception
	    assert(false);
	}
	(obj_->*fn)();
    }

    O * obj() {
	fprintf(stderr, "%p [%p]->%s()\n", this, obj_, __PRETTY_FUNCTION__);
	if (obj_ == nullptr) {
	    // FIXME: throw exception
	    assert(false);
	}
	return obj_;
    }
    const O * obj() const {
	fprintf(stderr, "%p [%p]->%s()\n", this, obj_, __PRETTY_FUNCTION__);
	if (obj_ == nullptr) {
	    // FIXME: throw exception
	    assert(false);
	}
	return obj_;
    }

    static value make(O *obj, size_t ref_count=0) {
	CAMLparam0();
	CAMLlocal1(res);
	fprintf(stderr, "Creating proxy for %p\n", obj);
	// does the object already have a proxy?
	res = obj->proxy();
	if (res == 0) {
	    // no proxy, create a new one
	    res = caml_alloc_custom(&caml_mrvn_QT5_Proxy_custom_ops, sizeof(Proxy), 1, sizeof(Proxy) + sizeof(O));
	    new(Data_custom_val(res))Proxy(obj);
	    obj->set_proxy(res);
	    if (ref_count > 0) obj->incr(ref_count);
	    fprintf(stderr, "  new proxy @ %lx\n", res);
	} else {
	    // return existing proxy
	    fprintf(stderr, "  old proxy @ %lx\n", res);
	}
	CAMLreturn(res);
    }
private:
    Proxy(O *obj) : obj_(obj) {
	fprintf(stderr, "%p [%p]->%s()\n", this, obj_, __PRETTY_FUNCTION__);
    }
    O *obj_;
};

#endif // #ifndef MRVN_QT5_PROXY_H
