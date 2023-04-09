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
    static const QString AlgName;

    // constructors
    AbstractCipherAes();

    // destructor
    virtual ~AbstractCipherAes();

    // methods
    virtual QString getAlgName() const final;
    virtual QString getModeName() const override = 0 ;

    virtual std::string encryptText(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false) override = 0;
    virtual std::string decryptText(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) noexcept(false) override = 0;
    virtual bool encryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false) override = 0;
    virtual bool decryptFile(const KeyGen& keygen, const Encoding encoding) noexcept(false) override = 0;
};

#endif // CIPHERAES_H
