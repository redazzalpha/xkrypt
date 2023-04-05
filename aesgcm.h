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

    virtual std::string encrypt(const KeyGen& keygen, const std::string& plain) override;
    virtual std::string decrypt(const KeyGen& keygen, const std::string& cipher) override;
};

#endif // AESGCM_H
