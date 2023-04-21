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
    

public slots:
    virtual std::string encryptText(const std::string& plain, Keygen* keygen, const Encoding encoding) override;
    virtual std::string decryptText(const std::string& cipher, Keygen* keygen, const Encoding encoding) override;
    virtual void encryptFile(std::vector<std::string> paths, Keygen* keygen, const Encoding encoding) override;
    virtual void decryptFile(std::vector<std::string> paths, Keygen* keygen, const Encoding encoding) override;
};

#endif // RSASSA_H
