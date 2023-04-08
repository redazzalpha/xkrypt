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

    virtual std::string encryptText(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false) override;
    virtual std::string decryptText(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) noexcept(false) override;
    virtual bool encryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false) override;
    virtual bool decryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false) override;
};

#endif // AESGCM_H
