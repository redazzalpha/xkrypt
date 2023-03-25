#include "kActionQuit.h"

// constructors
KActionQuit::KActionQuit(): KActionBase("quit", ":/assets/quit.png") {}

// destructor
KActionQuit::~KActionQuit(){}

// slots
void KActionQuit::onActionClick() { emit quit(); }
