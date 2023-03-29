#ifndef KEYGEN_H
#define KEYGEN_H

#include "osrng.h"
#include "secblock.h"

class KeyGen {
private:
    CryptoPP::AutoSeededRandomPool m_prng;
    CryptoPP::SecByteBlock m_key;
    CryptoPP::SecByteBlock m_iv = CryptoPP::SecByteBlock(CryptoPP::AES::BLOCKSIZE);
    int m_keyLength = CryptoPP::AES::BLOCKSIZE;

public:
    // constructors
    KeyGen();
    KeyGen(int keyLength);

    // methods
    void setKeyLength(int keyLength);
    CryptoPP::SecByteBlock generateKey();
    bool isKeyLoaded() const;
    void flushKey();
};

#endif // KEYGEN_H
