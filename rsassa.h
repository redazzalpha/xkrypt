#ifndef RSASSA_H
#define RSASSA_H

#include "cipherrsa.h"

class RsaSSA : public AbstractCipherRsa {
public:
    static const QString ModeName;

    // constructors
    RsaSSA();

    // destructor
    virtual ~RsaSSA();

    // methods
    virtual QString getModeName() const override;

    virtual std::string encryptText(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false) override;
    virtual std::string decryptText(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) noexcept(false) override;
    virtual bool encryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false) override;
    virtual bool decryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false) override;
};

#endif // RSASSA_H
