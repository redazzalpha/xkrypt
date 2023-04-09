#include "actiondecrypt.h"
#include "defines.h"
#include "enums.h"

// constructors
ActionDecrypt::ActionDecrypt(): AbstractActionPage("decrypt manager", IMG_DECRYPT_MANAGER) {}

// destructor
ActionDecrypt::~ActionDecrypt(){}

// slots
void ActionDecrypt::onActionClick()
{
    emit setStackPage(Page::decrypt);
}
