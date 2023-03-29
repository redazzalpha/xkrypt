#include "kactionkeyMgr.h"
#include "enums.h"

// constructors
KActionKeyMgr::KActionKeyMgr(): KActionPage("key manager", ":/assets/key.png") {}

// destructor
KActionKeyMgr::~KActionKeyMgr(){}

// slots
void KActionKeyMgr::onActionClick() { emit setStackPage(Page::generate); }
