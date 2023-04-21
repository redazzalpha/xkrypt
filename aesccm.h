#ifndef AESCCM_H
#define AESCCM_H

#include "cipheraes.h"

class AesCCM : public  AbstractCipherAes {
public:
    static const std::string ModeName;

    // constructors
    AesCCM();

    // destructor
    virtual ~AesCCM();

    // methods
    virtual std::string getModeName() const override;
    

public slots:
    virtual std::string encryptText(const std::string& plain, Keygen* keygen, const Encoding encoding) override;
    virtual std::string decryptText(const std::string& cipher, Keygen* keygen, const Encoding encoding) override;
    virtual void encryptFile(std::vector<std::string> paths, Keygen* keygen, const Encoding encoding) override;
    virtual void decryptFile(std::vector<std::string> paths, Keygen* keygen, const Encoding encoding) override;
};


#endif // AESCCM_H
