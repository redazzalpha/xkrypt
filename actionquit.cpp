#include "actionquit.h"
#include "defines.h"

// constructors
ActionQuit::ActionQuit(): AbstractActionGlobal("quit", IMG_QUIT) {}

// destructor
ActionQuit::~ActionQuit(){}

// slots
void ActionQuit::onActionClick()
{
    emit quit();
}
