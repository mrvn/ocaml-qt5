#ifdef MRVN_QT5_OLABEL_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OLABEL_H
#define MRVN_QT5_OLABEL_H
#define MRVN_QT5_OLABEL_H__INSIDE

#include "OFrame.h"

class OLabel : public OFrame {
public:
    OLabel();
    virtual ~OLabel();
};

template<class O, class Q>
class TLabel : public TFrame<O, Q> {
public:
    template<typename ... A>
    TLabel(A && ... a) : TFrame<O, Q>(std::forward<A>(a) ...) {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    template<typename ... A>
    TLabel(QString text, A && ... a) : TFrame<O, Q>(text, std::forward<A>(a) ...) {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
    virtual ~TLabel() {
	fprintf(stderr, "%p [0x%lx]->%s\n", this, O::maybe_obj(), __PRETTY_FUNCTION__);
    }
};

using OQLabel = TLabel<OLabel, QLabel>;

#undef MRVN_QT5_OLABEL_H__INSIDE
#endif // #ifndef MRVN_QT5_OLABEL_H
