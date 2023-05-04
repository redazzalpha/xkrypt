#ifndef AESCTR_H
#define AESCTR_H

#include "cipheraes.h"

class AesCTR : public AbstractCipherAes {
public:
    static const std::string ModeName;

    // constructors
    AesCTR();

    // destructor
    virtual ~AesCTR();

    // methods
    virtual std::string getModeName() const override;

public slots:
    virtual std::string encryptText(const std::string& plain, Keygen* keygen, const Encoding encoding) override;
    virtual std::string decryptText(const std::string& cipher, Keygen* keygen, const Encoding encoding) override;
    virtual void encryptFile(std::vector<std::string> paths, Keygen* keygen, const Encoding encoding) override;
    virtual void decryptFile(std::vector<std::string> paths, Keygen* keygen, const Encoding encoding) override;
};

#endif // AESCTR_H
