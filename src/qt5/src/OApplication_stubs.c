#include <QApplication>

#include "OApplication.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OApplication::OApplication() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OApplication::~OApplication() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

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

class OQApplication : private StringArray, public OApplication, public QApplication {
public:
OQApplication(value ml_args) : StringArray(ml_args), OApplication(), QApplication(argc_, argv_) {
	fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
    }
    virtual ~OQApplication() {
	fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
	preDestructor(this);
    }
};

extern "C" value caml_mrvn_QT5_OApplication_exec() {
  CAMLparam0();
  fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
  CAMLreturn(Val_int(QApplication::exec()));
}

extern "C" value caml_mrvn_QT5_OApplication_make(value ml_args) {
  CAMLparam1(ml_args);
  fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
  OQApplication *app = new OQApplication(ml_args);
  assert(app != nullptr);
  fprintf(stderr, "%s() = %p\n", __PRETTY_FUNCTION__, app);
  CAMLreturn(value(app));
}
