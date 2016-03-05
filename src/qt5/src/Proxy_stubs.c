#include "Proxy.h"

#include <stdio.h>

#include "OClass.h"
#include "OObject.h"
#include <QObject>

char caml_mrvn_QT5_Proxy_identifier[] = "mrvn.caml.QT5.Proxy";

static void proxy_finalize(value v) {
    Proxy<OClass> *proxy = (Proxy<OClass> *)Data_custom_val(v);
    //Proxy<OObject<QObject> > *proxy = (Proxy<OObject<QObject> > *)Data_custom_val(v);
    //Proxy<OObject<QObject> > *t = dynamic_cast<Proxy<OObject<QObject> >*>(proxy);
    fprintf(stderr, "%s(): proxy = %p\n", __PRETTY_FUNCTION__, proxy);
    proxy->~Proxy();
}

struct custom_operations caml_mrvn_QT5_Proxy_custom_ops = {
    caml_mrvn_QT5_Proxy_identifier,
    proxy_finalize,
    custom_compare_default,
    custom_hash_default,
    custom_serialize_default,
    custom_deserialize_default,
    custom_compare_ext_default,
};

