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
    virtual std::string encrypt(const KeyGen& keygen, const std::string& plain) override;
    virtual std::string decrypt(const KeyGen& keygen, const std::string& cipher) override;
};

#endif // RSAOEAP_H
