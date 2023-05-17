#include "keygenrsa.h"

// constructors
KeygenRsa::KeygenRsa(size_t keysize): AbstractKeygen(keysize) {}

// destructor
KeygenRsa::~KeygenRsa()
{
    delete m_private;
    delete m_public;
}

// methods
void KeygenRsa::generateKey()
{
    flush();
    m_private = new CryptoPP::RSA::PrivateKey;
    m_public = new CryptoPP::RSA::PublicKey;
    m_private->GenerateRandomWithKeySize(m_prng, static_cast<size_t>(m_keysize));
    *m_public = CryptoPP::RSA::PublicKey(*m_private);
}

void KeygenRsa::generateKey(size_t keysize, Encoding encoding)
{
    m_keysize = keysize;
    m_encoding = encoding;

    flush();
    m_private = new CryptoPP::RSA::PrivateKey;
    m_public = new CryptoPP::RSA::PublicKey;
    m_private->GenerateRandomWithKeySize(m_prng, static_cast<size_t>(m_keysize));
    *m_public = CryptoPP::RSA::PublicKey(*m_private);
}
bool KeygenRsa::isReady() const
{
}
void KeygenRsa::flush()
{
    delete m_private;
    delete m_public;
}

CryptoPP::RSA::PrivateKey* KeygenRsa::getPrivate()
{
    return m_private;
}

CryptoPP::RSA::PublicKey *KeygenRsa::getPublic()
{
    return m_public;
}
