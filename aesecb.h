#ifndef AESECB_H
#define AESECB_H

#include "cipheraes.h"

class AesECB : public  AbstractCipherAes {
public:
    static const std::string ModeName;

    // constructors
    AesECB();

    // destructor
    virtual ~AesECB();

    // methods
    virtual std::string modeName() const override;
    virtual Mode modeId() const override;
    virtual std::string encryptText(const std::string& plain, AbstractKeygen* keygen, const Encoding encoding) override;
    virtual std::string decryptText(const std::string& cipher, AbstractKeygen* keygen, const Encoding encoding) override;
    virtual void encryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding) override;
    virtual void decryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding) override;
};

#endif // AESECB_H
