#ifdef MRVN_QT5_OTIMEREVENT_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OTIMEREVENT_H
#define MRVN_QT5_OTIMEREVENT_H
#define MRVN_QT5_OTIMEREVENT_H__INSIDE

#include "OEvent.h"

class QTimerEvent;

class OTimerEvent : public OEvent {
public:
    OTimerEvent(QTimerEvent *event);
    virtual ~OTimerEvent();
    QTimerEvent * event() const;
};

#undef MRVN_QT5_OTIMEREVENT_H__INSIDE
#endif // #ifndef MRVN_QT5_OTIMEREVENT_H
