#ifndef KACTIONQUIT_H
#define KACTIONQUIT_H

#include "kActionBase.h"

/**
 * KActionDecrypt class represent QAction object
 * inherits from KActionBase
 */

class KActionQuit : public KActionBase {

public:
    // constructors
    KActionQuit();

    // destructor
    virtual ~KActionQuit();

public slots:
    virtual void onActionClick();
};

#endif // KACTIONQUIT_H
