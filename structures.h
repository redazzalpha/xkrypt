#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "secblock.h"

struct KeyIv
{
    CryptoPP::SecByteBlock m_key;
    CryptoPP::SecByteBlock m_iv;

    // constructors
    KeyIv(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv);
};

#endif // STRUCTURES_H
