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
    CipherAes();

    // destructor
    virtual ~CipherAes();

    // methods
    virtual void generateKey();
    virtual void decrypt();
    virtual void encrypt();
};

#endif // CIPHERAES_H
