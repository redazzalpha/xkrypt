#ifndef RSAOEAP_H
#define RSAOEAP_H

#include "cipherRsa.h"


class RsaOEAP : public CipherRsa {
public:
    static const QString ModeName;

    // constructors
    RsaOEAP();

    // destructor
    virtual ~RsaOEAP();

    // methods
    virtual QString getModeName() const override;
    virtual void decrypt() override;
    virtual void encrypt() override;
    virtual CryptoPP::SecByteBlock generateKey() override;
};

#endif // RSAOEAP_H
