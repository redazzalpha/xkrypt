#ifndef CIPHERAES_H
#define CIPHERAES_H

#include "cipherbase.h"

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
    virtual QString getModeName() const override = 0 ;
    virtual void encrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override = 0;
    virtual void decrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override = 0;
};

#endif // CIPHERAES_H
