#ifndef AESGCM_H
#define AESGCM_H

#include "cipheraes.h"

class AesGCM : public  CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesGCM();

    // destructor
    virtual ~AesGCM();

    // methods
    virtual QString getModeName() const override;

    virtual void encrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override;
    virtual void decrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override;
};

#endif // AESGCM_H
