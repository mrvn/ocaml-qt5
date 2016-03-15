#ifdef MRVN_QT5_OEVENT_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OEVENT_H
#define MRVN_QT5_OEVENT_H
#define MRVN_QT5_OEVENT_H__INSIDE

#include "OClass.h"

class QEvent;

class OEvent : public OClass {
public:
    OEvent(QEvent *event);
    virtual ~OEvent();
    void removeEvent();
    QEvent * event() const;
private:
    QEvent *event_;
};

#undef MRVN_QT5_OEVENT_H__INSIDE
#endif // #ifndef MRVN_QT5_OEVENT_H
