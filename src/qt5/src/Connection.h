#ifdef MRVN_QT5_CONNECTION_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_CONNECTION_H
#define MRVN_QT5_CONNECTION_H
#define MRVN_QT5_CONNECTION_H__INSIDE

#include <QMetaObject>
#include <caml/mlvalues.h>

class Connection : private QMetaObject::Connection {
public:
    ~Connection();
    void disconnect();
    static value make(const QMetaObject::Connection &con);
private:
    Connection(const QMetaObject::Connection &con);
};

#undef MRVN_QT5_CONNECTION_H__INSIDE
#endif // #ifndef MRVN_QT5_CONNECTION_H
