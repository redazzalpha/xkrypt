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
    static const QString AlgName;

    // constructors
    CipherRsa();

    // destructor
    virtual ~CipherRsa();

    // methods
    virtual QString getAlgName() const final;
    virtual QString getModeName() const = 0;
    virtual void generateKey() = 0;
    virtual void decrypt() = 0;
    virtual void encrypt() = 0;
};

#endif // CIPHERRSA_H
