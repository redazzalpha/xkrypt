#ifndef KEYGENBASE_H
#define KEYGENBASE_H

#include "enums.h"
#include "osrng.h"

class AbstractKeygen {
protected:
    CryptoPP::AutoSeededX917RNG<CryptoPP::AES> m_prng;
    size_t m_keysize;
    Encoding m_encoding = Encoding::NONE;
    CryptoPP::SecByteBlock m_salt {0};
    std::string m_password;

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
    virtual AbstractKeygen* keygenCpy() = 0;

    void setKeysize(size_t keysize);
    void setEncoding(Encoding newEncoding);
    void setSalt(const CryptoPP::SecByteBlock &newSalt);
    std::string password() const;
    size_t keysize() const;
    Encoding encoding() const;
    CryptoPP::SecByteBlock& salt();
    void setPassword(const std::string &newPassword);

    CryptoPP::SecByteBlock& genSalt();
};

#endif // KEYGENBASE_H
