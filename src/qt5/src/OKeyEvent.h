#ifdef MRVN_QT5_OKEYEVENT_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OKEYEVENT_H
#define MRVN_QT5_OKEYEVENT_H
#define MRVN_QT5_OKEYEVENT_H__INSIDE

#include "OEvent.h"

class QKeyEvent;

class OKeyEvent : public OEvent {
public:
    OKeyEvent(QKeyEvent *event);
    virtual ~OKeyEvent();
    QKeyEvent * event() const;
};

#undef MRVN_QT5_OKEYEVENT_H__INSIDE
#endif // #ifndef MRVN_QT5_OKEYEVENT_H
