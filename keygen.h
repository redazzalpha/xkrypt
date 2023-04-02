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
    void setKey(CryptoPP::SecByteBlock key);
    void setIv(CryptoPP::SecByteBlock iv);
    void setKeyLength(KeyLength keyLength = KeyLength::LENGTH_DEFAULT);
    CryptoPP::SecByteBlock getKey();
    CryptoPP::SecByteBlock getIv();

    void generateKey();
    bool isReady() const;
    void flush();
};

#endif // KEYGEN_H
