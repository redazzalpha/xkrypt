#ifndef KEYGENBASE_H
#define KEYGENBASE_H

#include "enums.h"
#include "osrng.h"

class AbstractKeygen {
protected:
    CryptoPP::AutoSeededX917RNG<CryptoPP::AES> m_prng;
    size_t m_keysize;
    Encoding m_encoding = Encoding::NONE;

public:
    // constructors
    AbstractKeygen(size_t keysize);

    //destructor
    virtual ~AbstractKeygen();

    // methods
    virtual void generateKey() = 0;
    virtual void generateKey(size_t keysize, Encoding encoding) = 0;
    virtual bool isReady() const = 0;
    virtual void flush() = 0;

    void setKeysize(size_t keysize);
    void setEncoding(Encoding newEncoding);
    size_t keysize() const;
    Encoding encoding() const;
};

#endif // KEYGENBASE_H
