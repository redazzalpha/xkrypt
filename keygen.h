#ifndef KEYGEN_H
#define KEYGEN_H

#include "osrng.h"
#include "secblock.h"
#include "enums.h"

class KeyGen {
private:
    CryptoPP::AutoSeededRandomPool m_prng;
    CryptoPP::SecByteBlock m_key {0};
    CryptoPP::SecByteBlock m_iv {0};
    KeyLength m_keyLength = KeyLength::LENGTH_DEFAULT;

public:
    // constructors
    KeyGen();
    KeyGen(KeyLength keyLength);

    // methods
    void setKey(CryptoPP::SecByteBlock key);
    void setIv(CryptoPP::SecByteBlock iv);
    void setKeyLength(KeyLength keyLength = KeyLength::LENGTH_DEFAULT);
    const CryptoPP::SecByteBlock& getKey() const;
    const CryptoPP::SecByteBlock& getIv() const;

    void generateKey();
    bool isReady() const;
    void flush();
};

#endif // KEYGEN_H
