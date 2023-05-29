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
std::string AbstractKeygen::password() const
{
    return m_password;
}

SecByteBlock& AbstractKeygen::genSalt()
{
    AutoSeededX917RNG<CryptoPP::AES> prng;
    m_salt.CleanNew(SALT_SIZE);
    prng.GenerateBlock(m_salt, m_salt.size());

//    string s = "11111111111111111111111111111111";
//    m_salt = SecByteBlock((CryptoPP::byte*)s.data(), s.size());

    return m_salt;
}
