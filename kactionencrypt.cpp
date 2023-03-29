#include "kactionencrypt.h"
#include "enums.h"

// constructors
KActionEncrypt::KActionEncrypt(): KActionPage("encrypt manager", ":/assets/encrypt.png") {}

// destructor
KActionEncrypt::~KActionEncrypt(){}

// slots
void KActionEncrypt::onActionClick() { emit setStackPage(Page::encrypt); }
