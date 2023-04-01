#include "kactionquit.h"
#include "defines.h"

// constructors
KActionQuit::KActionQuit(): KAction("quit", IMG_QUIT) {}

// destructor
KActionQuit::~KActionQuit(){}

// slots
void KActionQuit::onActionClick()
{
    emit quit();
}
