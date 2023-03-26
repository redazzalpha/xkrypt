#ifndef AESGCM_H
#define AESGCM_H

#include "cipherAes.h"

class AesGCM : public  CipherAes {
protected:
public:
    // constructors
    AesGCM();

    // destructor
    virtual ~AesGCM();

    // methods
    virtual void generateKey() override;
    virtual void decrypt() override;
    virtual void encrypt() override;
};

#endif // AESGCM_H
