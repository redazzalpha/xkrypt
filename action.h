#ifndef ACTION_H
#define ACTION_H

#include "actionbase.h"

class AbstractAction : public AbstractActionBase {
public:
    // constructor
    AbstractAction(const std::string& toolTipText, const std::string& iconPath);

    // destructor
    virtual ~AbstractAction();

public slots:
    virtual void onActionClick() override = 0;
};

#endif // ACTION_H
