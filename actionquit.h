#ifndef ACTIONQUIT_H
#define ACTIONQUIT_H

#include "actionglobal.h"

/**
 * KActionQuit class represents QAction object
 * inherits from KActionBase and handles
 * quit application
 */

class ActionQuit : public AbstractActionGlobal {
public:
    // constructors
    ActionQuit();

    // destructor
    virtual ~ActionQuit();

public slots:
    virtual void onActionClick() override;
};

#endif // ACTIONQUIT_H
