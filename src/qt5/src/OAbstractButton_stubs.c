#include <QAbstractButton>

#include "OAbstractButton.h"
#include "Signal.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

OAbstractButton::OAbstractButton() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

OAbstractButton::~OAbstractButton() {
    fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
}

class OQAbstractButton : public OAbstractButton, public QAbstractButton {
public:
    virtual ~OQAbstractButton() {
	fprintf(stderr, "%p->%s\n", this, __PRETTY_FUNCTION__);
	preDestructor();
    }
};

/* abstract
extern "C" value caml_mrvn_QT5_OAbstractButton_make(void) {
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQAbstractButton *obj = new OQAbstractButton();
    assert(obj != nullptr);
    return value(static_cast<OClass *>(obj));
}
*/

Signal<QAbstractButton, bool> QAbstractButton_clicked(&QAbstractButton::clicked);

extern "C"
value caml_mrvn_QT5_QAbstractButton_clicked(void) {
    CAMLparam0();
    fprintf(stderr, "%s() = %p\n", __PRETTY_FUNCTION__, (void*)&QAbstractButton_clicked);
    CAMLreturn((value)&QAbstractButton_clicked);
}
