#ifdef MRVN_CAML_WEAK__INSIDE
#error header loop
#endif

#ifndef MRVN_CAML_WEAK
#define MRVN_CAML_WEAK
#define MRVN_CAML_WEAK__INSIDE

#include <caml/mlvalues.h>

extern "C" value caml_weak_get (value ar, value n);
// ar : weak array
// n = index
// returns an option of the read value

extern "C" value caml_weak_set (value ar, value n, value el);
// ar : weak array
// n = index
// el = option containing the new value (as for Weak.set).

#undef MRVN_CAML_WEAK__INSIDE
#endif // #ifndef MRVN_CAML_WEAK
