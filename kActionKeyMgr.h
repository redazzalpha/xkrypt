#ifndef KACTIONKEYMGR_H
#define KACTIONKEYMGR_H

#include "kActionBase.h"

/**
 * KActionKeyMgr class represents QAction object
 * inherits from KActionBase and handles key
 * manager visibility
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
