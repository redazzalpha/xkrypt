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
    virtual void decrypt(const KeyGen& keygen) override;
    virtual void encrypt(const KeyGen& keygen) override;
};

#endif // RSAOEAP_H
