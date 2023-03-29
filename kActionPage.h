#ifndef KACTIONPAGE_H
#define KACTIONPAGE_H

#include "kActionBase.h"


class KActionPage : public KActionBase {
public:
    // constructor
    KActionPage(const std::string& toolTipText, const std::string& iconPath);

    // destructor
    virtual ~KActionPage();

public slots:
    virtual void onActionClick() override = 0;

};

#endif // KACTIONPAGE_H
