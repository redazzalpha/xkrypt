#include "keygen.h"
#include <iostream>

using namespace CryptoPP;

// constructors
KeyGen::KeyGen(){}
KeyGen::KeyGen(KeyLength keyLength): m_keyLength(keyLength){}

// methods
void KeyGen::setKey(CryptoPP::SecByteBlock key)
{
    m_key.CleanNew(0);
    m_key = key;
}
void KeyGen::setIv(CryptoPP::SecByteBlock iv)
{
    m_iv.CleanNew(0);
    m_iv = iv;
}
void KeyGen::setKeyLength(KeyLength keyLength)
{
    m_keyLength = keyLength;
}
const SecByteBlock& KeyGen::getKey() const
{
    return m_key;
}
const SecByteBlock& KeyGen::getIv() const
{
    return m_iv;
}

void KeyGen::generateKey()
{
    m_key.CleanNew(static_cast<size_t>(m_keyLength));
    m_iv.CleanNew(static_cast<size_t>(IvLength::LENGTH_DEFAULT));
    m_prng.GenerateBlock(m_key, m_key.size());
    m_prng.GenerateBlock(m_iv, m_iv.size());
}
bool KeyGen::isReady() const
{
    return !m_key.empty() && !m_iv.empty();
}
void KeyGen::flush()
{
    m_key.CleanNew(0);
    m_iv.CleanNew(0);
}
