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
    virtual std::string getModeName() const override;

    virtual std::string encryptText(const std::string& plain, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override;
    virtual std::string decryptText(const std::string& cipher, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override;
    virtual void encryptFile(const std::vector<std::string>& paths, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override;
    virtual void decryptFile(const std::vector<std::string>& paths, const KeyGen& keygen, const Encoding encoding) const noexcept(false) override;
};

#endif // AESEAX_H
