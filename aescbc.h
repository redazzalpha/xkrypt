#ifndef AESCBC_H
#define AESCBC_H

#include "cipheraes.h"
#include "keygen.h"

class AesCBC : public CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesCBC();

    // destructor
    virtual ~AesCBC();

    // methods
    virtual QString getModeName() const override;

    virtual std::string encrypt(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false) override;
    virtual std::string decrypt(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) noexcept(false) override;
};

#endif // AESCBC_H
