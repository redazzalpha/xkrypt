#ifndef RSAOAEP_H
#define RSAOAEP_H

#include "cipherrsa.h"


class RsaOAEP : public AbstractCipherRsa {
public:
    static const std::string ModeName;

    // constructors
    RsaOAEP();

    // destructor
    virtual ~RsaOAEP();

    // methods
    virtual std::string modeName() const override;
    virtual Mode modeId() const override;
    virtual std::string encryptText(const std::string& plain, AbstractKeygen* keygen, const Encoding encoding) override;
    virtual std::string decryptText(const std::string& cipher, AbstractKeygen* keygen, const Encoding encoding) override;
    virtual void encryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding, const std::string& newDir = "") override;
    virtual void decryptFile(const std::string& path, AbstractKeygen* keygen, const Encoding encoding, const std::string& newDir = "") override;
};

#endif // RSAOAEP_H
