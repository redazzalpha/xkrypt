#ifndef AESEAX_H
#define AESEAX_H

#include "cipheraes.h"

class AesEAX : public  CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesEAX();

    // destructor
    virtual ~AesEAX();

    // methods
    virtual QString getModeName() const override;

    virtual void encrypt(const KeyGen& keygen) override;
    virtual void decrypt(const KeyGen& keygen) override;
};

#endif // AESEAX_H
