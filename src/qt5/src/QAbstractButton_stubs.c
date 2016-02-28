#include <QAbstractButton>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include "Signal_stubs.h"

Signal<QAbstractButton, bool> QAbstractButton_clicked(&QAbstractButton::clicked);

extern "C"
value caml_mrvn_QT5_QAbstractButton_clicked(void) {
    CAMLparam0();
    CAMLreturn((value)&QAbstractButton_clicked);
}
