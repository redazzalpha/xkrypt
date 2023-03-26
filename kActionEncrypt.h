#ifndef KACTIONENCRYPT_H
#define KACTIONENCRYPT_H

#include "kActionPage.h"

/**
 * KActionEncrypt class represents QAction object
 * inherits from KActionBase and handles encrypt
 * manager visibility
 */

class KActionEncrypt : public KActionPage {
public:
    // constructors
    KActionEncrypt();

    // destructor
    virtual ~KActionEncrypt();

public slots:
    virtual void onActionClick();
};

#endif // KACTIONENCRYPT_H
