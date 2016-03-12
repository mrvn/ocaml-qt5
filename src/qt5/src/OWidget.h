#ifdef MRVN_QT5_OWIDGET_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OWIDGET_H
#define MRVN_QT5_OWIDGET_H
#define MRVN_QT5_OWIDGET_H__INSIDE

#include "OObject.h"

class OWidget : public OObject {
public:
    OWidget();
    virtual ~OWidget();
    /*
    virtual void keyPressEvent(QKeyEvent * event) {
	fprintf(stderr, "%p <0x%lx>->%s(%p)\n", this, OWidget<Q>::proxy(), __PRETTY_FUNCTION__, event);
	Q::keyPressEvent(event);
    }
    */
};

class OQWidget : public OWidget, public QWidget {
public:
    virtual ~OQWidget();
};

#undef MRVN_QT5_OWIDGET_H__INSIDE
#endif // #ifndef MRVN_QT5_OWIDGET_H
