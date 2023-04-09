#ifndef ACTIONQUIT_H
#define ACTIONQUIT_H

#include "action.h"

/**
 * KActionQuit class represents QAction object
 * inherits from KActionBase and handles
 * quit application
 */

class ActionQuit : public AbstractAction {
public:
    // constructors
    ActionQuit();

    // destructor
    virtual ~ActionQuit();

public slots:
    virtual void onActionClick() override;
};

#endif // ACTIONQUIT_H
