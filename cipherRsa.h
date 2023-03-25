#ifndef CIPHERRSA_H
#define CIPHERRSA_H

#include "cipherBase.h"

/**
 * CipherAes class represents Rsa algorithms
 * inherits from CipherBase and
 * encrypts decrypts and generates keys
 */

class CipherRsa : public CipherBase {

public:
    // constructors
    CipherRsa();

    // destructor
    virtual ~CipherRsa();

    // methods
    virtual void generateKey();
    virtual void decrypt();
    virtual void encrypt();

};

#endif // CIPHERRSA_H
