#ifndef AESCTR_H
#define AESCTR_H

#include "cipheraes.h"

class AesCTR : public AbstractCipherAes {
public:
    static const std::string ModeName;

    // constructors
    AesCTR();

    // destructor
    virtual ~AesCTR();

    // methods
    virtual std::string modeName() const override;
    virtual Mode modeId() const override;
    virtual std::string encryptText(const std::string& plain, AbstractKeygen* keygen, const Encoding encoding) override;
    virtual std::string decryptText(const std::string& cipher, AbstractKeygen* keygen, const Encoding encoding) override;
    virtual void encryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding) override;
    virtual void decryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding) override;
};

#endif // AESCTR_H
