#ifndef AESEAX_H
#define AESEAX_H

#include "cipheraes.h"

class AesEAX : public  AbstractCipherAes {
public:
    static const std::string ModeName;

    // constructors
    AesEAX();

    // destructor
    virtual ~AesEAX();

    // methods
    virtual std::string modeName() const override;
    virtual Mode modeId() const override;
    virtual std::string encryptText(const std::string& plain, AbstractKeygen* keygen, const Encoding encoding) override;
    virtual std::string decryptText(const std::string& cipher, AbstractKeygen* keygen, const Encoding encoding) override;
    virtual void encryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding, const std::string& newDir = "") override;
    virtual void decryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding, const std::string& newDir = "") override;
};

#endif // AESEAX_H
