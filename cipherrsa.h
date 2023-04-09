#ifndef CIPHERRSA_H
#define CIPHERRSA_H

#include "cipherbase.h"

/**
 * CipherAes class represents Rsa algorithms
 * inherits from CipherBase and
 * encrypts decrypts and generates keys
 */

class AbstractCipherRsa : public AbstractCipherBase {
public:
    static const QString AlgName;

    // constructors
    AbstractCipherRsa();

    // destructor
    virtual ~AbstractCipherRsa();

    // methods
    virtual QString getAlgName() const final;
    virtual QString getModeName() const override = 0;

    virtual std::string encryptText(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false) override = 0;
    virtual std::string decryptText(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) noexcept(false) override = 0;
    virtual bool encryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false) override = 0;
    virtual bool decryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false) override = 0;
};

#endif // CIPHERRSA_H
