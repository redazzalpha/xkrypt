#ifndef ACTIONDECRYPT_H
#define ACTIONDECRYPT_H

#include "actionpage.h"

/**
 * KActionDecrypt class represents QAction object
 * inherits from KActionBase and handles decrypt
 * manager visibility
 */

class ActionDecrypt : public AbstractActionPage {
public:
    // constructors
    ActionDecrypt();

    // destructor
    virtual ~ActionDecrypt();

public slots:
    virtual void onActionClick() override;
};

#endif // KACTIONENCRYPT_H

