#ifdef MRVN_QT5_OPALETTE_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OPALETTE_H
#define MRVN_QT5_OPALETTE_H
#define MRVN_QT5_OPALETTE_H__INSIDE

#include <utility>

#include "OClass.h"

class QPalette;

class OPalette : public virtual OClass {
public:
    OPalette();
    virtual ~OPalette();
};

class OQPalette : public OPalette, public QPalette {
public:
    OQPalette();
    OQPalette(const QPalette &palette);
    virtual ~OQPalette();
};

extern "C" value caml_mrvn_QT5_OPalette_alloc(const QPalette &palette);

#undef MRVN_QT5_OPALETTE_H__INSIDE
#endif // #ifndef MRVN_QT5_OPALETTE_H
