#include "actionkeyMgr.h"
#include "defines.h"
#include "enums.h"

// constructors
ActionKeyMgr::ActionKeyMgr(): AbstractActionPage("key manager", IMG_KEY_MANAGER) {}

// destructor
ActionKeyMgr::~ActionKeyMgr(){}

// slots
void ActionKeyMgr::onActionClick()
{
    emit setStackPage(Page::generate);
}
