#ifdef MRVN_QT5_DEBUG_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_DEBUG_H
#define MRVN_QT5_DEBUG_H
#define MRVN_QT5_DEBUG_H__INSIDE

#include <utility>

#ifdef DEBUG
#include <stdio.h>

template<typename ... A>
void DEBUG(const char *format, A && ... a) {
    fprintf(stderr, format, std::forward<A>(a) ...);
}
#else
template<typename ... A>
void DEBUG(const char *, A && ...) { }
#endif

#undef MRVN_QT5_DEBUG_H__INSIDE
#endif // #ifndef MRVN_QT5_DEBUG_H
