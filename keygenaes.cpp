#include "enums.h"
#include "keygenaes.h"
#include <cryptopp/scrypt.h>
#include <iostream>

using namespace CryptoPP;

// constructors
KeygenAes::KeygenAes(size_t keysize): AbstractKeygen(keysize)
{
    m_key.CleanNew(m_keysize);
    m_iv.CleanNew(static_cast<size_t>(Aes::IvSize::LENGTH_DEFAULT));
    m_pk.CleanNew(static_cast<size_t>(Aes::KeySize::LENGTH_32));
    m_pkiv.CleanNew(static_cast<size_t>(Aes::IvSize::LENGTH_DEFAULT));
}

KeygenAes::KeygenAes(size_t keysize, size_t ivsize): AbstractKeygen(keysize)
{
    m_key.CleanNew(m_keysize);
    m_iv.CleanNew(ivsize);
    m_pk.CleanNew(static_cast<size_t>(Aes::KeySize::LENGTH_32));
    m_pkiv.CleanNew(static_cast<size_t>(Aes::IvSize::LENGTH_DEFAULT));
}
KeygenAes::KeygenAes(const KeygenAes &a) : KeygenAes(a.m_key.size(), a.m_iv.size())
{
    m_key.CleanNew(a.m_key.size());
    m_iv.CleanNew(a.m_iv.size());
    m_pk.CleanNew(a.m_pk.size());
    m_pkiv.CleanNew(a.m_pkiv.size());
    m_salt.CleanNew(a.m_salt.size());
    m_key = a.m_key;
    m_iv = a.m_iv;
    m_pk = a.m_pk;
    m_pkiv = a.m_pkiv;
    m_salt = a.m_salt;
    m_encoding = a.m_encoding;
}

// operators
KeygenAes &KeygenAes::operator=(const KeygenAes &a)
{
    if(this != &a) {
        m_key.CleanNew(a.m_key.size());
        m_iv.CleanNew(a.m_iv.size());
        m_pk.CleanNew(a.m_pk.size());
        m_pkiv.CleanNew(a.m_pkiv.size());
        m_salt.CleanNew(a.m_salt.size());
        m_key = a.m_key;
        m_iv = a.m_iv;
        m_pk = a.m_pk;
        m_pkiv = a.m_pkiv;
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
    m_keysize = m_key.size();
}
void KeygenAes::setIv(CryptoPP::SecByteBlock iv)
{
    m_iv.CleanNew(0);
    m_iv = iv;
}
void KeygenAes::setPk(CryptoPP::SecByteBlock pk)
{
    m_pk = pk;
}
void KeygenAes::setPkIv(CryptoPP::SecByteBlock pkiv)
{
    m_pkiv = pkiv;
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
SecByteBlock& KeygenAes::pk()
{
    return m_pk;
}
SecByteBlock& KeygenAes::pkiv()
{
    return m_pkiv;
}
bool KeygenAes::pkState() const
{
    return m_pkState;
}

KeygenAes* KeygenAes::pkDerive(const std::string &password, const bool create)
{
    int iterations = 0, coast = 1024, blocksize = 8, parallelization = 16;
    CryptoPP::Scrypt scrypt;
    if(create) {
        m_pk.CleanNew(static_cast<size_t>(Aes::KeySize::LENGTH_32));
        m_pkiv.CleanNew(static_cast<size_t>(Aes::IvSize::LENGTH_DEFAULT));
        genSalt();
        genPkIv();
    }

    iterations = scrypt.DeriveKey(m_pk, m_pk.size(), (CryptoPP::byte*)password.data(), password.size(), m_salt, m_salt.size(), coast, blocksize, parallelization);
    std::cout << "iterations performed: " << iterations << std::endl;

    return this;
}
SecByteBlock& KeygenAes::genPkIv()
{
    AutoSeededX917RNG<CryptoPP::AES> prng;
    m_pkiv.CleanNew(static_cast<size_t>(Aes::IvSize::LENGTH_DEFAULT));
    prng.GenerateBlock(m_pkiv, m_pkiv.size());
    return m_pkiv;

}

