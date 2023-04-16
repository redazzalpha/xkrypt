#ifndef RSASSA_H
#define RSASSA_H

#include "cipherrsa.h"

class RsaSSA : public AbstractCipherRsa {
public:
    static const std::string ModeName;

    // constructors
    RsaSSA();

    // destructor
    virtual ~RsaSSA();

    // methods
    virtual std::string getModeName() const override;
    
    virtual std::string encryptText(const std::string& plain, Keygen* keygen, const Encoding encoding) noexcept(false) override;
    virtual std::string decryptText(const std::string& cipher, Keygen* keygen, const Encoding encoding) noexcept(false) override;
    virtual void encryptFile(std::vector<std::string>* paths, Keygen* keygen, const Encoding encoding) noexcept(false) override;
    virtual void decryptFile(std::vector<std::string>* paths, Keygen* keygen, const Encoding encoding) noexcept(false) override;
};

#endif // RSASSA_H
