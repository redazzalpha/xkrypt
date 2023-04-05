#ifndef AESGCM_H
#define AESGCM_H

#include "cipheraes.h"

class AesGCM : public  CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesGCM();

    // destructor
    virtual ~AesGCM();

    // methods
    virtual QString getModeName() const override;

    virtual void encrypt(const KeyGen& keygen) override;
    virtual void decrypt(const KeyGen& keygen) override;
};

#endif // AESGCM_H
