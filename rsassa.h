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

    virtual void encrypt(const KeyGen& keygen) override;
    virtual void decrypt(const KeyGen& keygen) override;
};

#endif // RSASSA_H
