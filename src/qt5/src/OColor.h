#ifdef MRVN_QT5_OCOLOR_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OCOLOR_H
#define MRVN_QT5_OCOLOR_H
#define MRVN_QT5_OCOLOR_H__INSIDE

#include <utility>

#include "OClass.h"

class QColor;

class OColor : public virtual OClass {
public:
    OColor();
    virtual ~OColor();
};

class OQColor : public OColor, public QColor {
public:
    OQColor(const char *name);
    OQColor(const QColor &color);
    virtual ~OQColor();
};

#undef MRVN_QT5_OCOLOR_H__INSIDE
#endif // #ifndef MRVN_QT5_OCOLOR_H
