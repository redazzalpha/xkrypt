#ifndef AESECB_H
#define AESECB_H

#include "cipheraes.h"

class AesECB : public  AbstractCipherAes {
public:
    static const std::string ModeName;

    // constructors
    AesECB();

    // destructor
    virtual ~AesECB();

    // methods
    virtual std::string getModeName() const override;


public slots:
    virtual std::string encryptText(const std::string& plain, Keygen* keygen, const Encoding encoding) override;
    virtual std::string decryptText(const std::string& cipher, Keygen* keygen, const Encoding encoding) override;
    virtual void encryptFile(std::vector<std::string> paths, Keygen* keygen, const Encoding encoding) override;
    virtual void decryptFile(std::vector<std::string> paths, Keygen* keygen, const Encoding encoding) override;
};

#endif // AESECB_H
