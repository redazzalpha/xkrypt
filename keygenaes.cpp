#include "defines.h"
#include "enums.h"
#include "keygenaes.h"
#include <cryptopp/scrypt.h>
#include <base64.h>
#include <iostream>

using namespace CryptoPP;
using namespace std;

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
    m_key.CleanNew(a.m_key.size());
    m_iv.CleanNew(a.m_iv.size());
    m_salt.CleanNew(a.m_salt.size());
    m_key = a.m_key;
    m_iv = a.m_iv;
    m_salt = a.m_salt;
    m_encoding = a.m_encoding;
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
        genSalt();
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
bool KeygenAes::pkState() const
{
    return m_pkState;
}

KeygenAes* KeygenAes::pkDerive(const std::string &password, const bool create)
{
    KeygenAes* pk = new KeygenAes(*this);
    Scrypt scrypt;

    if(create) pk->genSalt();
    pk->m_key.CleanNew(static_cast<size_t>(Aes::KeySize::LENGTH_32));
    pk->m_iv.CleanNew(static_cast<size_t>(Aes::IvSize::LENGTH_DEFAULT));

    scrypt.DeriveKey(
        pk->m_key, pk->m_key.size(),
        (CryptoPP::byte*)password.data(), password.size(),
        pk->m_salt, pk->m_salt.size(),
        SCRYPT_COAST,
        SCRYPT_BLOCKSIZE,
        SCRYPT_PARALLELIZATION
    );
    scrypt.DeriveKey(
        pk->m_iv, pk->m_iv.size(),
        pk->m_key, pk->m_key.size(),
        pk->m_salt, pk->m_salt.size(),
        SCRYPT_COAST,
        SCRYPT_BLOCKSIZE,
        SCRYPT_PARALLELIZATION
    );

    return pk;
}
KeygenAes *KeygenAes::pkDerive(const SecByteBlock& key, const bool isGenSalt)
{
    KeygenAes* pk = new KeygenAes(*this);
    Scrypt scrypt;

    if(isGenSalt) pk->genSalt();
    pk->m_key.CleanNew(m_key.size());
    pk->m_iv.CleanNew(static_cast<size_t>(Aes::IvSize::LENGTH_DEFAULT));

    scrypt.DeriveKey(
        pk->m_key, pk->m_key.size(),
        key, key.size(),
        pk->m_salt, pk->m_salt.size(),
        SCRYPT_COAST,
        SCRYPT_BLOCKSIZE,
        SCRYPT_PARALLELIZATION
        );
    scrypt.DeriveKey(
        pk->m_iv, pk->m_iv.size(),
        pk->m_key, pk->m_key.size(),
        pk->m_salt, pk->m_salt.size(),
        SCRYPT_COAST,
        SCRYPT_BLOCKSIZE,
        SCRYPT_PARALLELIZATION
    );

    return pk;
}







