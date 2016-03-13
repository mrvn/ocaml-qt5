#ifdef MRVN_QT5_STRINGARRAY_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_STRINGARRAY_H
#define MRVN_QT5_STRINGARRAY_H
#define MRVN_QT5_STRINGARRAY_H__INSIDE

#include <caml/mlvalues.h>

class StringArray {
public:
    StringArray(value ml_args);
    ~StringArray();
protected:
    int argc_;
    char **argv_;
};

#undef MRVN_QT5_STRINGARRAY_H__INSIDE
#endif // #ifndef MRVN_QT5_STRINGARRAY_H
