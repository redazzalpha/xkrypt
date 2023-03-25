#ifndef DEFINES_H
#define DEFINES_H

#include <iostream>

std::string NO_KEY_MSG(std::string action) { return "Cannot " + action + " - No key has not been loaded! \n Please load key or generate one and retry."; }

#endif // DEFINES_H
