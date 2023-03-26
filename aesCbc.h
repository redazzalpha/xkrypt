#ifndef AESCBC_H
#define AESCBC_H

#include "cipherAes.h"

class AesCBC : public CipherAes {
public:
    // constructors
    AesCBC();

    // destructor
    virtual ~AesCBC();

    // methods
    virtual void generateKey() override;
    virtual void decrypt() override;
    virtual void encrypt() override;
};

#endif // AESCBC_H
