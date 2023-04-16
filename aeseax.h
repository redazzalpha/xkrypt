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
    
    virtual std::string encryptText(const std::string& plain, Keygen* keygen, const Encoding encoding) noexcept(false) override;
    virtual std::string decryptText(const std::string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false) override;
    virtual void encryptFile(std::vector<std::string>* paths, Keygen* keygen, const Encoding encoding) noexcept(false) override;
    virtual void decryptFile(std::vector<std::string>* paths, Keygen* keygen, const Encoding encoding) noexcept(false) override;
};

#endif // AESEAX_H
