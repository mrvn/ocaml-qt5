#include "StringArray.h"

#include <cassert>
#include <cstring>
#include <caml/memory.h>

#include "debug.h"

StringArray::StringArray(value ml_args) {
    DEBUG("%p->%s(0x%lx)\n", this, __PRETTY_FUNCTION__, ml_args);
    CAMLparam1(ml_args);
    argc_ = caml_array_length(ml_args);
    DEBUG("%p->%s: argc_ = %d\n", this, __PRETTY_FUNCTION__, argc_);
    argv_ = new char*[argc_];
    DEBUG("%p->%s: argv_ = %p\n", this, __PRETTY_FUNCTION__, argv_);
    assert(argv_ != nullptr);
    for (int i = 0; i < argc_; ++i) {
	argv_[i] = strdup(String_val(Field(ml_args, i)));
	assert(argv_[i] != nullptr);
	DEBUG("%p->%s: argv_[%d] = %p '%s'\n", this, __PRETTY_FUNCTION__, i, argv_[i], argv_[i]);
    }
    CAMLreturn0;
}

StringArray::~StringArray() {
    DEBUG("%p->%s\n", this, __PRETTY_FUNCTION__);
    for (int i = 0; i < argc_; ++i) {
	free(argv_[i]);
    }
    delete[] argv_;
}
