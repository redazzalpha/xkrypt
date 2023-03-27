#include "cipherBase.h"

// constructors
CipherBase::CipherBase() {}

// destructor
CipherBase::~CipherBase() {}

bool CipherBase::isKeyLoaded() const {
    // return true by default for
    // inherited classes that don't redefine
    return true;
}
