#include "kActionEncrypt.h"

// constructors
KActionEncrypt::KActionEncrypt(): KActionBase("encrypt manager", ":/assets/encrypt.png") {}

// slots
void KActionEncrypt::onActionClick() { emit setStackPage(0); }
