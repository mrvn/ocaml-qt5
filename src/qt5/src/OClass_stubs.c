#include "OClass.h"

#include <stdio.h>
#include <caml/memory.h>

#include "Proxy.h"

OClass::OClass() : proxy_(0), ref_count_(0) {
    fprintf(stderr, "%p <0x%lx>->%s()\n", this, proxy_, __PRETTY_FUNCTION__);
}

OClass::~OClass() {
    fprintf(stderr, "%p <0x%lx>->%s()\n", this, proxy_, __PRETTY_FUNCTION__);
    assert(ref_count_ == 0);
    assert(proxy_ != 0);
    Proxy<OClass> *proxy = (Proxy<OClass> *)Data_custom_val(proxy_);
    proxy->invalidate();
    proxy_ = 0;
    fprintf(stderr, "%p <0x%lx>->%s() done\n", this, proxy_, __PRETTY_FUNCTION__);
}

void OClass::set_proxy(value proxy) {
    fprintf(stderr, "%p <0x%lx>->%s(0x%lx)\n", this, proxy_, __PRETTY_FUNCTION__, proxy);
    assert(proxy_ == 0);
    proxy_ = proxy;
    fprintf(stderr, "%p <0x%lx>->%s(0x%lx) done\n", this, proxy_, __PRETTY_FUNCTION__, proxy);
}

size_t OClass::ref_count() const {
    //fprintf(stderr, "%p <0x%lx>->%s() = %zu\n", this, proxy_, __PRETTY_FUNCTION__, ref_count_);
    return ref_count_;
}

void OClass::incr(size_t amount) {
    fprintf(stderr, "%p <0x%lx>->%s(%zu)", this, proxy_, __PRETTY_FUNCTION__, amount);
    if (ref_count_ == 0) {
	fprintf(stderr, " ### registering root ###");
	// caml_register_generational_global_root(&proxy_);
	caml_register_generational_global_root(&proxy_);
    }
    ref_count_ += amount;
    fprintf(stderr, " = %zu\n", ref_count_);
}

void OClass::decr(size_t amount) {
    fprintf(stderr, "%p <0x%lx>->%s(%zu)", this, proxy_, __PRETTY_FUNCTION__, amount);
    assert (ref_count_ >= amount);
    ref_count_ -= amount;
    if (ref_count_ == 0) {
	fprintf(stderr, " ### removing root ###");
	// caml_remove_generational_global_root(&proxy_);
	caml_remove_generational_global_root(&proxy_);
    }
    fprintf(stderr, " = %zu\n", ref_count_);
}

value OClass::proxy() const {
    //fprintf(stderr, "%p [0x%lx]->%s()\n", this, proxy_, __PRETTY_FUNCTION__);
    return proxy_;
}
