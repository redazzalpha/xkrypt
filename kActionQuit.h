#ifndef KACTIONQUIT_H
#define KACTIONQUIT_H

#include "kAction.h"

/**
 * KActionQuit class represents QAction object
 * inherits from KActionBase and handles
 * quit application
 */

class KActionQuit : public KAction {
public:
    // constructors
    KActionQuit();

    // destructor
    virtual ~KActionQuit();

public slots:
    virtual void onActionClick() override;
};

#endif // KACTIONQUIT_H
