#include "keygenbase.h"
#include "defines.h"

using namespace CryptoPP;
using namespace std;

// constructors
AbstractKeygen::AbstractKeygen(size_t keysize): m_keysize(keysize), m_salt(SALT_SIZE) {}

// destructor
AbstractKeygen::~AbstractKeygen() {}

// methods
void AbstractKeygen::setKeysize(size_t keysize)
{
    m_keysize = keysize;
}
void AbstractKeygen::setEncoding(Encoding newEncoding)
{
    m_encoding = newEncoding;
}
void AbstractKeygen::setSalt(const CryptoPP::SecByteBlock &newSalt)
{
    m_salt = newSalt;
}
void AbstractKeygen::setPassword(const std::string &newPassword)
{
    m_password = newPassword;
}
void AbstractKeygen::setPkState(bool newPkState)
{
    m_pkState = newPkState;
}
size_t AbstractKeygen::keysize() const
{
    return m_keysize;
}
Encoding AbstractKeygen::encoding() const
{
    return m_encoding;
}
SecByteBlock& AbstractKeygen::salt()
{
    return m_salt;
}
std::string& AbstractKeygen::password()
{
    return m_password;
}
bool AbstractKeygen::pkState() const
{
    return m_pkState;
}

SecByteBlock& AbstractKeygen::genSalt()
{
    m_salt.CleanNew(SALT_SIZE);
    m_prng.GenerateBlock(m_salt, m_salt.size());
    return m_salt;
}
