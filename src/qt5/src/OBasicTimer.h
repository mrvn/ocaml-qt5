#ifdef MRVN_QT5_OBASICTIMER_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OBASICTIMER_H
#define MRVN_QT5_OBASICTIMER_H
#define MRVN_QT5_OBASICTIMER_H__INSIDE

#include "OClass.h"

class QBasicTimer;
class OObject;
class QObject;

class OBasicTimer : public virtual OClass {
public:
    OBasicTimer();
    virtual ~OBasicTimer();
    void start(int msec, OObject *object);
    virtual void qStart(int msec, QObject *object) = 0;
    void stop();
    virtual void qStop() = 0;
private:
    void removeObject();
    OObject *object_;
};

class OQBasicTimer : public OBasicTimer, public QBasicTimer {
public:
    OQBasicTimer();
    virtual ~OQBasicTimer();
    virtual void qStart(int msec, QObject *object);
    virtual void qStop();
};

#undef MRVN_QT5_OBASICTIMER_H__INSIDE
#endif // #ifndef MRVN_QT5_OBASICTIMER_H
