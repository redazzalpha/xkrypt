#include "kactionkeyMgr.h"
#include "defines.h"
#include "enums.h"

// constructors
KActionKeyMgr::KActionKeyMgr(): KActionPage("key manager", IMG_KEY_MANAGER) {}

// destructor
KActionKeyMgr::~KActionKeyMgr(){}

// slots
void KActionKeyMgr::onActionClick() { emit setStackPage(Page::generate); }
