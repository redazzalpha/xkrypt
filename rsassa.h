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

    virtual std::string encryptText(const std::string& plain, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override;
    virtual std::string decryptText(const std::string& cipher, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override;
    virtual bool encryptFile(const std::string& path, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override;
    virtual bool decryptFile(const std::string& path, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override;
};

#endif // RSASSA_H
