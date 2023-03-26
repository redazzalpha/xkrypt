#ifndef CIPHERAES_H
#define CIPHERAES_H

#include "cipherBase.h"

/**
 * CipherAes class represents Aes algorithms
 * inherits from CipherBase and
 * encrypts decrypts and generates keys
 */

class CipherAes : public CipherBase {
public:
    // constructors
    CipherAes(const std::string& algName);

    // destructor
    virtual ~CipherAes();

    // methods
    virtual void generateKey() = 0;
    virtual void decrypt() = 0;
    virtual void encrypt() = 0;
};

#endif // CIPHERAES_H
