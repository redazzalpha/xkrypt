#ifndef RSAOEAP_H
#define RSAOEAP_H

#include "cipherrsa.h"


class RsaOEAP : public CipherRsa {
public:
    static const QString ModeName;

    // constructors
    RsaOEAP();

    // destructor
    virtual ~RsaOEAP();

    // methods
    virtual QString getModeName() const override;

    virtual std::string encryptText(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false) override;
    virtual std::string decryptText(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) noexcept(false) override;
    virtual void encryptFile(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false) override;
    virtual void decryptFile(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) noexcept(false) override;
};

#endif // RSAOEAP_H
