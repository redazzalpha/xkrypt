#ifndef AESCFB_H
#define AESCFB_H

#include "cipheraes.h"

class AesCFB : public AbstractCipherAes {
public:
    static const std::string ModeName;

    // constructors
    AesCFB();

    // destructor
    virtual ~AesCFB();

    // methods
    virtual std::string modeName() const override;
    virtual Mode modeId() const override;
    virtual std::string encryptText(const std::string& plain, Keygen* keygen, const Encoding encoding) override;
    virtual std::string decryptText(const std::string& cipher, Keygen* keygen, const Encoding encoding) override;
    virtual void encryptFile(const std::string& path, Keygen* keygen, const Encoding encoding) override;
    virtual void decryptFile(const std::string& path, Keygen* keygen, const Encoding encoding) override;
};

#endif // AESCFB_H