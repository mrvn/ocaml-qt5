#include <QApplication>

#include "OApplication.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OApplication::OApplication() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OApplication::~OApplication() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

class StringArray {
public:
    StringArray(value ml_args) {
	fprintf(stderr, "%p->%s(0x%lx)\n", this, __PRETTY_FUNCTION__, ml_args);
	CAMLparam1(ml_args);
	argc_ = caml_array_length(ml_args);
	fprintf(stderr, "%p->%s: argc_ = %d\n", this, __PRETTY_FUNCTION__, argc_);
	argv_ = new char*[argc_];
	fprintf(stderr, "%p->%s: argv_ = %p\n", this, __PRETTY_FUNCTION__, argv_);
	assert(argv_ != nullptr);
	for (int i = 0; i < argc_; ++i) {
	    argv_[i] = strdup(String_val(Field(ml_args, i)));
	    assert(argv_[i] != nullptr);
	    fprintf(stderr, "%p->%s: argv_[%d] = %p '%s'\n", this, __PRETTY_FUNCTION__, i, argv_[i], argv_[i]);
	}
	CAMLreturn0;
    }
    ~StringArray() {
	fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
	for (int i = 0; i < argc_; ++i) {
	    free(argv_[i]);
	}
	delete[] argv_;
    }
protected:
    int argc_;
    char **argv_;
};

class OQApplication : public OApplication, private StringArray, public QApplication {
public:
    OQApplication(value ml_args) : OApplication(), StringArray(ml_args), QApplication(argc_, argv_) {
	fprintf(stderr, "%p [0x%lx]->%s(0x%lx)\n", this, maybe_obj(), __PRETTY_FUNCTION__, ml_args);
    }
    virtual ~OQApplication() {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
	preDestructor();
    }
};

extern "C" value caml_mrvn_QT5_OApplication_exec() {
  CAMLparam0();
  fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
  CAMLreturn(Val_int(QApplication::exec()));
}

extern "C" value caml_mrvn_QT5_OApplication_make(value ml_args) {
  CAMLparam1(ml_args);
  fprintf(stderr, "%s(0x%lx)\n", __PRETTY_FUNCTION__, ml_args);
  OQApplication *app = new OQApplication(ml_args);
  assert(app != nullptr);
  fprintf(stderr, "%s = %p\n", __PRETTY_FUNCTION__, app);
  CAMLreturn(value(static_cast<OClass *>(app)));
}
