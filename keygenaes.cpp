#include "enums.h"
#include "keygenaes.h"
#include <iostream>

using namespace CryptoPP;

// constructors
KeygenAes::KeygenAes(size_t keysize): AbstractKeygen(keysize){}

// methods
void KeygenAes::generateKey()
{
    m_key.CleanNew(0);
    m_iv.CleanNew(0);
    if(m_keysize >= static_cast<size_t>(Aes::KeySize::LENGTH_DEFAULT)) {
        m_key.CleanNew(static_cast<size_t>(m_keysize));
        m_iv.CleanNew(static_cast<size_t>(Aes::IvSize::LENGTH_DEFAULT));
        m_prng.GenerateBlock(m_key, m_key.size());
        m_prng.GenerateBlock(m_iv, m_iv.size());
    }
}
void KeygenAes::generateKey(size_t keysize, Encoding encoding)
{
    m_keysize = keysize;
    m_encoding = encoding;
    m_key.CleanNew(0);
    m_iv.CleanNew(0);
    if(m_keysize >= static_cast<size_t>(Aes::KeySize::LENGTH_DEFAULT)) {
        m_key.CleanNew(static_cast<size_t>(m_keysize));
        m_iv.CleanNew(static_cast<size_t>(Aes::IvSize::LENGTH_DEFAULT));
        m_prng.GenerateBlock(m_key, m_key.size());
        m_prng.GenerateBlock(m_iv, m_iv.size());
    }
}
bool KeygenAes::isReady() const
{
    return !m_key.empty() && !m_iv.empty();
}
void KeygenAes::flush()
{
    m_key.CleanNew(0);
    m_iv.CleanNew(0);
}

void KeygenAes::setKey(CryptoPP::SecByteBlock key)
{
    m_key.CleanNew(0);
    m_key = key;
}
void KeygenAes::setIv(CryptoPP::SecByteBlock iv)
{
    m_iv.CleanNew(0);
    m_iv = iv;
}
const SecByteBlock& KeygenAes::getKey() const
{
    return m_key;
}
const SecByteBlock& KeygenAes::getIv() const
{
    return m_iv;
}

