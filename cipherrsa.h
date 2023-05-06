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
    virtual std::string algName() const final;
    virtual std::string modeName() const override = 0;
    virtual Alg algId() const final;
    virtual Mode modeId() const override = 0;
    virtual std::string encryptText(const std::string& plain, Keygen* keygen, const Encoding encoding) override = 0;
    virtual std::string decryptText(const std::string& cipher, Keygen* keygen, const Encoding encoding) override = 0;
    virtual void encryptFile(const std::string& path, Keygen* keygen, const Encoding encoding) override = 0;
    virtual void decryptFile(const std::string& path, Keygen* keygen, const Encoding encoding) override = 0;
};

#endif // CIPHERRSA_H
