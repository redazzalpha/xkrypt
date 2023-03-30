#ifndef KEYGEN_H
#define KEYGEN_H

#include "osrng.h"
#include "secblock.h"
#include "enums.h"

class KeyGen {
private:
    CryptoPP::AutoSeededRandomPool m_prng;
    CryptoPP::SecByteBlock m_key;
    CryptoPP::SecByteBlock m_iv = CryptoPP::SecByteBlock(CryptoPP::AES::BLOCKSIZE);
    KeyLength m_keyLength = KeyLength::LENGTH_DEFAULT;

public:
    // constructors
    KeyGen();
    KeyGen(KeyLength keyLength);

    // methods
    void setKeyLength(KeyLength keyLength = KeyLength::LENGTH_DEFAULT);
    int getKeyLength();
    CryptoPP::SecByteBlock generateKey();
    bool isKeyLoaded() const;
    void flushKey();
};

#endif // KEYGEN_H
