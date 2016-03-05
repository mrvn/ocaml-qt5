#ifndef MRVN_QT5_OOBJECT_H
#define MRVN_QT5_OOBJECT_H

#include <QObject>
#include <stdio.h>

#include "OClass.h"

template<class Q>
class OObject : public Q, public OClass {
public:
    template<typename ... A>
    OObject(A && ... a) : Q(a...) {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, proxy(), __PRETTY_FUNCTION__);
    }
    virtual ~OObject() {
	fprintf(stderr, "%p <0x%lx>->%s()\n", this, proxy(), __PRETTY_FUNCTION__);
    }
private:
};

#endif // #ifndef MRVN_QT5_OOBJECT_H
