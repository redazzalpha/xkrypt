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
    static const QString AlgName;

    // constructors
    CipherAes();

    // destructor
    virtual ~CipherAes();

    // methods
    virtual QString getAlgName() const final;
    virtual QString getModeName() const = 0;
    virtual void generateKey() = 0;
    virtual void decrypt() = 0;
    virtual void encrypt() = 0;

};

#endif // CIPHERAES_H
