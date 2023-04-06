#ifndef RSASSA_H
#define RSASSA_H

#include "cipherrsa.h"

class RsaSSA : public CipherRsa {
public:
    static const QString ModeName;

    // constructors
    RsaSSA();

    // destructor
    virtual ~RsaSSA();

    // methods
    virtual QString getModeName() const override;

    virtual std::string encrypt(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false) override;
    virtual std::string decrypt(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) noexcept(false) override;
};

#endif // RSASSA_H
