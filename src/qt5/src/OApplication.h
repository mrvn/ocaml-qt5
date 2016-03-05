#ifndef MRVN_QT5_OAPPLICATION_H
#define MRVN_QT5_OAPPLICATION_H

#include <stdio.h>
#include <cassert>
#include <caml/memory.h>

#include "OObject.h"

class StringArray {
public:
    StringArray(value ml_args) {
	fprintf(stderr, "%p->%s()\n", this, __PRETTY_FUNCTION__);
	CAMLparam1(ml_args);
	argc_ = caml_array_length(ml_args);
	fprintf(stderr, "%p->%s(): argc_ = %d\n", this, __PRETTY_FUNCTION__, argc_);
	argv_ = new char*[argc_];
	fprintf(stderr, "%p->%s(): argv_ = %p\n", this, __PRETTY_FUNCTION__, argv_);
	assert(argv_ != nullptr);
	for (int i = 0; i < argc_; ++i) {
	    argv_[i] = strdup(String_val(Field(ml_args, i)));
	    assert(argv_[i] != nullptr);
	    fprintf(stderr, "%p->%s(): argv_[%d] = %p '%s'\n", this, __PRETTY_FUNCTION__, i, argv_[i], argv_[i]);
	}
	CAMLreturn0;
    }
    ~StringArray() {
	fprintf(stderr, "%p->%s()\n", this, __PRETTY_FUNCTION__);
	for (int i = 0; i < argc_; ++i) {
	    free(argv_[i]);
	}
	delete argv_;
    }
protected:
    int argc_;
    char **argv_;
};

template<class Q>
class OApplication : private StringArray, public OObject<Q> {
public:
    template<typename ... A>
    OApplication(value ml_args, A && ... a) : StringArray(ml_args), OObject<Q>(argc_, argv_, a...) {
	fprintf(stderr, "%p <0x%lx>->%s(): argc_ @ %p, argv_ @ %p, argv_[0] = %p '%s'\n", this, OObject<Q>::proxy(), __PRETTY_FUNCTION__, &argc_, argv_, argv_[0], argv_[0]);
    }
    virtual ~OApplication() {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, OObject<Q>::proxy(), __PRETTY_FUNCTION__);
    }
private:
};

#endif // #ifndef MRVN_QT5_OAPPLICATION_H
