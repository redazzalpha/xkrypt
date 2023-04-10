#ifndef CIPHERAES_H
#define CIPHERAES_H

#include "cipherbase.h"

/**
 * CipherAes class represents Aes algorithms
 * inherits from CipherBase and
 * encrypts decrypts and generates keys
 */

class AbstractCipherAes : public AbstractCipherBase {
public:
    static const std::string AlgName;

    // constructors
    AbstractCipherAes();

    // destructor
    virtual ~AbstractCipherAes();

    // methods
    virtual std::string getAlgName() const final;
    virtual std::string getModeName() const override = 0 ;

    virtual std::string encryptText(const std::string& plain, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override = 0;
    virtual std::string decryptText(const std::string& cipher, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override = 0;
    virtual void encryptFile(const std::string& path, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override = 0;
    virtual void decryptFile(const std::string& path, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override = 0;
};

#endif // CIPHERAES_H
