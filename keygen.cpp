#include "keygen.h"
#include <iostream>

using namespace CryptoPP;

// constructors
Keygen::Keygen(){}
Keygen::Keygen(KeyLength keyLength): m_keyLength(keyLength){}

// methods
void Keygen::setKey(CryptoPP::SecByteBlock key)
{
    m_key.CleanNew(0);
    m_key = key;
}
void Keygen::setIv(CryptoPP::SecByteBlock iv)
{
    m_iv.CleanNew(0);
    m_iv = iv;
}
void Keygen::setKeyLength(KeyLength keyLength)
{
    m_keyLength = keyLength;
}
const SecByteBlock& Keygen::getKey() const
{
    return m_key;
}
const SecByteBlock& Keygen::getIv() const
{
    return m_iv;
}

void Keygen::generateKey()
{
    m_key.CleanNew(0);
    m_iv.CleanNew(0);
    if(m_keyLength >= KeyLength::LENGTH_DEFAULT) {
        m_key.CleanNew(static_cast<size_t>(m_keyLength));
        m_iv.CleanNew(static_cast<size_t>(IvLength::LENGTH_DEFAULT));
        m_prng.GenerateBlock(m_key, m_key.size());
        m_prng.GenerateBlock(m_iv, m_iv.size());
    }
}
bool Keygen::isReady() const
{
    return !m_key.empty() && !m_iv.empty();
}
void Keygen::flush()
{
    m_key.CleanNew(0);
    m_iv.CleanNew(0);
}
