#ifndef MRVN_QT5_CONNECTION_H
#define MRVN_QT5_CONNECTION_H

#include <QMetaObject>
#include <caml/mlvalues.h>

#include "OClass.h"

class Connection : private QMetaObject::Connection {
public:
    ~Connection();
    void disconnect();
    static value make(const QMetaObject::Connection &con);
private:
    Connection(const QMetaObject::Connection &con);
};

//value make(QMetaObject::Connection con, value ml_fn);

#endif // #ifndef MRVN_QT5_CONNECTION_H
