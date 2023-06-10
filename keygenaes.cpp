#include "defines.h"
#include "enums.h"
#include "keygenaes.h"
#include <cryptopp/scrypt.h>
#include <base64.h>
#include <iostream>

using namespace CryptoPP;
using namespace std;

// constructors
KeygenAes::KeygenAes(size_t keysize): AbstractKeygen(keysize) {}
KeygenAes::KeygenAes(const KeygenAes &a) : AbstractKeygen(a.m_key.size())
{
    m_key.CleanNew(a.m_key.size());
    m_iv.CleanNew(a.m_iv.size());
    m_salt.CleanNew(a.m_salt.size());
    m_key = a.m_key;
    m_iv = a.m_iv;
    m_salt = a.m_salt;
    m_encoding = a.m_encoding;
    m_password = a.m_password;
    m_pkState = a.m_pkState;
}

// operators
KeygenAes &KeygenAes::operator=(const KeygenAes &a)
{
    if(this != &a) {
        m_key.CleanNew(a.m_key.size());
        m_iv.CleanNew(a.m_iv.size());
        m_salt.CleanNew(a.m_salt.size());
        m_key = a.m_key;
        m_iv = a.m_iv;
        m_salt = a.m_salt;
        m_keysize = a.m_keysize;
        m_encoding = a.m_encoding;
        m_password = a.m_password;
        m_pkState = a.m_pkState;
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
        m_salt.CleanNew(SALT_SIZE);
        m_prng.GenerateBlock(m_key, m_key.size());
        m_prng.GenerateBlock(m_iv, m_iv.size());
        m_prng.GenerateBlock(m_salt, m_salt.size());
    }
}
void KeygenAes::generateKey(size_t keysize, Encoding encoding)
{
    m_keysize = keysize;
    m_encoding = encoding;
    generateKey();
}
bool KeygenAes::isReady() const
{
    return
        (!m_key.empty() && !m_iv.empty()) &&
        (m_key.size() == m_keysize) &&
        (m_iv.size() == static_cast<size_t>(Aes::IvSize::LENGTH_DEFAULT));
}
void KeygenAes::flush()
{
    m_key.CleanNew(0);
    m_iv.CleanNew(0);
    m_salt.CleanNew(0);
}
KeygenAes* KeygenAes::keygenCpy()
{
    return new KeygenAes(*this);
}
void KeygenAes::setKey(CryptoPP::SecByteBlock key)
{
    m_key.CleanNew(0);
    m_key = key;
    m_keysize = m_key.size();
}
void KeygenAes::setIv(CryptoPP::SecByteBlock iv)
{
    m_iv.CleanNew(0);
    m_iv = iv;
}
void KeygenAes::setPkState(bool newPkState)
{
    m_pkState = newPkState;
}
SecByteBlock& KeygenAes::key()
{
    return m_key;
}
SecByteBlock& KeygenAes::Iv()
{
    return m_iv;
}

KeygenAes* KeygenAes::pkDerive(const std::string &password, const bool isGenSalt)
{
    Scrypt scrypt;

    if(isGenSalt) genSalt();
    m_key.CleanNew(static_cast<size_t>(Aes::KeySize::LENGTH_MAX));
    m_iv.CleanNew(static_cast<size_t>(Aes::IvSize::LENGTH_MAX));

    scrypt.DeriveKey(
        m_key, m_key.size(),
        (CryptoPP::byte*)password.data(), password.size(),
        m_salt, m_salt.size(),
        SCRYPT_COAST,
        SCRYPT_BLOCKSIZE,
        SCRYPT_PARALLELIZATION
    );
    scrypt.DeriveKey(
        m_iv, m_iv.size(),
        m_key, m_key.size(),
        m_salt, m_salt.size(),
        SCRYPT_COAST,
        SCRYPT_BLOCKSIZE,
        SCRYPT_PARALLELIZATION
    );

    return this;
}
KeygenAes *KeygenAes::pkDerive(const bool isGenSalt)
{
    Scrypt scrypt;

    if(isGenSalt) genSalt();
    m_iv.CleanNew(static_cast<size_t>(Aes::IvSize::LENGTH_MAX));

    scrypt.DeriveKey(
        m_key, m_key.size(),
        m_key, m_key.size(),
        m_salt, m_salt.size(),
        SCRYPT_COAST,
        SCRYPT_BLOCKSIZE,
        SCRYPT_PARALLELIZATION
        );
    scrypt.DeriveKey(
        m_iv, m_iv.size(),
        m_key, m_key.size(),
        m_salt, m_salt.size(),
        SCRYPT_COAST,
        SCRYPT_BLOCKSIZE,
        SCRYPT_PARALLELIZATION
    );

    return this;
}







