#include "keygenrsa.h"
#include <iostream>
#include <hex.h>
#include <integer.h>

using namespace std;

// constructors

KeygenRsa::KeygenRsa(size_t keysize): AbstractKeygen(keysize) {}
KeygenRsa::KeygenRsa(const KeygenRsa &a): AbstractKeygen(a.m_keysize)
{
    m_private = new CryptoPP::RSA::PrivateKey(*a.m_private);
    m_public = new CryptoPP::RSA::PublicKey(*a.m_public);
    m_encoding = a.m_encoding;
}

KeygenRsa &KeygenRsa::operator=(const KeygenRsa &a)
{
    if(this != &a) {
        m_private = new CryptoPP::RSA::PrivateKey(*a.m_private);
        m_public = new CryptoPP::RSA::PublicKey(*a.m_public);
        m_keysize = a.m_keysize;
        m_encoding = a.m_encoding;
    }
    return *this;
}

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
    m_private = new CryptoPP::RSA::PrivateKey();
    m_private->GenerateRandomWithKeySize(m_prng, static_cast<size_t>(m_keysize));
    m_public = new CryptoPP::RSA::PublicKey(*m_private);
}
void KeygenRsa::generateKey(size_t keysize, Encoding encoding)
{
    m_keysize = keysize;
    m_encoding = encoding;

    flush();
    m_private = new CryptoPP::RSA::PrivateKey;
    m_private->GenerateRandomWithKeySize(m_prng, static_cast<size_t>(m_keysize));
    m_public = new CryptoPP::RSA::PublicKey(*m_private);
}
bool KeygenRsa::isReady() const
{
    return true; // got to set return
}
void KeygenRsa::flush()
{
    if(m_private) delete m_private;
    if(m_public) delete m_public;
    m_private = new CryptoPP::RSA::PrivateKey;
    m_public = new CryptoPP::RSA::PublicKey;
}
KeygenRsa* KeygenRsa::keygenCpy()
{
    return new KeygenRsa(*this);
}

void KeygenRsa::setPrivate(CryptoPP::RSA::PrivateKey *newPrivate)
{
    delete m_private;
    m_private = new CryptoPP::RSA::PrivateKey(*newPrivate);
}
void KeygenRsa::setPublic(CryptoPP::RSA::PrivateKey *privateKey)
{
    delete m_public;
    m_public = new CryptoPP::RSA::PublicKey(*privateKey);
}
void KeygenRsa::setPublic(CryptoPP::RSA::PublicKey *newPublic)
{
    delete m_public;
    m_public = new CryptoPP::RSA::PublicKey(*newPublic);
}
CryptoPP::RSA::PrivateKey* KeygenRsa::getPrivate()
{
    return m_private;
}
CryptoPP::RSA::PublicKey *KeygenRsa::getPublic()
{
    return m_public;
}

CryptoPP::InvertibleRSAFunction KeygenRsa::params()
{
    CryptoPP::InvertibleRSAFunction params;
    params.SetModulus(m_private->GetModulus());
    params.SetPrime1(m_private->GetPrime1());
    params.SetPrime2(m_private->GetPrime2());
    params.SetPublicExponent(m_private->GetPublicExponent());
    params.SetPrivateExponent(m_private->GetPrivateExponent());

    return params;
}

