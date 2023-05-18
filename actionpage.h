#ifndef ACTIONPAGE_H
#define ACTIONPAGE_H

#include "actionbase.h"


class AbstractActionPage : public AbstractAction {
public:
    // constructor
    AbstractActionPage(const std::string& toolTipText, const std::string& iconPath);

    // destructor
    virtual ~AbstractActionPage();

public slots:
    virtual void onActionClick() override = 0;

};

#endif // ACTIONPAGE_H
