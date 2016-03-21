#ifdef MRVN_QT5_OCLASS_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OCLASS_H
#define MRVN_QT5_OCLASS_H
#define MRVN_QT5_OCLASS_H__INSIDE

#include <caml/mlvalues.h>

class OClass {
public:
    OClass(size_t ref_count=0);
    virtual ~OClass();
    void register_obj(value ml_obj);
    void unregister_obj();
    void incr(size_t amount=1);
    void decr(size_t amount=1);
protected:
    value maybe_obj();
    value maybe_obj() const;
    value get_obj();
    value get_obj() const;
private:
    value ml_obj_;
    size_t ref_count_;
};

#undef MRVN_QT5_OCLASS_H__INSIDE
#endif // #ifndef MRVN_QT5_OCLASS_H
