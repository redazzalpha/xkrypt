#include "actionencrypt.h"
#include "defines.h"
#include "enums.h"

// constructors
ActionEncrypt::ActionEncrypt(): AbstractActionPage("encrypt manager", IMG_ENCRYPT_MANAGER) {}

// destructor
ActionEncrypt::~ActionEncrypt(){}

// slots
void ActionEncrypt::onActionClick()
{
    emit setStackPage(Page::encrypt);
}
