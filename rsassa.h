#ifndef RSASSA_H
#define RSASSA_H

#include "cipherrsa.h"

class RsaSSA : public CipherRsa {
public:
    static const QString ModeName;

    // constructors
    RsaSSA();

    // destructor
    virtual ~RsaSSA();

    // methods
    virtual QString getModeName() const override;

    virtual void encrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override;
    virtual void decrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override;
};

#endif // RSASSA_H
