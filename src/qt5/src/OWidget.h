#ifdef MRVN_QT5_OWIDGET_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OWIDGET_H
#define MRVN_QT5_OWIDGET_H
#define MRVN_QT5_OWIDGET_H__INSIDE

#include <QSize>

#include "OObject.h"
#include "OPaintDevice.h"

class OLayout;
class QPaintEvent;
class QEvent;
class QKeyEvent;

class OWidget : public virtual OObject, public virtual OPaintDevice {
public:
    OWidget();
    virtual ~OWidget();
    void setLayout(OLayout *layout);
    void paintEvent(QPaintEvent *event);
    virtual void qPaintEvent(QPaintEvent *event) = 0;
    virtual QSize sizeHint() const;
    virtual QSize qSizeHint() const = 0;
    virtual QSize minimumSizeHint() const;
    virtual QSize qMinimumSizeHint() const = 0;
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void qKeyPressEvent(QKeyEvent * event) = 0;
};

template<class O, class Q>
class TWidget : public TObject<O, Q> {
public:
    template<typename ... A>
    TWidget(A && ... a) : TObject<O, Q>(std::forward<A>(a) ...) {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TWidget() {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual void paintEvent(QPaintEvent *event) final override {
	//fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
	O::paintEvent(event);
    };
    virtual void qPaintEvent(QPaintEvent *event) {
	// fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
        Q::paintEvent(event);
    }
    virtual QSize sizeHint() const final override {
	return O::sizeHint();
    }
    virtual QSize qSizeHint() const {
	return Q::sizeHint();
    }
    virtual QSize minimumSizeHint() const final override {
	return O::minimumSizeHint();
    }
    virtual QSize qMinimumSizeHint() const {
	return Q::minimumSizeHint();
    }
    virtual void keyPressEvent(QKeyEvent * event) final override {
	O::keyPressEvent(event);
    }
    virtual void qKeyPressEvent(QKeyEvent * event) {
	Q::keyPressEvent(event);
    }
};

using OQWidget = TWidget<OWidget, QWidget>;

#undef MRVN_QT5_OWIDGET_H__INSIDE
#endif // #ifndef MRVN_QT5_OWIDGET_H
