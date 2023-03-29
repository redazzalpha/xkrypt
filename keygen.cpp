#include "keygen.h"
#include <iostream>

using namespace CryptoPP;

// constructors
KeyGen::KeyGen() {}
KeyGen::KeyGen(int keyLength): m_keyLength(keyLength) {}

// methods
void KeyGen::setKeyLength(int keyLength) {
    m_keyLength = keyLength;
}
SecByteBlock KeyGen::generateKey() {
    m_key.CleanNew(m_keyLength);
    m_prng.GenerateBlock(m_key, m_key.size());
    m_prng.GenerateBlock(m_iv, m_iv.size());
    return m_key;
}
bool KeyGen::isKeyLoaded() const {
    return !m_key.empty();
}
void KeyGen::flushKey() {
    m_key.CleanNew(0);
}
