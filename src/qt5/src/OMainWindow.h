#ifdef MRVN_QT5_OMAINWINDOW_H__INSIDE
#error header loop
#endif

#ifndef MRVN_QT5_OMAINWINDOW_H
#define MRVN_QT5_OMAINWINDOW_H
#define MRVN_QT5_OMAINWINDOW_H__INSIDE

#include "OWidget.h"

class OMainWindow : public OWidget {
public:
    OMainWindow();
    virtual ~OMainWindow();
    virtual void preDestructor();
    virtual void setCentralWidget(OWidget *w);
private:
    void removeCentralWidget();
};

#undef MRVN_QT5_OMAINWINDOW_H__INSIDE
#endif // #ifndef MRVN_QT5_OMAINWINDOW_H
