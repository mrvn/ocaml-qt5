#include <QBasicTimer>
#include <QObject>

#include "OBasicTimer.h"

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <cassert>

#include "debug.h"
#include "OObject.h"

OBasicTimer::OBasicTimer() : object_(nullptr) {
    DEBUG("%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
}

OBasicTimer::~OBasicTimer() {
    DEBUG("%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
    removeObject();
}

void OBasicTimer::removeObject() {
    DEBUG("%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
    if (object_ != nullptr) {
        object_->decr();
        object_ = nullptr;
    }
}

void OBasicTimer::start(int msec, OObject *object) {
    DEBUG("%p [0x%lx]->%s(%d, %p)\n", this, maybe_obj(), __PRETTY_FUNCTION__, msec, object);
    object->incr();
    removeObject();
    object_ = object;
    QObject *obj = dynamic_cast<QObject *>(object);
    assert((obj != nullptr) && "OObject not mixed with QObject");
    qStart(msec, obj);
}

void OBasicTimer::stop() {
    DEBUG("%p [0x%lx]->%s\n", this, maybe_obj(), __PRETTY_FUNCTION__);
    qStop();
    removeObject();
}

OQBasicTimer::OQBasicTimer() : OBasicTimer(), QBasicTimer() {
    DEBUG("%p [0x%lx]->%s\n", this, OBasicTimer::maybe_obj(), __PRETTY_FUNCTION__);
}

OQBasicTimer::~OQBasicTimer() {
    DEBUG("%p [0x%lx]->%s\n", this, OBasicTimer::maybe_obj(), __PRETTY_FUNCTION__);
}

void OQBasicTimer::qStart(int msec, QObject *object) {
    DEBUG("%p [0x%lx]->%s(%d, %p)\n", this, OBasicTimer::maybe_obj(), __PRETTY_FUNCTION__, msec, object);
    QBasicTimer::start(msec, object);
}

void OQBasicTimer::qStop() {
    DEBUG("%p [0x%lx]->%s\n", this, OBasicTimer::maybe_obj(), __PRETTY_FUNCTION__);
    QBasicTimer::stop();
}

extern "C" value caml_mrvn_QT5_OBasicTimer_start(OClass *obj, value ml_msec, OClass *object) {
    CAMLparam0();
    DEBUG("%s(%p, %d, %p)\n", __PRETTY_FUNCTION__, obj, Int_val(ml_msec), object);
    OBasicTimer *basicTimer = dynamic_cast<OBasicTimer *>(obj);
    assert((basicTimer != nullptr) && "not an OBasicTimer");
    OObject *oObject = dynamic_cast<OObject *>(object);
    assert((oObject != nullptr) && "not an OObject");
    basicTimer->start(Int_val(ml_msec), oObject);
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OBasicTimer_stop(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    OBasicTimer *basicTimer = dynamic_cast<OBasicTimer *>(obj);
    assert((basicTimer != nullptr) && "not an OBasicTimer");
    basicTimer->stop();
    CAMLreturn(Val_unit);
}

extern "C" value caml_mrvn_QT5_OBasicTimer_timerId(OClass *obj) {
    CAMLparam0();
    DEBUG("%s(%p)\n", __PRETTY_FUNCTION__, obj);
    QBasicTimer *timer = dynamic_cast<QBasicTimer *>(obj);
    assert((timer != nullptr) && "OBasicTimer not mixed with QBasicTimer");
    int id = timer->timerId();
    DEBUG("%s(%p): id = %d\n", __PRETTY_FUNCTION__, obj, id);
    CAMLreturn(Val_int(id));
}

extern "C" value caml_mrvn_QT5_OBasicTimer_make() {
    CAMLparam0();
    DEBUG("%s()\n", __PRETTY_FUNCTION__);
    OQBasicTimer *obj = new OQBasicTimer();
    assert(obj != nullptr);
    CAMLreturn(value(static_cast<OClass *>(obj)));
}
