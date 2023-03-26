#ifndef AESEAX_H
#define AESEAX_H

#include "cipherAes.h"

class AesEAX : public  CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesEAX();

    // destructor
    virtual ~AesEAX();

    // methods
    virtual void generateKey() override;
    virtual void decrypt() override;
    virtual void encrypt() override;
    virtual QString getModeName() const override;
};

#endif // AESEAX_H
