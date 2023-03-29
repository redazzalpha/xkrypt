#ifndef KACTIONKEYMGR_H
#define KACTIONKEYMGR_H

#include "kactionpage.h"

/**
 * KActionKeyMgr class represents QAction object
 * inherits from KActionBase and handles key
 * manager visibility
 */

class KActionKeyMgr : public KActionPage {
public:
    // constructors
    KActionKeyMgr();

    // destructor
    virtual ~KActionKeyMgr();

public slots:
    virtual void onActionClick() override;
};

#endif // KACTIONKEYMGR_H
