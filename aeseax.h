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

    virtual std::string encrypt(const KeyGen& keygen, const std::string& plain) override;
    virtual std::string decrypt(const KeyGen& keygen, const std::string& cipher) override;
};

#endif // AESEAX_H
