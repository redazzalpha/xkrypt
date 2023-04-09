#ifndef ACTIONENCRYPT_H
#define ACTIONENCRYPT_H

#include "actionpage.h"

/**
 * KActionEncrypt class represents QAction object
 * inherits from KActionBase and handles encrypt
 * manager visibility
 */

class ActionEncrypt : public AbstractActionPage {
public:
    // constructors
    ActionEncrypt();

    // destructor
    virtual ~ActionEncrypt();

public slots:
    virtual void onActionClick() override;
};

#endif // ACTIONENCRYPT_H
