#ifndef RSAOEAP_H
#define RSAOEAP_H

#include "cipherrsa.h"


class RsaOEAP : public AbstractCipherRsa {
public:
    static const QString ModeName;

    // constructors
    RsaOEAP();

    // destructor
    virtual ~RsaOEAP();

    // methods
    virtual QString getModeName() const override;

    virtual std::string encryptText(const std::string& plain, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override;
    virtual std::string decryptText(const std::string& cipher, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override;
    virtual bool encryptFile(const std::string& fname, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override;
    virtual bool decryptFile(const std::string& fname, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override;
};

#endif // RSAOEAP_H
