#ifndef MRVN_QT5_CONNECTION_STUBS_H
#define MRVN_QT5_CONNECTION_STUBS_H

#include <QMetaObject>
#include <caml/mlvalues.h>

value make(QMetaObject::Connection con, value ml_fn);

#endif // #ifndef MRVN_QT5_CONNECTION_STUBS_H
