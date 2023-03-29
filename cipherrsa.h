#ifndef CIPHERRSA_H
#define CIPHERRSA_H

#include "cipherbase.h"

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
    virtual QString getModeName() const override = 0;
    virtual void encrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override = 0;
    virtual void decrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override = 0;
};

#endif // CIPHERRSA_H
