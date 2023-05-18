#include "enums.h"
#include "keygenaes.h"
#include <iostream>

using namespace CryptoPP;

// constructors
KeygenAes::KeygenAes(size_t keysize): AbstractKeygen(keysize)
{
    m_key.CleanNew(m_keysize);
    m_iv.CleanNew(static_cast<size_t>(Aes::IvSize::LENGTH_DEFAULT));
}

KeygenAes::KeygenAes(size_t keysize, size_t ivsize): AbstractKeygen(keysize)
{
    m_key.CleanNew(m_keysize);
    m_iv.CleanNew(ivsize);
}
KeygenAes::KeygenAes(const KeygenAes &a) : KeygenAes(a.m_key.size(), a.m_iv.size())
{
    m_key = a.m_key;
    m_iv = a.m_iv;
    m_encoding = a.m_encoding;
}

// operators
KeygenAes &KeygenAes::operator=(const KeygenAes &a)
{
    if(this != &a) {
        m_key.CleanNew(a.m_key.size());
        m_iv.CleanNew(a.m_iv.size());
        m_key = a.m_key;
        m_iv = a.m_iv;
        m_keysize = a.m_keysize;
        m_encoding = a.m_encoding;
    }
    return *this;
}

// methods
void KeygenAes::generateKey()
{
    flush();
    if(m_keysize >= static_cast<size_t>(Aes::KeySize::LENGTH_DEFAULT)) {
        m_key.CleanNew(m_keysize);
        m_iv.CleanNew(static_cast<size_t>(Aes::IvSize::LENGTH_DEFAULT));
        m_prng.GenerateBlock(m_key, m_key.size());
        m_prng.GenerateBlock(m_iv, m_iv.size());
    }
}
void KeygenAes::generateKey(size_t keysize, Encoding encoding)
{
    flush();
    m_keysize = keysize;
    m_encoding = encoding;
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
KeygenAes* KeygenAes::keygenCpy()
{
    return new KeygenAes(*this);
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

