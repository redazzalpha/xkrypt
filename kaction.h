#ifndef KACTION_H
#define KACTION_H

#include "kactionbase.h"

class KAction : public KActionBase {
public:
    // constructor
    KAction(const std::string& toolTipText, const std::string& iconPath);

    // destructor
    virtual ~KAction();

public slots:
    virtual void onActionClick() override = 0;
};

#endif // KACTION_H
