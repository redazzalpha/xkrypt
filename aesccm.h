#ifndef AESCCM_H
#define AESCCM_H

#include "cipheraes.h"

class AesCCM : public  CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesCCM();

    // destructor
    virtual ~AesCCM();

    // methods
    virtual QString getModeName() const override;

    virtual std::string encryptText(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false) override;
    virtual std::string decryptText(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) noexcept(false) override;
    virtual void encryptFile(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false) override;
    virtual void decryptFile(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) noexcept(false) override;

};


#endif // AESCCM_H
