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
    static const std::string AlgName;

    // constructors
    AbstractCipherRsa();

    // destructor
    virtual ~AbstractCipherRsa();

    // methods
    virtual std::string getAlgName() const final;
    virtual std::string getModeName() const override = 0;

    virtual std::string encryptText(const std::string& plain, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override = 0;
    virtual std::string decryptText(const std::string& cipher, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override = 0;
    virtual void encryptFile(const std::string& path, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override = 0;
    virtual void decryptFile(const std::string& path, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override = 0;
};

#endif // CIPHERRSA_H
