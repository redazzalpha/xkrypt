#ifndef AESGCM_H
#define AESGCM_H

#include "cipherAes.h"

class AesGCM : public  CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesGCM();

    // destructor
    virtual ~AesGCM();

    // methods
    virtual void generateKey() override;
    virtual void decrypt() override;
    virtual void encrypt() override;
    virtual QString getModeName() const override;
};

#endif // AESGCM_H
