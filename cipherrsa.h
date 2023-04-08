#ifndef CIPHERRSA_H
#define CIPHERRSA_H

#include "cipherbase.h"

/**
 * CipherAes class represents Rsa algorithms
 * inherits from CipherBase and
 * encrypts decrypts and generates keys
 */

class CipherRsa : public CipherBase {
public:
    static const QString AlgName;

    // constructors
    CipherRsa();

    // destructor
    virtual ~CipherRsa();

    // methods
    virtual QString getAlgName() const final;
    virtual QString getModeName() const override = 0;

    virtual std::string encryptText(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false) override = 0;
    virtual std::string decryptText(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) noexcept(false) override = 0;
    virtual void encryptFile(const KeyGen& keygen, std::fstream* file, const Encoding encoding) noexcept(false) = 0;
    virtual void decryptFile(const KeyGen& keygen, std::fstream* file, const Encoding encoding) noexcept(false) = 0;
};

#endif // CIPHERRSA_H
