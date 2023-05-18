#ifndef ACTIONGLOBAL_H
#define ACTIONGLOBAL_H

#include "actionbase.h"

class AbstractActionGlobal : public AbstractAction {
public:
    // constructor
    AbstractActionGlobal(const std::string& toolTipText, const std::string& iconPath);

    // destructor
    virtual ~AbstractActionGlobal();

public slots:
    virtual void onActionClick() override = 0;
};

#endif // ACTIONGLOBAL_H
