#ifndef AESEAX_H
#define AESEAX_H

#include "cipherAes.h"

class AesEAX : public  CipherAes {
public:
    // constructors
    AesEAX();

    // destructor
    virtual ~AesEAX();

    // methods
    virtual void generateKey() override;
    virtual void decrypt() override;
    virtual void encrypt() override;
};

#endif // AESEAX_H
