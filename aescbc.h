#ifndef AESCBC_H
#define AESCBC_H

#include "cipheraes.h"

class AesCBC : public CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesCBC();

    // destructor
    virtual ~AesCBC();

    // methods
    virtual QString getModeName() const override;
    virtual void encrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override;
    virtual void decrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override;
};

#endif // AESCBC_H
