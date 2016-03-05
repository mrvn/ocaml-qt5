#include <QAbstractButton>

#include "OAbstractButton.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>

#include "Signal.h"

Signal<QAbstractButton, bool> QAbstractButton_clicked(&QAbstractButton::clicked);

extern "C"
value caml_mrvn_QT5_QAbstractButton_clicked(void) {
    CAMLparam0();
    fprintf(stderr, "%s() = %p\n", __PRETTY_FUNCTION__, (void*)&QAbstractButton_clicked);
    CAMLreturn((value)&QAbstractButton_clicked);
}
