#ifndef KACTIONDECRYPT_H
#define KACTIONDECRYPT_H

#include "kactionpage.h"

/**
 * KActionDecrypt class represents QAction object
 * inherits from KActionBase and handles decrypt
 * manager visibility
 */

class KActionDecrypt : public KActionPage {
public:
    // constructors
    KActionDecrypt();

    // destructor
    virtual ~KActionDecrypt();

public slots:
    virtual void onActionClick() override;
};

#endif // KACTIONENCRYPT_H

