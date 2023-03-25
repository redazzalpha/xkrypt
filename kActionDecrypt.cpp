#include "kActionDecrypt.h"

// constructors
KActionDecrypt::KActionDecrypt(): KActionBase("decrypt manager", ":/assets/decrypt.png") {}

// destructor
KActionDecrypt::~KActionDecrypt(){}

// slots
void KActionDecrypt::onActionClick() { emit setStackPage(Page::decrypt); }
