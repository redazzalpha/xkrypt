#include "kActionDecrypt.h"

// constructors
KActionDecrypt::KActionDecrypt(): KActionBase("decrypt manager", ":/assets/decrypt.png") {}

// slots
void KActionDecrypt::onActionClick() { emit setStackPage(2); }
