#ifndef AESCCM_H
#define AESCCM_H

#include "cipheraes.h"

class AesCCM : public  AbstractCipherAes {
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
    virtual bool encryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false) override;
    virtual bool decryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false) override;

};


#endif // AESCCM_H
