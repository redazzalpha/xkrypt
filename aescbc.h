#ifndef AESCBC_H
#define AESCBC_H

#include "cipheraes.h"
#include "keygen.h"

class AesCBC : public CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesCBC();

    // destructor
    virtual ~AesCBC();

    // methods
    virtual QString getModeName() const override;

    virtual void encrypt(const KeyGen& keygen) override;
    virtual void decrypt(const KeyGen& keygen) override;
};

#endif // AESCBC_H
