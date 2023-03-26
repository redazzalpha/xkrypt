#include "cipherBase.h"

// constructors
CipherBase::CipherBase(const std::string& algName):  m_algName(algName) {}

// destructor
CipherBase::~CipherBase() {}

// methods
bool CipherBase::isKeyLoaded() const {
    return !(m_key.empty());
}
std::string CipherBase::getAlgName() const {
    return m_algName;
}

