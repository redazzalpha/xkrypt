#ifndef RSAOEAP_H
#define RSAOEAP_H

#include "cipherrsa.h"


class RsaOEAP : public CipherRsa {
public:
    static const QString ModeName;

    // constructors
    RsaOEAP();

    // destructor
    virtual ~RsaOEAP();

    // methods
    virtual QString getModeName() const override;
    virtual void decrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override;
    virtual void encrypt(CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv) override;
};

#endif // RSAOEAP_H
