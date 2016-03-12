#ifdef MRVN_QT5_OAPPLICATION_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OAPPLICATION_H
#define MRVN_QT5_OAPPLICATION_H
#define MRVN_QT5_OAPPLICATION_H__INSIDE

#include "OObject.h"

class OApplication : public OObject {
public:
    OApplication();
    virtual ~OApplication();
};

#undef MRVN_QT5_OAPPLICATION_H__INSIDE
#endif // #ifndef MRVN_QT5_OAPPLICATION_H
