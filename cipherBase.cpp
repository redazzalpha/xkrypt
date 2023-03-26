#include "cipherBase.h"

// constructors
CipherBase::CipherBase() {}

// destructor
CipherBase::~CipherBase() {}

// methods
bool CipherBase::isKeyLoaded() const {
    return !(m_key.empty());
}
