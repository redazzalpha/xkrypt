#ifndef AESCBC_H
#define AESCBC_H

#include "cipherAes.h"

class AesCBC : public CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesCBC();

    // destructor
    virtual ~AesCBC();

    // methods
    virtual void generateKey() override;
    virtual void decrypt() override;
    virtual void encrypt() override;
    virtual QString getModeName() const override;
};

#endif // AESCBC_H
