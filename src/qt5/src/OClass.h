#ifndef MRVN_QT5_OCLASS_H
#define MRVN_QT5_OCLASS_H

#include <caml/mlvalues.h>

class OClass {
public:
    OClass();
    virtual ~OClass();
    virtual void set_proxy(value proxy);
    virtual size_t ref_count() const;
    virtual void incr(size_t amount=1);
    virtual void decr(size_t amount=1);
    virtual value proxy() const;
private:
    value proxy_;
    size_t ref_count_;
};

#endif // #ifndef MRVN_QT5_OCLASS_H
