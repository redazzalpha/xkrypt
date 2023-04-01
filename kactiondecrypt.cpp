#include "kactiondecrypt.h"
#include "defines.h"
#include "enums.h"

// constructors
KActionDecrypt::KActionDecrypt(): KActionPage("decrypt manager", IMG_DECRYPT_MANAGER) {}

// destructor
KActionDecrypt::~KActionDecrypt(){}

// slots
void KActionDecrypt::onActionClick()
{
    emit setStackPage(Page::decrypt);
}
