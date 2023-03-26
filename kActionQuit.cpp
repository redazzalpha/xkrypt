#include "kActionQuit.h"

// constructors
KActionQuit::KActionQuit(): KAction("quit", ":/assets/quit.png") {}

// destructor
KActionQuit::~KActionQuit(){}

// slots
void KActionQuit::onActionClick() { emit quit(); }
