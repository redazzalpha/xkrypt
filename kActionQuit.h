#ifndef KACTIONQUIT_H
#define KACTIONQUIT_H

#include "kActionBase.h"

/**
 * KActionQuit class represents QAction object
 * inherits from KActionBase and handles
 * quit application
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
