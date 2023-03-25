#include "kActionEncrypt.h"

// constructors
KActionEncrypt::KActionEncrypt(): KActionBase("encrypt manager", ":/assets/encrypt.png") {}

// destructor
KActionEncrypt::~KActionEncrypt(){}

// slots
void KActionEncrypt::onActionClick() { emit setStackPage(Page::encrypt); }
