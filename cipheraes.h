#ifndef CIPHERAES_H
#define CIPHERAES_H

#include "cipherbase.h"

/**
 * CipherAes class represents Aes algorithms
 * inherits from CipherBase and
 * encrypts decrypts and generates keys
 */

class AbstractCipherAes : public AbstractCipher {
public:
    static const std::string AlgName;

    // constructors
    AbstractCipherAes();

    // destructor
    virtual ~AbstractCipherAes();

    // methods
    virtual std::string algName() const final;
    virtual Algorithms algId() const final;
    virtual std::string modeName() const override = 0 ;
    virtual Mode modeId() const override = 0;
    virtual std::string encryptText(const std::string& plain, AbstractKeygen* keygen, const Encoding encoding) override = 0;
    virtual std::string decryptText(const std::string& cipher, AbstractKeygen* keygen, const Encoding encoding) override = 0;
    virtual void encryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding, const std::string& newDir = "") override = 0;
    virtual void decryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding, const std::string& newDir = "") override = 0;
};

#endif // CIPHERAES_H
