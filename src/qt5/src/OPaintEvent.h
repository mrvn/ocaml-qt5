#ifdef MRVN_QT5_OPAINTEVENT_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OPAINTEVENT_H
#define MRVN_QT5_OPAINTEVENT_H
#define MRVN_QT5_OPAINTEVENT_H__INSIDE

#include "OEvent.h"

class QPaintEvent;

class OPaintEvent : public OEvent {
public:
    OPaintEvent(QPaintEvent *event);
    virtual ~OPaintEvent();
    QPaintEvent * event() const;
};

#undef MRVN_QT5_OPAINTEVENT_H__INSIDE
#endif // #ifndef MRVN_QT5_OPAINTEVENT_H
