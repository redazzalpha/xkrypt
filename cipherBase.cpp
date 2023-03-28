#include "cipherBase.h"
#include <fstream>


// constructors
CipherBase::CipherBase() {}

// destructor
CipherBase::~CipherBase() {}

// methods
bool CipherBase::isKeyLoaded() const {
    // return true by default for
    // inherited classes that don't redefine
    return true;
}
