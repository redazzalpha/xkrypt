#include "cipherBase.h"

// constructors
CipherBase::CipherBase(const std::string& algName): m_algName(algName) {}

// destructor
CipherBase::~CipherBase() {}

// methods
bool CipherBase::isKeyLoaded() {
    return !(m_key.empty());
}
