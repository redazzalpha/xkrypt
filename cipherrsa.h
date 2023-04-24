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

public slots:
    virtual std::string encryptText(const std::string& plain, Keygen* keygen, const Encoding encoding) override = 0;
    virtual std::string decryptText(const std::string& cipher, Keygen* keygen, const Encoding encoding) override = 0;
    virtual void encryptFile(std::vector<std::string> paths, Keygen* keygen, const Encoding encoding) override = 0;
    virtual void decryptFile(std::vector<std::string>  paths, Keygen* keygen, const Encoding encoding) override = 0;
};

#endif // CIPHERRSA_H
