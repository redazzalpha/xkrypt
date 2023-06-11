#ifndef AESCBC_H
#define AESCBC_H

#include "cipheraes.h"

class AesCBC : public AbstractCipherAes {
public:
    static const std::string ModeName;

    // constructors
    AesCBC();

    // destructor
    virtual ~AesCBC();

    // methods
    virtual std::string modeName() const override;
    virtual Mode modeId() const override;
    virtual std::string encryptText(const std::string& plain, AbstractKeygen* keygen, const Encoding encoding) override;
    virtual std::string decryptText(const std::string& cipher, AbstractKeygen* keygen, const Encoding encoding) override;
    virtual void encryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding, const std::string& newDir = "") override;
    virtual void decryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding, const std::string& newDir = "") override;
};

#endif // AESCBC_H
