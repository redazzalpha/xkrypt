#ifndef AESEAX_H
#define AESEAX_H

#include "cipheraes.h"

class AesEAX : public  CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesEAX();

    // destructor
    virtual ~AesEAX();

    // methods
    virtual QString getModeName() const override;
    virtual void encrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override;
    virtual void decrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override;
};

#endif // AESEAX_H
