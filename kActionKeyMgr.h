#ifndef KACTIONKEYMGR_H
#define KACTIONKEYMGR_H

#include "kActionBase.h"

/**
 * KActionKeyMgr class represent QAction object
 * inherits from KActionBase
 */

class KActionKeyMgr : public KActionBase {

public:
    // constructors
    KActionKeyMgr();

    // destructor
    virtual ~KActionKeyMgr();

public slots:
    virtual void onActionClick();
};

#endif // KACTIONKEYMGR_H
