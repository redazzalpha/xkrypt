#ifndef AESGCM_H
#define AESGCM_H

#include "cipheraes.h"

class AesGCM : public  AbstractCipherAes {
public:
    static const std::string ModeName;

    // constructors
    AesGCM();

    // destructor
    virtual ~AesGCM();

    // methods
    virtual std::string getModeName() const override;
    
    virtual std::string encryptText(const std::string& plain, Keygen* keygen, const Encoding encoding) noexcept(false) override;
    virtual std::string decryptText(const std::string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false) override;
    virtual void encryptFile(std::vector<std::string>* paths, Keygen* keygen, const Encoding encoding) noexcept(false) override;
    virtual void decryptFile(std::vector<std::string>* paths, Keygen* keygen, const Encoding encoding) noexcept(false) override;
};

#endif // AESGCM_H
