#ifndef MRVN_QT5_OEVENT_H
#define MRVN_QT5_OEVENT_H

#include <QEvent>
#include <stdio.h>

#include "OClass.h"

class OEvent : public OClass {
public:
    OEvent(QEvent *event) : event_(event) {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, proxy(), __PRETTY_FUNCTION__);
    }
    virtual ~OEvent() {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, proxy(), __PRETTY_FUNCTION__);
    }
private:
    QEvent *event_;
};

#endif // #ifndef MRVN_QT5_OEVENT_H
