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
    CipherRsa(const std::string& algName);

    // destructor
    virtual ~CipherRsa();

    // methods
    virtual void generateKey() = 0;
    virtual void decrypt() = 0;
    virtual void encrypt() = 0;

};

#endif // CIPHERRSA_H
