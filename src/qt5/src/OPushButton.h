#ifndef MRVN_QT5_OPUSHBUTTON_H
#define MRVN_QT5_OPUSHBUTTON_H

#include <QString>
#include <stdio.h>

#include "OAbstractButton.h"

template<class O>
class OPushButton : public OAbstractButton<O> {
public:
    template<typename ... A>
    OPushButton(QString text, A && ... a) : OAbstractButton<O>(text, a...) {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, OAbstractButton<O>::proxy(), __PRETTY_FUNCTION__);
    }
    virtual ~OPushButton() {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, OAbstractButton<O>::proxy(), __PRETTY_FUNCTION__);
    }
private:
};

#endif // #ifndef MRVN_QT5_OPUSHBUTTON_H
