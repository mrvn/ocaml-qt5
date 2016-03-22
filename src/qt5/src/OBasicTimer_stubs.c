#include <QBasicTimer>
#include <QObject>

#include "OBasicTimer.h"

#include <stdio.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "OObject.h"

OBasicTimer::OBasicTimer() : object_(nullptr) {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OBasicTimer::~OBasicTimer() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
    removeObject();
}

void OBasicTimer::removeObject() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
    if (object_ != nullptr) {
        object_->decr();
        object_ = nullptr;
    }
}

void OBasicTimer::start(int msec, OObject *object) {
    fprintf(stderr, "%p [0x%lx]->%s(%d, %p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, msec, object);
    object->incr();
    removeObject();
    object_ = object;
    QObject *obj = dynamic_cast<QObject *>(object);
    assert((obj != nullptr) && "OObject not mixed with QObject");
    qStart(msec, obj);
}

void OBasicTimer::stop() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
    qStop();
    removeObject();
}

OQBasicTimer::OQBasicTimer() : OBasicTimer(), QBasicTimer() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, OBasicTimer::maybe_obj(), __PRETTY_FUNCTION__);
}

OQBasicTimer::~OQBasicTimer() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, OBasicTimer::maybe_obj(), __PRETTY_FUNCTION__);
}

void OQBasicTimer::qStart(int msec, QObject *object) {
    fprintf(stderr, "%p [0x%lx]->%s(%d, %p)\n", this, OBasicTimer::maybe_obj(), __PRETTY_FUNCTION__, msec, object);
    QBasicTimer::start(msec, object);
}

void OQBasicTimer::qStop() {
    fprintf(stderr, "%p [0x%lx]->%s\n", this, OBasicTimer::maybe_obj(), __PRETTY_FUNCTION__);
    QBasicTimer::stop();
}

extern "C" value caml_mrvn_QT5_OBasicTimer_start(OClass *obj, value ml_msec, OClass *object) {
    CAMLparam0();
    fprintf(stderr, "%s(%p, %d, %p)\n", __PRETTY_FUNCTION__, obj, Int_val(ml_msec), object);
    OBasicTimer *basicTimer = dynamic_cast<OBasicTimer *>(obj);
    assert((basicTimer != nullptr) && "not an OBasicTimer");
    OObject *oObject = dynamic_cast<OObject *>(object);
    assert((oObject != nullptr) && "not an OObject");
    basicTimer->start(Int_val(ml_msec), oObject);
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OBasicTimer_stop(OClass *obj) {
    CAMLparam0();
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    OBasicTimer *basicTimer = dynamic_cast<OBasicTimer *>(obj);
    assert((basicTimer != nullptr) && "not an OBasicTimer");
    basicTimer->stop();
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OBasicTimer_timerId(OClass *obj) {
    CAMLparam0();
    fprintf(stderr, "%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QBasicTimer *timer = dynamic_cast<QBasicTimer *>(obj);
    assert((timer != nullptr) && "OBasicTimer not mixed with QBasicTimer");
    int id = timer->timerId();
    fprintf(stderr, "%s(%p): id = %d\n", __PRETTY_FUNCTION__, obj, id);
    CAMLreturn(Val_int(id));
}

extern "C" value caml_mrvn_QT5_OBasicTimer_make() {
    CAMLparam0();
    fprintf(stderr, "%s()\n", __PRETTY_FUNCTION__);
    OQBasicTimer *obj = new OQBasicTimer();
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}
