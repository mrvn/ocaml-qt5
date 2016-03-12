#include "OClass.h"

#include <stdio.h>
#include <cassert>
#include <caml/memory.h>
#include <caml/callback.h>
#include "caml_weak.h"

OClass::OClass(size_t ref_count) : ml_obj_(0), ref_count_(ref_count) {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OClass::~OClass() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
    assert((ml_obj_ == 0) && "Qt5 object destroyed while alive in ocaml");
    if (ref_count_ != 0) {
	// Qt destroyed us, must be the last reference
	assert((ref_count_ == 1) && "Qt5 object destroyed while still in use by Qt5");
	ref_count_ = 0;
	/*
	if (ml_obj_ != 0) {
	    // ocaml object still attached, this should not happen
	    value obj = get_obj();
	    fprintf(stderr, "%p->%s: obj = 0x%lx\n", this, __PRETTY_FUNCTION__, obj);
	    value fn = caml_get_public_method(obj, caml_hash_variant("invalidate"));
	    fprintf(stderr, "%p->%s: fn = 0x%lx\n", this, __PRETTY_FUNCTION__, fn);
	    assert((fn != 0) && "ocaml object for this has no invalidate method");
	    caml_callback(fn, obj);
	}
	*/
    }
}

void OClass::register_obj(value ml_obj) {
    fprintf(stderr, "%p->%s(0x%lx)\n", this, __PRETTY_FUNCTION__, ml_obj);
    assert((ml_obj_ == 0) && "registered twice");
    ml_obj_ = ml_obj;
    caml_register_generational_global_root(&ml_obj_);
    incr();
}

void OClass::unregister_obj() {
    // fprintf(stderr, "%p [0x%lx]->%s\n", this, get_obj(), __PRETTY_FUNCTION__);
    // Weak.t is already None
    fprintf(stderr, "%p [...]->%s\n", this, __PRETTY_FUNCTION__);
    assert((ml_obj_ != 0) && "not registered");
    caml_remove_generational_global_root(&ml_obj_);
    ml_obj_ = 0;
    decr();
}

void OClass::incr(size_t amount) {
    fprintf(stderr, "%p [0x%lx]->%s(%zu)\n", this, get_obj(), __PRETTY_FUNCTION__, amount);
    ++ref_count_;
    //fprintf(stderr, "  = %zu\n", ref_count_);
}

void OClass::decr(size_t amount) {
    fprintf(stderr, "%p [...]->%s(%zu)\n", this, __PRETTY_FUNCTION__, amount);
    --ref_count_;
    //fprintf(stderr, "  = %zu\n", ref_count_);
    if (ref_count_ == 0) {
	//fprintf(stderr, "  deleting %p\n", this);
	assert((ml_obj_ == 0) && "last decr() must come from/after unregister_obj()");
	delete this;
    }
    //fprintf(stderr, "  done\n");
}

value OClass::maybe_obj() {
    CAMLparam0();
    CAMLlocal2(opt, res);
    // fprintf(stderr, "%p [weak=0x%lx]->%s()\n", this, ml_obj_, __PRETTY_FUNCTION__);
    res = 0;
    if (ml_obj_ != 0) {
	opt = caml_weak_get(ml_obj_, 0);
	// fprintf(stderr, "%p [weak=0x%lx]->%s(): opt = 0x%lx\n", this, ml_obj_, __PRETTY_FUNCTION__, opt);
	if (Is_block(opt)) { // Some x
	    res = Field(opt, 0);
	    // fprintf(stderr, "%p [weak=0x%lx]->%s(): res = 0x%lx\n", this, ml_obj_, __PRETTY_FUNCTION__, res);
	    if (res != 0) {
		// fprintf(stderr, "%p [weak=0x%lx]->%s(): tag = %u\n", this, ml_obj_, __PRETTY_FUNCTION__, Tag_val(res));
		assert((Tag_val(res) == Object_tag) && "this is not attached to an ocaml object");
	    }
	}
    }
    // fprintf(stderr, "%p [0x%lx]->%s()\n", this, res, __PRETTY_FUNCTION__);
    CAMLreturn(res);
}

value OClass::get_obj() {
    CAMLparam0();
    CAMLlocal1(res);
    // fprintf(stderr, "%p [weak=0x%lx]->%s()\n", this, ml_obj_, __PRETTY_FUNCTION__);
    res = maybe_obj();
    // fprintf(stderr, "%p [0x%lx]->%s()\n", this, res, __PRETTY_FUNCTION__);
    assert((res != 0) && "failed to find object for this");
    CAMLreturn(res);
}

//external make : unit -> 'a t = "caml_mrvn_Qt5_OClass_make"
extern "C" value caml_mrvn_Qt5_OClass_make(void) {
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OClass *obj = new OClass();
    assert((obj != nullptr) && "FIXME: allocation failure");
    return value(obj);
}

//external register : 'a t -> 'a -> unit = "caml_mrvn_Qt5_OClass_register_obj"
extern "C" void caml_mrvn_Qt5_OClass_register_obj(OClass *obj, value ml_obj) {
    fprintf(stderr, "%s(%p, 0x%lx)\n", __PRETTY_FUNCTION__, obj, ml_obj);
    obj->register_obj(ml_obj);
}

//external unregister : 'a t -> unit = "caml_mrvn_Qt5_OClass_unregister_obj"
extern "C" void caml_mrvn_Qt5_OClass_unregister_obj(OClass *obj) {
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    obj->unregister_obj();
}
