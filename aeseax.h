#ifndef AESEAX_H
#define AESEAX_H

#include "cipheraes.h"

class AesEAX : public  CipherAes {
public:
    static const QString ModeName;

    // constructors
    AesEAX();

    // destructor
    virtual ~AesEAX();

    // methods
    virtual QString getModeName() const override;

    virtual std::string encryptText(const KeyGen& keygen, const std::string& plain, const Encoding encoding) noexcept(false) override;
    virtual std::string decryptText(const KeyGen& keygen, const std::string& cipher, const Encoding encoding) noexcept(false) override;
    virtual void encryptFile(const KeyGen& keygen, std::fstream* file, const Encoding encoding) noexcept(false) override;
    virtual void decryptFile(const KeyGen& keygen, std::fstream* file, const Encoding encoding) noexcept(false) override;
};

#endif // AESEAX_H
