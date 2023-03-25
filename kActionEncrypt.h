#ifndef KACTIONENCRYPT_H
#define KACTIONENCRYPT_H

#include "kActionBase.h"

/**
 * KActionEncrypt class represent QAction object
 * inherits from KActionBase
 */

class KActionEncrypt : public KActionBase {

public:
    // constructors
    KActionEncrypt();

    // destructor
    virtual ~KActionEncrypt();

public slots:
    virtual void onActionClick();
};

#endif // KACTIONENCRYPT_H
