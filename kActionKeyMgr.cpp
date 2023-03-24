#include "kActionKeyMgr.h"

// constructors
KActionKeyMgr::KActionKeyMgr(): KActionBase("key manager", ":/assets/keyManager.png") {}

// slots
void KActionKeyMgr::onActionClick() { emit setStackPage(1); }
