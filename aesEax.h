#ifndef AESEAX_H
#define AESEAX_H

#include "cipherAes.h"

class AesEAX : public  CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesEAX(const int keyLength = CryptoPP::AES::DEFAULT_KEYLENGTH);

    // destructor
    virtual ~AesEAX();

    // methods
    virtual void decrypt() override;
    virtual void encrypt() override;
    virtual QString getModeName() const override;
};

#endif // AESEAX_H
