#ifndef MRVN_QT5_PROXY_STUBS_H
#define MRVN_QT5_PROXY_STUBS_H

#include <QObject>
#include <QVariant>
#include <caml/mlvalues.h>
#include <caml/custom.h>
#include <cassert>

extern char caml_mrvn_QT5_Proxy_identifier[];
extern struct custom_operations caml_mrvn_QT5_Proxy_custom_ops;

template<class Q>
class Proxy : public QObject {
public:
  Proxy(Q *obj, bool shared = false) : QObject(), obj_(obj), shared_(shared) {
    fprintf(stderr, "%p->%s(%p, %s)\n", this, __PRETTY_FUNCTION__, obj_, shared_ ? "true" : "false");
    obj_->setProperty(caml_mrvn_QT5_Proxy_identifier, QVariant((qlonglong)this));
    QObject::connect(obj_, &QObject::destroyed, this, &Proxy::obj_destroyed);
  }
  ~Proxy() {
    fprintf(stderr, "%p->%s()\n", this, __PRETTY_FUNCTION__);
    if (obj_ != nullptr) {
      fprintf(stderr, "  obj = %p\n", obj_);
      obj_->setProperty(caml_mrvn_QT5_Proxy_identifier, QVariant());
      if (!shared_) {
        fprintf(stderr, "  deleting\n");
        delete obj_;
      }
      obj_ = nullptr;
    }
  }
  template<typename T, typename A>
  T call(T (Q::*fn)(A arg), A arg) {
    if (obj_ == nullptr) {
      // FIXME: throw exception
      assert(false);
    }
    return (obj_->*fn)(arg);
  }
  template<typename A>
  void call(void (Q::*fn)(A arg), A arg) {
    if (obj_ == nullptr) {
      // FIXME: throw exception
      assert(false);
    }
    (obj_->*fn)(arg);
  }
  template<typename T, typename A>
  T call(T (Q::*fn)(A arg) const, A arg) const {
    if (obj_ == nullptr) {
      // FIXME: throw exception
      assert(false);
    }
    return (obj_->*fn)(arg);
  }
  template<typename A>
  void call(void (Q::*fn)(A arg) const, A arg) const {
    if (obj_ == nullptr) {
      // FIXME: throw exception
      assert(false);
    }
    (obj_->*fn)(arg);
  }
  template<typename T>
  T call(T (Q::*fn)()) {
    if (obj_ == nullptr) {
      // FIXME: throw exception
      assert(false);
    }
    fprintf(stderr, "%s: %p->(%p)\n", __PRETTY_FUNCTION__, obj_, (void*)fn);
    return (obj_->*fn)();
  }
  void call(void (Q::*fn)()) {
    if (obj_ == nullptr) {
      // FIXME: throw exception
      assert(false);
    }
    fprintf(stderr, "%s: %p->(%p)\n", __PRETTY_FUNCTION__, obj_, (void*)fn);
    (obj_->*fn)();
  }
  template<typename T>
  T call(T (Q::*fn)() const) const {
    if (obj_ == nullptr) {
      // FIXME: throw exception
      assert(false);
    }
    fprintf(stderr, "%s: %p->(%p)\n", __PRETTY_FUNCTION__, obj_, (void*)fn);
    return (obj_->*fn)();
  }
  void call(void (Q::*fn)() const) const {
    if (obj_ == nullptr) {
      // FIXME: throw exception
      assert(false);
    }
    fprintf(stderr, "%s: %p->(%p)\n", __PRETTY_FUNCTION__, obj_, (void*)fn);
    (obj_->*fn)();
  }
  Q * obj() {
    if (obj_ == nullptr) {
      // FIXME: throw exception
      assert(false);
    }
    return obj_;
  }
  const Q * obj() const {
    if (obj_ == nullptr) {
      // FIXME: throw exception
      assert(false);
    }
    return obj_;
  }
  static value create(Q *obj, bool shared = false) {
    fprintf(stderr, "Creating proxy for %p\n", obj);
    // does the object already have a proxy?
    QVariant v = obj->property(caml_mrvn_QT5_Proxy_identifier);
    if (v.isNull()) {
      // no proxy, create a new one
      value res = caml_alloc_custom(&caml_mrvn_QT5_Proxy_custom_ops, sizeof(Proxy), 1, 1000);
      new(Data_custom_val(res))Proxy(obj, shared);
      fprintf(stderr, "  new proxy @ %lu\n", res);
      return res;
    } else {
      // return existing proxy
      value res = v.toLongLong();
      fprintf(stderr, "  old proxy @ %lu\n", res);
      return res;
    }
  }
private:
  void obj_destroyed(QObject *obj = nullptr) {
    fprintf(stderr, "%p->%s(%p)\n", this, __PRETTY_FUNCTION__, obj);
    assert(obj == obj_);
    obj_ = nullptr;
  }

  Q *obj_;
  bool shared_;
};

#endif // #ifndef MRVN_QT5_PROXY_STUBS_H
