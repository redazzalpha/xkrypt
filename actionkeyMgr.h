#ifndef ACTIONKEYMGR_H
#define ACTIONKEYMGR_H

#include "actionpage.h"

/**
 * KActionKeyMgr class represents QAction object
 * inherits from KActionBase and handles key
 * manager visibility
 */

class ActionKeyMgr : public AbstractActionPage {
public:
    // constructors
    ActionKeyMgr();

    // destructor
    virtual ~ActionKeyMgr();

public slots:
    virtual void onActionClick() override;
};

#endif // ACTIONKEYMGR_H
