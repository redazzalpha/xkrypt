#include "kactionencrypt.h"
#include "defines.h"
#include "enums.h"

// constructors
KActionEncrypt::KActionEncrypt(): KActionPage("encrypt manager", IMG_ENCRYPT_MANAGER) {}

// destructor
KActionEncrypt::~KActionEncrypt(){}

// slots
void KActionEncrypt::onActionClick() { emit setStackPage(Page::encrypt); }
