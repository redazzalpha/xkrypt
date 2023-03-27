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
    virtual void decrypt() override;
    virtual void encrypt() override;
    virtual std::string generateKey(const bool saveOnfile) override;
    virtual QString getModeName() const override;
};

#endif // RSAOEAP_H
