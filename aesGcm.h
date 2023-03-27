#ifndef AESGCM_H
#define AESGCM_H

#include "cipherAes.h"

class AesGCM : public  CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesGCM(const int keyLength = CryptoPP::AES::DEFAULT_KEYLENGTH);

    // destructor
    virtual ~AesGCM();

    // methods
    virtual void decrypt() override;
    virtual void encrypt() override;
    virtual QString getModeName() const override;
};

#endif // AESGCM_H
