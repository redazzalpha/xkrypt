#include "kactiondecrypt.h"
#include "enums.h"

// constructors
KActionDecrypt::KActionDecrypt(): KActionPage("decrypt manager", ":/assets/decrypt.png") {}

// destructor
KActionDecrypt::~KActionDecrypt(){}

// slots
void KActionDecrypt::onActionClick() { emit setStackPage(Page::decrypt); }
