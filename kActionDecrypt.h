#ifndef KACTIONDECRYPT_H
#define KACTIONDECRYPT_H

#include "kActionBase.h"

/**
 * KActionDecrypt class represent QAction object
 * inherits from KActionBase
 */

class KActionDecrypt : public KActionBase {

public:
    // constructors
    KActionDecrypt();

    // destructor
    virtual ~KActionDecrypt();

public slots:
    virtual void onActionClick();
};

#endif // KACTIONENCRYPT_H

