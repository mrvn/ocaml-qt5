#ifndef MRVN_QT5_SIGNAL_STUBS_H
#define MRVN_QT5_SIGNAL_STUBS_H

#include <QMetaObject>
#include <QObject>
#include <caml/mlvalues.h>
#include <caml/custom.h>
#include <cassert>
#include <stdio.h>

extern char caml_mrvn_QT5_Signal_identifier[];
extern struct custom_operations caml_mrvn_QT5_Signal_custom_ops;

class SignalBase {
public:
  SignalBase() { };
  virtual ~SignalBase() { };
  virtual QMetaObject::Connection connect(void *obj, value ml_fn) = 0;
};
  
template<class Q, typename A>
class Signal : public SignalBase {
public:
  Signal(void (Q::*fn)(A)) : fn_(fn) { }
  QMetaObject::Connection connect(void *obj, value ml_fn) {
    fprintf(stderr, "%s\n", __PRETTY_FUNCTION__);
    return QObject::connect((Q*)obj, fn_, [obj](A) { fprintf(stderr, "triggered\n");});
  }
private:
  void (Q::*fn_)(A);
};

#endif // #ifndef MRVN_QT5_SIGNAL_STUBS_H
